#include <stdio.h>
#include <string.h>
#include "arvore_curso.h"

No_Curso *no_curso_cria(int codigo, char *nome, int qt_per)
{
    No_Curso *no = (No_Curso *)malloc(sizeof(No_Curso)); //v.Aloc

    no->info.cod = codigo;
    no->info.qt_periodos = qt_per;
    no->info.nome = nome;
    no->direito = NULL;
    no->esquerdo = NULL;

    return no;
}

No_Curso *arvore_curso_cria()
{
    return NULL;
}

void arvore_curso_desaloca(No_Curso **raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            desalocar_no_curso(&(*raiz)->esquerdo);

        if ((*raiz)->direito != NULL)
            desalocar_no_curso(&(*raiz)->direito);
        
        free(*raiz);
        *raiz = NULL;
    }
}

void arvore_curso_add(No_Curso **raiz, Curso *info)
{
    if ((*raiz) == NULL)
        (*raiz) = criar_no_curso(info->cod, info->nome, info->qt_periodos);
    else
    {
        if (info->cod < (*raiz)->info.cod)
            add_curso(&(*raiz)->esquerdo, info);
        else
            add_curso(&(*raiz)->direito, info);
    }
}

void exibir_arvore_curso(No_Curso *raiz)
{
    if(raiz != NULL)
    {
        exibir_arvore_curso(raiz->esquerdo);
        printf("%d -> ", raiz->info.cod);
        printf("%d -> ", raiz->info.nome);
        printf("%d -> ", raiz->info.qt_periodos);
        exibir_arvore_curso(raiz->direito);
    }
}

No_Curso *arvore_curso_remover_no(No_Curso **raiz)
{
    No_Curso *no;
    no = (*raiz);

    // Caso de 2 filhos
    if(no->esquerdo != NULL && no->direito != NULL)
    {
        if(no->direito->esquerdo != NULL)
        {
            No_Curso *aux;
            aux = no->direito;
            while(aux->esquerdo->esquerdo != NULL)
                aux = aux->esquerdo;

            (*raiz) = remover_no_curso(&(aux->esquerdo));
        }
        else 
            (*raiz) = remover_no_curso(&(no->direito));

        (*raiz)->esquerdo = no->esquerdo;
        (*raiz)->direito = no->direito;
    }
    // Caso de 1 filho (esquerdo)
    else if(no->esquerdo != NULL)
        (*raiz) = no->esquerdo;
    // Caso de 1 filho (direito)
    else if(no->direito != NULL)
        (*raiz) = no->direito;
    // Caso de nenhum filho
    else
        (*raiz) = NULL;

    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

No_Curso *remover_arvore_curso(No_Curso **raiz, Curso *curso)
{
    No_Curso *no;
    no = NULL;

    if((*raiz) != NULL)
    {
        if((*raiz)->info.cod == curso->cod)
            no = remover_no_curso(&(*raiz));
        else if (curso->cod < (*raiz)->info.cod)
            no = remover_arvore_curso(&((*raiz)->esquerdo), curso);
        else if (curso->cod > (*raiz)->info.cod)
            no = remover_arvore_curso(&((*raiz)->direito), curso);
    }

    return no;
}
