#include <stdio.h>
#include <stdlib.h>
#include "cadastro.h"
#include "lista_alunos/lista.h"
#include "arvorebb_matricula/arvorebb_matricula.h"
#include "arvorebb_disciplina/arvorebb_disciplina.h"
#include "arvorebb_curso/arvorebb_curso.h"
#include "arvorebb_notas/arvorebb_notas.h"

void cadastrar_aluno(Lista **lista, ArvoreBB_Curso *raiz)
{
    Aluno aluno;

    leia_int("\nCódigo do curso do aluno: ", &aluno.codigo_curso);

    ArvoreBB_Curso *curso = arvorebb_curso_buscar(raiz, aluno.codigo_curso);
    if(curso != NULL)
    {
        aluno.nome = alocar_str(50);

        leia_int("Matricula do aluno: ", &aluno.matricula);
        leia_str("Nome do aluno: ", aluno.nome);

        aluno.arvbb_matricula = arvorebb_matricula_cria();   // = NULL
        aluno.arvbb_nota = arvorebb_nota_cria();   // = NULL
        lista_add_ordenado(lista, aluno);
    }
    else
        printf("\nCurso não existe");
}

void cadastrar_curso(ArvoreBB_Curso **raiz)
{
    Curso curso;
    curso.nome = alocar_str(50);

    leia_int("\nCódigo do curso: ", &curso.cod);
    leia_str("Nome do curso: ", curso.nome);

    curso.qt_periodos = 0;
    while(curso.qt_periodos <= 0)
    {
        leia_int("Quantidade de períodos: ", &curso.qt_periodos);
        if(curso.qt_periodos < 0)
            printf("\nErro! Digite uma quantidade válida de períodos");
    }

    curso.arvbb_disciplina = arvorebb_disciplina_cria();

    if(arvorebb_curso_add(raiz, curso))
        printf("\nCurso cadastrado com sucesso");
    else
    {
        printf("\nNão foi possível adicionar curso! Código já utilizado");
        free(curso.nome);
        curso.nome = NULL;
    }
}

void cadastrar_disciplina(ArvoreBB_Curso *raiz)
{
    int codigo_curso;

    leia_int("\nCódigo do curso: ", &codigo_curso);

    ArvoreBB_Curso *curso = arvorebb_curso_buscar(raiz, codigo_curso);

    if(curso != NULL)
    {
        Disciplina disciplina;
        disciplina.nome_disciplina = alocar_str(50);

        leia_int("\nCódigo da disciplina: ", &disciplina.codigo_disciplina);
        leia_str("Nome da disciplina: ", disciplina.nome_disciplina);

        disciplina.periodo = 0;
        while(disciplina.periodo <= 0 || disciplina.periodo > curso->info.qt_periodos)
        {
            leia_int("\nPeríodo da disciplina: ", &disciplina.periodo);
            if(disciplina.periodo <= 0 || disciplina.periodo > curso->info.qt_periodos)
                printf("\nErro! Digite um período entre 1 e %d", curso->info.qt_periodos);
        }

        disciplina.carga_horaria = 0;
        while(disciplina.carga_horaria < 30 || disciplina.carga_horaria > 90 || disciplina.carga_horaria % 15 != 0)
        {
            leia_int("Carga horária: ", &disciplina.carga_horaria);
            if(disciplina.carga_horaria < 30 || disciplina.carga_horaria > 90 || disciplina.carga_horaria % 15 != 0)
                printf("\nErro! Digite uma carga horária entre 30 e 90 que seja divisível por 15");
        }

        if(arvorebb_disciplina_add(&(curso->info.arvbb_disciplina), disciplina))
            printf("\nDisciplina cadastrada com sucesso");
        else
        {
            printf("\nNão foi possível adicionar disciplina! Código já utilizado");
            free(disciplina.nome_disciplina);
            disciplina.nome_disciplina = NULL;
        }
    }
    else
        printf("\nCurso não cadastrado");
}

void cadastrar_matricula(Lista *lista, ArvoreBB_Curso *raiz)
{
    int matricula_aluno;

    leia_int("Matricula do aluno: ", &matricula_aluno);

    Lista *aluno = lista_alunos_buscar(lista, matricula_aluno);
    
    if (aluno != NULL)
    {
        ArvoreBB_Curso *curso = arvorebb_curso_buscar(raiz, aluno->info.codigo_curso);

        int codigo_disciplina;
        leia_int("Código da disciplina: ", &codigo_disciplina);

        ArvoreBB_Disciplina *disciplina;
        disciplina = arvorebb_disciplina_buscar(curso->info.arvbb_disciplina, codigo_disciplina);

        if (disciplina != NULL)
        {
            if(arvorebb_matricula_add(aluno->info.arvbb_matricula, codigo_disciplina))
                printf("\nMatrícula efetuada com sucesso na disciplina %s", disciplina->info.nome_disciplina);
            else
                printf("\nMatrícula já foi realizada anteriormente");
        }
        else
            printf("\nDisciplina inválida");
    }
    else
        printf("\nAluno não encontrado");

}

void cadastrar_notas(Lista *lista)
{
    int matricula_aluno;

    leia_int("\nMatricula do aluno: ", &matricula_aluno);

    Lista *aluno = lista_alunos_buscar(lista, matricula_aluno);
    
    if (aluno != NULL)
    {
        Nota nota;
        leia_int("Código da disciplina: ", &nota.codigo_disciplina);

        if(arvorebb_matricula_remover(&(aluno->info.arvbb_matricula), nota.codigo_disciplina))
        {
            leia_int("Semestre: ", &nota.semestre);
            nota.semestre = -1;
            while(nota.semestre < 0 || nota.semestre > 10)
            {
                leia_float("Nota final: ", &nota.semestre);
                if(nota.semestre < 0 || nota.semestre > 10)
                    printf("\nErro! Digite uma nota válida");
            }
            if(arvorebb_nota_add(&(aluno->info.arvbb_matricula), nota))
                printf("\nNota cadastrada com sucesso");
            else
                printf("\nNão foi possível cadastrar nota");
        }
        else
            printf("\nCódigo inválido");
    }
    else
        printf("\nAluno não encontrado");
}


// /// Remover

// xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na mesma.

// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.


// /// Histórico

// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva nota organizadas pelo período que a disciplina está cadastrada no curso.