#include <stdio.h>
#include <stdlib.h>
#include "arvore_matricula.h"

No_Matricula *no_matricula_cria(int matricula)
{
    No_Matricula *no = (No_Matricula *) malloc(sizeof(No_Matricula));
    no->info = matricula;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

Arvore_Matricula *arvore_matricula_cria()
{
    Arvore_Matricula *arvore = (Arvore_Matricula *) malloc(sizeof(Arvore_Matricula));
    arvore->raiz = NULL;
    return arvore;
}

void no_matricula_desaloca(No_Matricula **no)
{
    if(no != NULL)
    {
        if((*no)->esquerdo != NULL)
            no_matricula_desaloca(&((*no)->esquerdo));

        if((*no)->direito != NULL)
            no_matricula_desaloca(&((*no)->direito));
        free(*no);
        *no = NULL;
    }
}

void arvore_matricula_desaloca(Arvore_Matricula **arvore)
{
    no_matricula_desaloca(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

void arvore_matricula_add_no(No_Matricula *raiz, No_Matricula *no)
{
    if(raiz != NULL)
    {
        if(no->info < raiz->info)
        {
            if(raiz->esquerdo == NULL)
                raiz->esquerdo = no;
            else
                arvore_matricula_add_no(raiz->esquerdo, no);
        }
        else
        {
            if(raiz->direito == NULL)
                raiz->direito = no;
            else
                arvore_matricula_add_no(raiz->direito, no);
        }
    }
}

void arvore_matricula_add(Arvore_Matricula *arvore, int matricula)
{
    No_Matricula *no = no_matricula_cria(matricula);

    if(arvore->raiz == NULL)
        arvore->raiz = no;
    else
        arvore_matricula_add_no(arvore->raiz, no);
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


No_Matricula *arvore_matricula_remover_no_aux(No_Matricula **raiz)
{
    No_Matricula *no = (*raiz);

    // Caso de 2 filhos
    if(no->esquerdo != NULL && no->direito != NULL)
    {
        if(no->direito->esquerdo != NULL)
        {
            No_Matricula *aux = no->direito;
            while(aux->esquerdo->esquerdo != NULL)
                aux = aux->esquerdo;

            (*raiz) = arvore_matricula_remover_no_aux(&(aux->esquerdo));
        }
        else 
            (*raiz) = arvore_matricula_remover_no_aux(&(no->direito));

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

No_Matricula *arvore_matricula_remover_no(No_Matricula *raiz, int matricula)
{
    No_Matricula *no = NULL;

    if(raiz != NULL)
    {
        if(matricula < raiz->info && raiz->esquerdo != NULL)
        {
            if(matricula == raiz->esquerdo->info)
                no = arvore_matricula_remover_no_aux(&(raiz->esquerdo));
            else
                no = arvore_matricula_remover_no(raiz->esquerdo, matricula);
        }
        else if(matricula > raiz->info && raiz->direito != NULL)
        {
            if(matricula == raiz->direito->info)
                no = arvore_matricula_remover_no_aux(&(raiz->direito));
            else
                no = arvore_matricula_remover_no(raiz->direito, matricula);
        }
    }

    return no;
}

No_Matricula *arvore_matricula_remover(Arvore_Matricula *arvore, int matricula)
{
    No_Matricula *no = NULL;

    if(arvore->raiz != NULL)
    {
        if(arvore->raiz->info == matricula)
            no = arvore_matricula_remover_no_aux(&(arvore->raiz));
        else
            no = arvore_matricula_remover_no(arvore->raiz, matricula);
    }
    
    return no;
}