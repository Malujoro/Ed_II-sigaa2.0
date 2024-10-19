#include <stdio.h>
#include <stdlib.h>
#include "exibirbb.h"
#include "../lista_alunos/listabb.h"
#include "../arvorebb/arvorebb.h"

void exibir_alunos_do_curso(Lista *lista, int codigo_curso)
{
    Lista *aux = lista;
    while (aux!= NULL)
    {
        if(aux->info.codigo_curso == codigo_curso)
            aluno_exibir(aux->info);
    
        aux = aux->proximo;
    }
}

void exibir_todos_cursos(ArvoreBB *raiz_curso)
{
    arvorebb_curso_exibir(raiz_curso);
}

void exibir_disciplinas_do_curso(ArvoreBB *raiz_curso)
{
    arvorebb_disciplina_exibir(raiz_curso->info.curso.arvbb_disciplina);
}

void exibir_disciplinas_do_periodo_curso(ArvoreBB *raiz_disciplina, int periodo)
{
    if(raiz_disciplina != NULL)
    {
        exibir_disciplinas_do_periodo_curso(raiz_disciplina->esquerdo, periodo);
        if(raiz_disciplina->info.disciplina.periodo == periodo)
            disciplina_exibir(raiz_disciplina->info.disciplina);
        exibir_disciplinas_do_periodo_curso(raiz_disciplina->direito, periodo);
    }
}

void exibir_disciplinas_do_aluno(Aluno aluno)
{
    arvorebb_exibir(aluno.arvbb_matricula);
}

void exibir_disciplinas_do_periodo_aluno(ArvoreBB *raiz_nota, int periodo)
{
    if(raiz_nota != NULL)
    {
        exibir_disciplinas_do_periodo_aluno(raiz_nota->esquerdo, periodo);
        if(raiz_nota->info.nota.semestre == periodo)
            printf("Nota: %.1f", raiz_nota->info.nota.nota_final);
        exibir_disciplinas_do_periodo_aluno(raiz_nota->direito, periodo);
    }
}

void exibir_nota_da_disciplina_aluno(Aluno aluno, int codigo, ArvoreBB *raiz_curso)
{
    ArvoreBB *nota, *curso, *disciplina;
    nota = arvorebb_buscar(aluno.arvbb_nota, codigo);
    if(nota != NULL)
    {
        curso = arvorebb_buscar(raiz_curso, aluno.codigo_curso);
        disciplina = arvorebb_buscar(curso->info.curso.arvbb_disciplina, codigo);
        nota_exibir(nota->info.nota);
        printf("Período do curso: %d | Carga horária: %d", disciplina->info.disciplina.periodo, disciplina->info.disciplina.carga_horaria);
    }
    else
        printf("Disciplina com Nota não encontrada");
}

static void arvorebb_nota_preenche_vetor(ArvoreBB *raiz_nota, Nota *vetor, int *tam)
{
    if(raiz_nota != NULL)
    {
        vetor[*tam] = raiz_nota->info.nota;
        (*tam)++;
        arvorebb_nota_preenche_vetor(raiz_nota->esquerdo, vetor, tam);
        arvorebb_nota_preenche_vetor(raiz_nota->direito, vetor, tam);
    }
}

void exibir_historico(Aluno aluno, ArvoreBB *raiz_curso)
{
    ArvoreBB *curso;
    curso = arvorebb_buscar(raiz_curso, aluno.codigo_curso);

    printf("\nNome do curso: [%s]\n", curso->info.curso.nome);

    int quant_notas = arvorebb_total_nos(aluno.arvbb_nota);
    if(quant_notas > 0)
    {
        int tam = 0;
        Nota notas[quant_notas];

        arvorebb_nota_preenche_vetor(aluno.arvbb_nota, notas, &tam);

        Disciplina disciplinas[curso->info.curso.qt_periodos][quant_notas];
        int posicoes[curso->info.curso.qt_periodos][quant_notas];

        int tamanhos[curso->info.curso.qt_periodos];
        for(int i = 0; i < curso->info.curso.qt_periodos; i++)
            tamanhos[i] = 0;

        for(int i = 0; i < quant_notas; i++)
        {
            ArvoreBB *disciplina; 
            disciplina = arvorebb_buscar(curso->info.curso.arvbb_disciplina, notas[i].codigo_disciplina);

            int indice = disciplina->info.disciplina.periodo - 1;
            disciplinas[indice][tamanhos[indice]] = disciplina->info.disciplina;
            posicoes[indice][tamanhos[indice]] = i;
            tamanhos[indice]++;
        }

        for(int i = 0; i < curso->info.curso.qt_periodos; i++)
        {
            printf("\n%dº período: ", i+1);
            for(int j = 0; j < tamanhos[i]; j++)
                printf("\nDisciplina: %s | Nota: %.1f", disciplinas[i][j].nome_disciplina, notas[posicoes[i][j]].nota_final);
        }
    }
    else
        printf("\nNão há matrículas cadastradas\n");
}