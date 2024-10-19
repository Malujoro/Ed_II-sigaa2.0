#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "../../extras/extras.h"
#include "../arvore/arvore.h"
#include "../lista_alunos/lista.h"

void cadastrar_aluno(Lista **lista, ArvoreBB *raiz_curso)
{
    Aluno aluno;

    leia_int("Código do curso do aluno: ", &aluno.codigo_curso);

    ArvoreBB *curso;
    curso = arvorebb_buscar(raiz_curso, aluno.codigo_curso);
    if(curso != NULL)
    {
        aluno.nome = alocar_str(50);

        leia_int("Matricula do aluno: ", &aluno.matricula);
        leia_str("Nome do aluno: ", aluno.nome);

        aluno.arvbb_matricula = arvorebb_cria();
        aluno.arvbb_nota = arvorebb_cria();
        lista_add_ordenado(lista, aluno);
    }
    else
        printf("\nCurso não existe\n");
}

void cadastrar_curso(ArvoreBB **raiz_curso)
{
    Curso curso;
    curso.nome = alocar_str(50);

    leia_int("Código do curso: ", &curso.cod);
    leia_str("Nome do curso: ", curso.nome);

    curso.qt_periodos = 0;
    while(curso.qt_periodos <= 0)
    {
        leia_int("Quantidade de períodos: ", &curso.qt_periodos);
        if(curso.qt_periodos < 0)
            printf("\nErro! Digite uma quantidade válida de períodos\n");
    }

    curso.arvbb_disciplina = arvorebb_cria();

    union Data info;
    info.curso = curso;

    if(arvorebb_add(raiz_curso, info))
        printf("\nCurso cadastrado com sucesso\n");
    else
    {
        printf("\nNão foi possível adicionar curso! Código já utilizado\n");
        free(curso.nome);
        curso.nome = NULL;
    }
}

void cadastrar_disciplina(ArvoreBB *raiz_curso)
{
    int codigo_curso;

    leia_int("Código do curso: ", &codigo_curso);

    ArvoreBB *curso;
    curso = arvorebb_buscar(raiz_curso, codigo_curso);

    if(curso != NULL)
    {
        Disciplina disciplina;
        disciplina.nome_disciplina = alocar_str(50);

        leia_int("\nCódigo da disciplina: ", &disciplina.codigo_disciplina);
        leia_str("Nome da disciplina: ", disciplina.nome_disciplina);

        disciplina.periodo = 0;
        while(disciplina.periodo <= 0 || disciplina.periodo > curso->info.curso.qt_periodos)
        {
            leia_int("Período da disciplina: ", &disciplina.periodo);
            if(disciplina.periodo <= 0 || disciplina.periodo > curso->info.curso.qt_periodos)
                printf("\nErro! Digite um período entre 1 e %d\n", curso->info.curso.qt_periodos);
        }

        disciplina.carga_horaria = 0;
        while(disciplina.carga_horaria < 30 || disciplina.carga_horaria > 90 || disciplina.carga_horaria % 15 != 0)
        {
            leia_int("Carga horária: ", &disciplina.carga_horaria);
            if(disciplina.carga_horaria < 30 || disciplina.carga_horaria > 90 || disciplina.carga_horaria % 15 != 0)
                printf("\nErro! Digite uma carga horária entre 30 e 90 que seja divisível por 15\n");
        }
        
        union Data info;
        info.disciplina = disciplina;
        if(arvorebb_add(&(curso->info.curso.arvbb_disciplina), info))
            printf("\nDisciplina cadastrada com sucesso\n");
        else
        {
            printf("\nNão foi possível adicionar disciplina! Código já utilizado\n");
            free(disciplina.nome_disciplina);
            disciplina.nome_disciplina = NULL;
        }
    }
    else
        printf("\nCurso não cadastrado\n");
}

void cadastrar_matricula(Lista *lista, ArvoreBB *raiz_curso)
{
    int matricula_aluno;

    leia_int("Matricula do aluno: ", &matricula_aluno);

    Lista *aluno;
    aluno = lista_alunos_buscar(lista, matricula_aluno);
    
    if (aluno != NULL)
    {
        ArvoreBB *curso;
        curso = arvorebb_buscar(raiz_curso, aluno->info.codigo_curso);

        int codigo_disciplina;
        leia_int("Código da disciplina: ", &codigo_disciplina);

        ArvoreBB *disciplina;
        disciplina = arvorebb_buscar(curso->info.curso.arvbb_disciplina, codigo_disciplina);

        if (disciplina != NULL)
        {
            union Data info;
            info.matricula = codigo_disciplina;
            if(arvorebb_add(&(aluno->info.arvbb_matricula), info))
                printf("\nMatrícula efetuada com sucesso na disciplina %s\n", disciplina->info.disciplina.nome_disciplina);
            else
                printf("\nMatrícula já foi realizada anteriormente\n");
        }
        else
            printf("\nDisciplina inválida\n");
    }
    else
        printf("\nAluno não encontrado\n");

}

void cadastrar_notas(Lista *lista)
{
    int matricula_aluno;

    leia_int("Matricula do aluno: ", &matricula_aluno);

    Lista *aluno;
    aluno = lista_alunos_buscar(lista, matricula_aluno);
    
    if (aluno != NULL)
    {
        Nota nota;
        leia_int("Código da disciplina: ", &nota.codigo_disciplina);

        if(arvorebb_remover(&(aluno->info.arvbb_matricula), nota.codigo_disciplina))
        {
            leia_int("Semestre: ", &nota.semestre);
            nota.nota_final = -1;
            while(nota.nota_final < 0 || nota.nota_final > 10)
            {
                leia_float("Nota final: ", &nota.nota_final);
                if(nota.nota_final < 0 || nota.nota_final > 10)
                    printf("\nErro! Digite uma nota válida\n");
            }
            union Data info;
            info.nota = nota;
            if(arvorebb_add(&(aluno->info.arvbb_nota), info))
                printf("\nNota cadastrada com sucesso\n");
            else
                printf("\nNão foi possível cadastrar nota\n");
        }
        else
            printf("\nCódigo inválido\n");
    }
    else
        printf("\nAluno não encontrado\n");
}