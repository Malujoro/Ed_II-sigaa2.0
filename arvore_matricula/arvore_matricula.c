#include <stdio.h>
#include <stdlib.h>
#include "arvore_matricula.h"

Arvore_Matricula *no_aloca()
{
    Arvore_Matricula *no;
    no = (Arvore_Matricula *) malloc(sizeof(Arvore_Matricula));
    
    if(no != NULL)
    {
        printf("Erro ao alocar nó da árvore de matrículas");
        exit(EXIT_FAILURE);
    }

    return no;
}

Arvore_Matricula *no_matricula_cria(int codigo_disciplina)
{
    Arvore_Matricula *no;
    no = no_aloca();

    no->info = codigo_disciplina;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

Arvore_Matricula *arvore_matricula_cria()
{
    return NULL;
}

void arvore_matricula_desaloca(Arvore_Matricula **raiz)
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

void arvore_matricula_add(Arvore_Matricula **raiz, int codigo_disciplina)
{
    if((*raiz) == NULL)
        (*raiz) = no_matricula_cria(codigo_disciplina);
    else
    {
        if(codigo_disciplina < (*raiz)->info)
            arvore_matricula_add(&(*raiz)->esquerdo, codigo_disciplina);
        else
            arvore_matricula_add(&(*raiz)->direito, codigo_disciplina);
    }
}

void arvore_matricula_exibir(Arvore_Matricula *raiz)
{
    if(raiz != NULL)
    {
        arvore_matricula_exibir(raiz->esquerdo);
        printf("%d -> ", raiz->info);
        arvore_matricula_exibir(raiz->direito);
    }
}


Arvore_Matricula *arvore_matricula_remover_no(Arvore_Matricula **raiz)
{
    Arvore_Matricula *no;
    no = (*raiz);

    // Caso de 2 filhos
    if(no->esquerdo != NULL && no->direito != NULL)
    {
        if(no->direito->esquerdo != NULL)
        {
            Arvore_Matricula *aux;
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

Arvore_Matricula *arvore_matricula_remover(Arvore_Matricula **raiz, int codigo_disciplina)
{
    Arvore_Matricula *no;
    no = NULL;

    if((*raiz) != NULL)
    {
        if((*raiz)->info == codigo_disciplina)
            no = arvore_matricula_remover_no(&(*raiz));
        else if (codigo_disciplina < (*raiz)->info)
            no = arvore_matricula_remover(&((*raiz)->esquerdo), codigo_disciplina);
        else if (codigo_disciplina > (*raiz)->info)
            no = arvore_matricula_remover(&((*raiz)->direito), codigo_disciplina);
    }
    
    return no;
}