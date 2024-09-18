#include <stdio.h>
#include <stdlib.h>
#include "arvore_matricula.h"

No_Matricula *no_matricula_cria(int matricula)
{
    No_Matricula *no;
    no = (No_Matricula *) malloc(sizeof(No_Matricula));

    no->info = matricula;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

No_Matricula *arvore_matricula_cria()
{
    return NULL;
}

void arvore_matricula_desaloca(No_Matricula **raiz)
{
    if((*raiz) != NULL)
    {
        if((*raiz)->esquerdo != NULL)
            arvore_matricula_desaloca(&((*raiz)->esquerdo));

        if((*raiz)->direito != NULL)
            arvore_matricula_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvore_matricula_add(No_Matricula **raiz, int matricula)
{
    if((*raiz) == NULL)
        (*raiz) = no_matricula_cria(matricula);
    else
    {
        if(matricula < (*raiz)->info)
            arvore_matricula_add(&(*raiz)->esquerdo, matricula);
        else
            arvore_matricula_add(&(*raiz)->direito, matricula);
    }
}

void arvore_matricula_exibir(No_Matricula *raiz)
{
    if(raiz != NULL)
    {
        arvore_matricula_exibir(raiz->esquerdo);
        printf("%d -> ", raiz->info);
        arvore_matricula_exibir(raiz->direito);
    }
}


No_Matricula *arvore_matricula_remover_no(No_Matricula **raiz)
{
    No_Matricula *no;
    no = (*raiz);

    // Caso de 2 filhos
    if(no->esquerdo != NULL && no->direito != NULL)
    {
        if(no->direito->esquerdo != NULL)
        {
            No_Matricula *aux;
            aux = no->direito;
            while(aux->esquerdo->esquerdo != NULL)
                aux = aux->esquerdo;

            (*raiz) = arvore_matricula_remover_no(&(aux->esquerdo));
        }
        else 
            (*raiz) = arvore_matricula_remover_no(&(no->direito));

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

No_Matricula *arvore_matricula_remover(No_Matricula **raiz, int matricula)
{
    No_Matricula *no;
    no = NULL;

    if((*raiz) != NULL)
    {
        if((*raiz)->info == matricula)
            no = arvore_matricula_remover_no(&(*raiz));
        else if (matricula < (*raiz)->info)
            no = arvore_matricula_remover(&((*raiz)->esquerdo), matricula);
        else if (matricula > (*raiz)->info)
            no = arvore_matricula_remover(&((*raiz)->direito), matricula);
    }
    
    return no;
}