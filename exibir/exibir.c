#include <stdio.h>
#include <stdlib.h>
#include "exibir.h"
#include "../lista_alunos/lista.h"
#include "../arvorebb_matricula/arvorebb_matricula.h"
#include "../arvorebb_disciplina/arvorebb_disciplina.h"
#include "../arvorebb_curso/arvorebb_curso.h"
#include "../arvorebb_notas/arvorebb_notas.h"

// /// Exibir

// vi) Mostrar todos os alunos de um determinado curso.

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

// vii) Mostrar todos os cursos do Campus.
void exibir_todos_cursos(ArvoreBB_Curso *raiz)
{
    arvorebb_curso_exibir(raiz);
}

// viii)Mostrar todas as disciplinas de um determinado curso.

void exibir_disciplinas_do_curso(ArvoreBB_Curso *raiz)
{
    arvorebb_curso_exibir(raiz);
}

// ix) Mostrar todas as disciplinas de um determinado período de um curso.
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


// x) Mostrar todas as disciplinas que um determinado aluno está matriculado

void exibir_disciplinas_do_aluno(Aluno aluno)
{
    arvorebb_matricula_exibir(aluno.arvbb_matricula);
}


// xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.

void exibir_disciplinas_do_periodo_aluno(ArvoreBB_Nota *raiz, int periodo)
{
    if(raiz != NULL)
    {
        exibir_disciplinas_do_periodo_aluno(raiz->esquerdo, periodo);
        if(raiz->info.semestre == periodo)
            printf("Nota: %d", raiz->info.nota_final);
        exibir_disciplinas_do_periodo_aluno(raiz->direito, periodo);
    }
}

// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da disciplina.
void exibir_nota_da_disciplina_aluno(Nota nota)
{
    nota_exibir(nota);
}

// 1) Aluno pode se "rematricular" na matéria?
// 2) Já existe uma função de exibir pra árvore, então seria correto criar uma função que "apenas" a utiliza? (por questões de estética e modularização)