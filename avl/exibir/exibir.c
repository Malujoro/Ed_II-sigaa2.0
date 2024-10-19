#include <stdio.h>
#include <stdlib.h>
#include "exibir.h"
#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"

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

void exibir_todos_cursos(ArvoreAVL *raiz_curso)
{
    arvoreavl_curso_exibir(raiz_curso);
}

void exibir_disciplinas_do_curso(ArvoreAVL *raiz_curso)
{
    arvoreavl_disciplina_exibir(raiz_curso->info.curso.arvavl_disciplina);
}

void exibir_disciplinas_do_periodo_curso(ArvoreAVL *raiz_disciplina, int periodo)
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
    arvoreavl_exibir(aluno.arvavl_matricula);
}

void exibir_disciplinas_do_periodo_aluno(ArvoreAVL *raiz_nota, int periodo)
{
    if(raiz_nota != NULL)
    {
        exibir_disciplinas_do_periodo_aluno(raiz_nota->esquerdo, periodo);
        if(raiz_nota->info.nota.semestre == periodo)
            printf("Nota: %.1f", raiz_nota->info.nota.nota_final);
        exibir_disciplinas_do_periodo_aluno(raiz_nota->direito, periodo);
    }
}

void exibir_nota_da_disciplina_aluno(Aluno aluno, int codigo, ArvoreAVL *raiz_curso)
{
    ArvoreAVL *nota, *curso, *disciplina;
    nota = arvoreavl_buscar(aluno.arvavl_nota, codigo);
    if(nota != NULL)
    {
        curso = arvoreavl_buscar(raiz_curso, aluno.codigo_curso);
        disciplina = arvoreavl_buscar(curso->info.curso.arvavl_disciplina, codigo);
        nota_exibir(nota->info.nota);
        printf("Período do curso: %d | Carga horária: %d", disciplina->info.disciplina.periodo, disciplina->info.disciplina.carga_horaria);
    }
    else
        printf("Disciplina com Nota não encontrada");
}

static void arvoreavl_nota_preenche_vetor(ArvoreAVL *raiz_nota, Nota *vetor, int *tam)
{
    if(raiz_nota != NULL)
    {
        vetor[*tam] = raiz_nota->info.nota;
        (*tam)++;
        arvoreavl_nota_preenche_vetor(raiz_nota->esquerdo, vetor, tam);
        arvoreavl_nota_preenche_vetor(raiz_nota->direito, vetor, tam);
    }
}

void exibir_historico(Aluno aluno, ArvoreAVL *raiz_curso)
{
    ArvoreAVL *curso;
    curso = arvoreavl_buscar(raiz_curso, aluno.codigo_curso);

    printf("\nNome do curso: [%s]\n", curso->info.curso.nome);

    int quant_notas = arvoreavl_total_nos(aluno.arvavl_nota);
    if(quant_notas > 0)
    {
        int tam = 0;
        Nota notas[quant_notas];

        arvoreavl_nota_preenche_vetor(aluno.arvavl_nota, notas, &tam);

        Disciplina disciplinas[curso->info.curso.qt_periodos][quant_notas];
        int posicoes[curso->info.curso.qt_periodos][quant_notas];

        int tamanhos[curso->info.curso.qt_periodos];
        for(int i = 0; i < curso->info.curso.qt_periodos; i++)
            tamanhos[i] = 0;

        for(int i = 0; i < quant_notas; i++)
        {
            ArvoreAVL *disciplina; 
            disciplina = arvoreavl_buscar(curso->info.curso.arvavl_disciplina, notas[i].codigo_disciplina);

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