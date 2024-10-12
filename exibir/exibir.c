#include <stdio.h>
#include <stdlib.h>
#include "exibir.h"
#include "../lista_alunos/lista.h"
#include "../arvorebb_matricula/arvorebb_matricula.h"
#include "../arvorebb_disciplina/arvorebb_disciplina.h"
#include "../arvorebb_curso/arvorebb_curso.h"
#include "../arvorebb_notas/arvorebb_notas.h"

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

void exibir_todos_cursos(ArvoreBB_Curso *raiz)
{
    arvorebb_curso_exibir(raiz);
}

void exibir_disciplinas_do_curso(ArvoreBB_Curso *raiz)
{
    arvorebb_disciplina_exibir(raiz->info.arvbb_disciplina);
}

void exibir_disciplinas_do_periodo_curso(ArvoreBB_Disciplina *raiz, int periodo)
{
    if(raiz != NULL)
    {
        exibir_disciplinas_do_periodo_curso(raiz->esquerdo, periodo);
        if(raiz->info.periodo == periodo)
            disciplina_exibir(raiz->info);
        exibir_disciplinas_do_periodo_curso(raiz->direito, periodo);
    }
}

void exibir_disciplinas_do_aluno(Aluno aluno)
{
    arvorebb_matricula_exibir(aluno.arvbb_matricula);
}

void exibir_disciplinas_do_periodo_aluno(ArvoreBB_Nota *raiz, int periodo)
{
    if(raiz != NULL)
    {
        exibir_disciplinas_do_periodo_aluno(raiz->esquerdo, periodo);
        if(raiz->info.semestre == periodo)
            printf("Nota: %f", raiz->info.nota_final);
        exibir_disciplinas_do_periodo_aluno(raiz->direito, periodo);
    }
}

void exibir_nota_da_disciplina_aluno(Nota nota)
{
    nota_exibir(nota);
}

// /// Histórico

// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva nota organizadas pelo período que a disciplina está cadastrada no curso.

static void arvorebb_nota_preenche_vetor(ArvoreBB_Nota *raiz, Nota *vetor, int *tam)
{
    if(raiz != NULL)
    {
        vetor[*tam] = raiz->info;
        (*tam)++;
        arvorebb_nota_preenche_vetor(raiz->esquerdo, vetor, tam);
        arvorebb_nota_preenche_vetor(raiz->direito, vetor, tam);
    }
}

// TODO Buscar maneira mais eficiente de se fazer
void exibir_historico(Aluno aluno, ArvoreBB_Curso *raiz)
{
    ArvoreBB_Curso *curso;
    curso = arvorebb_curso_buscar(raiz, aluno.codigo_curso);

    printf("\nNome do curso: %s", curso->info.nome);

    int quant_notas = arvorebb_nota_total_nos(aluno.arvbb_nota);
    if(quant_notas > 0)
    {
        int tam = 0;
        Nota notas[quant_notas];

        arvorebb_nota_preenche_vetor(aluno.arvbb_nota, notas, &tam);

        Disciplina disciplinas[curso->info.qt_periodos][quant_notas];
        int posicoes[curso->info.qt_periodos][quant_notas];

        int tamanhos[curso->info.qt_periodos];
        for(int i = 0; i < curso->info.qt_periodos; i++)
            tamanhos[i] = 0;

        for(int i = 0; i < quant_notas; i++)
        {
            ArvoreBB_Disciplina *disciplina; 
            disciplina = arvorebb_disciplina_buscar(curso->info.arvbb_disciplina, notas[i].codigo_disciplina);

            int indice = disciplina->info.periodo - 1;
            disciplinas[indice][tamanhos[indice]] = disciplina->info;
            posicoes[indice][tamanhos[indice]] = i;
            tamanhos[indice]++;
        }

        for(int i = 0; i < curso->info.qt_periodos; i++)
        {
            printf("\n%dº período: ", i+1);
            for(int j = 0; j < tamanhos[i]; j++)
            {
                printf("Disciplina: %s | Nota: %.1f", disciplinas[i][j].nome_disciplina, notas[posicoes[i][j]].nota_final);
            }
        }
    }
    else
        printf("\nNão há matrículas cadastradas\n");
}