#include <stdio.h>
#include <stdlib.h>
#include "arvorebb_matricula.h"

ArvoreBB_Matricula *no_matricula_aloca()
{
    ArvoreBB_Matricula *no;
    no = (ArvoreBB_Matricula *)malloc(sizeof(ArvoreBB_Matricula));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de matrículas");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreBB_Matricula *no_matricula_cria(int codigo_matricula)
{
    ArvoreBB_Matricula *no;
    no = no_matricula_aloca();

    no->info = codigo_matricula;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

// TODO talvez remover a função de criar
ArvoreBB_Matricula *arvorebb_matricula_cria()
{
    return NULL;
}

void arvorebb_matricula_desaloca(ArvoreBB_Matricula **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_matricula_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_matricula_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

int arvorebb_matricula_add(ArvoreBB_Matricula **raiz, int codigo_matricula)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_matricula_cria(codigo_matricula);
    else
    {
        if (codigo_matricula < (*raiz)->info)
            inseriu = arvorebb_matricula_add(&((*raiz)->esquerdo), codigo_matricula);
        else if (codigo_matricula > (*raiz)->info)
            inseriu = arvorebb_matricula_add(&((*raiz)->direito), codigo_matricula);
        else
            inseriu = 0;
    }

    return inseriu;
}

void arvorebb_matricula_exibir(ArvoreBB_Matricula *raiz)
{
    if (raiz != NULL)
    {
        printf("%d | ", raiz->info);
        arvorebb_matricula_exibir(raiz->esquerdo);
        arvorebb_matricula_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreBB_Matricula *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreBB_Matricula *endereco_filho_unico(ArvoreBB_Matricula *raiz)
{
    ArvoreBB_Matricula *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreBB_Matricula *menor_filho(ArvoreBB_Matricula *raiz)
{
    ArvoreBB_Matricula *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvorebb_matricula_remover(ArvoreBB_Matricula **raiz, int codigo_matricula)
{
    ArvoreBB_Matricula *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info == codigo_matricula)
        {
            if (no_folha(*raiz))
            {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            }
            else if ((endereco_filho = endereco_filho_unico(*raiz)) != NULL)
            {
                aux = *raiz;
                *raiz = endereco_filho;
                free(aux);
            }
            else
            {
                endereco_menor_filho = menor_filho((*raiz)->direito);
                (*raiz)->info = endereco_menor_filho->info;
                arvorebb_matricula_remover(&((*raiz)->direito), endereco_menor_filho->info);
            }
        }
        else if (codigo_matricula < (*raiz)->info)
            removeu = arvorebb_matricula_remover(&((*raiz)->esquerdo), codigo_matricula);
        else if (codigo_matricula > (*raiz)->info)
            removeu = arvorebb_matricula_remover(&((*raiz)->direito), codigo_matricula);
    }
    else
        removeu = 0;

    return removeu;
}

// int main()
// {
//     for (int cont = 0; cont < 10; cont++)
//     {

//         ArvoreBB_Matricula *raiz = arvorebb_matricula_cria();

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

//         for (int i = 0; i < quant; i++)
//             arvorebb_matricula_add(&raiz, mat[i]);

//         if (cont == 0)
//         {
//             printf("Árvore original\n");
//             arvorebb_matricula_exibir(raiz);
//             printf("\n");
//         }

//         int removeu = arvorebb_matricula_remover(&raiz, cont);
//         if (removeu)
//             printf("\nÁrvore após remover %d\n", cont);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvorebb_matricula_exibir(raiz);

//         arvorebb_matricula_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }