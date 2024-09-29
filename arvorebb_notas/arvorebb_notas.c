#include <stdio.h>
#include <stdlib.h>
#include "arvorebb_notas.h"

ArvoreBB_Nota *no_nota_aloca()
{
    ArvoreBB_Nota *no;
    no = (ArvoreBB_Nota *)malloc(sizeof(ArvoreBB_Nota));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de notas");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreBB_Nota *no_nota_cria(Nota nota)
{
    ArvoreBB_Nota *no;
    no = no_nota_aloca();

    no->info = nota;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

ArvoreBB_Nota *arvorebb_nota_cria()
{
    return NULL;
}

void arvorebb_nota_desaloca(ArvoreBB_Nota **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_nota_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_nota_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

int arvorebb_nota_add(ArvoreBB_Nota **raiz, Nota nota)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_nota_cria(nota);
    else
    {
        if (nota.codigo_disciplina < (*raiz)->info.codigo_disciplina)
            arvorebb_nota_add(&(*raiz)->esquerdo, nota);
        else if (nota.codigo_disciplina > (*raiz)->info.codigo_disciplina)
            arvorebb_nota_add(&(*raiz)->direito, nota);
        else
            inseriu = 0;
    }

    return inseriu;
}

ArvoreBB_Nota *arvorebb_nota_buscar(ArvoreBB_Nota *raiz, int codigo)
{
    ArvoreBB_Nota *retorno;

    if(raiz != NULL)
    {
        if(codigo == raiz->info.codigo_disciplina)
            retorno = raiz;
        else if(codigo < raiz->info.codigo_disciplina)
            retorno = arvorebb_nota_buscar(raiz->esquerdo, codigo);
        else if(codigo > raiz->info.codigo_disciplina)
            retorno = arvorebb_nota_buscar(raiz->direito, codigo);
    }
    else
        retorno = NULL;
    
    return retorno;
}

void nota_exibir(Nota nota)
{
    printf("Código: %d | Semestre: %d | Nota final: %.1f\n", nota.codigo_disciplina, nota.semestre, nota.nota_final);
}

void arvorebb_nota_exibir(ArvoreBB_Nota *raiz)
{
    if (raiz != NULL)
    {
        arvorebb_nota_exibir(raiz->esquerdo);
        nota_exibir(raiz->info);
        arvorebb_nota_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreBB_Nota *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreBB_Nota *endereco_filho_unico(ArvoreBB_Nota *raiz)
{
    ArvoreBB_Nota *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreBB_Nota *menor_filho(ArvoreBB_Nota *raiz)
{
    ArvoreBB_Nota *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvorebb_nota_remover(ArvoreBB_Nota **raiz, int codigo_disciplina)
{
    ArvoreBB_Nota *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.codigo_disciplina == codigo_disciplina)
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
                arvorebb_nota_remover(&((*raiz)->direito), endereco_menor_filho->info.codigo_disciplina);
            }
        }
        else if (codigo_disciplina < (*raiz)->info.codigo_disciplina)
            removeu = arvorebb_nota_remover(&((*raiz)->esquerdo), codigo_disciplina);
        else if (codigo_disciplina > (*raiz)->info.codigo_disciplina)
            removeu = arvorebb_nota_remover(&((*raiz)->direito), codigo_disciplina);
    }
    else
        removeu = 0;

    return removeu;
}

// int main()
// {
//     for(int cont = 0; cont < 10; cont ++)
//     {

//         ArvoreBB_Nota *raiz = arvorebb_nota_cria();
//         Nota nota;

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};
//         Nota notas[10];

//         for(int i = 0; i < quant; i++)
//         {
//             nota.codigo_disciplina = mat[i];
//             nota.semestre = mat[i] * 10;
//             nota.nota_final = mat[i] * 100;
//             nota.carga_horaria = mat[i] * 1000;

//             notas[i] = nota;
//             arvorebb_nota_add(&raiz, nota);
//         }

//         if(cont == 0)
//         {
//             printf("Árvore original\n");
//             arvorebb_nota_exibir(raiz);
//             printf("\n");
//         }

//         int removeu = arvorebb_nota_remover(&raiz, notas[cont].codigo_disciplina);
//         if(removeu)
//             printf("\nÁrvore após remover %d\n", notas[cont].codigo_disciplina);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvorebb_nota_exibir(raiz);

//         arvorebb_nota_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }