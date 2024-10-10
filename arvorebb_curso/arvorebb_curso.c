#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvorebb_curso.h"

ArvoreBB_Curso *no_curso_aloca()
{
    ArvoreBB_Curso *no;
    no = (ArvoreBB_Curso *)malloc(sizeof(ArvoreBB_Curso));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de curso");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreBB_Curso *no_curso_cria(Curso curso)
{
    ArvoreBB_Curso *no = (ArvoreBB_Curso *)malloc(sizeof(ArvoreBB_Curso));

    no->info = curso;
    no->direito = NULL;
    no->esquerdo = NULL;
    
    return no;
}

// TODO talvez remover a função de criar
ArvoreBB_Curso *arvorebb_curso_cria()
{
    return NULL;
}

void arvorebb_curso_desaloca(ArvoreBB_Curso **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_curso_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_curso_desaloca(&((*raiz)->direito));
        
        free((*raiz)->info.nome);
        (*raiz)->info.nome = NULL;

        free(*raiz);
        *raiz = NULL;
    }
}

int arvorebb_curso_add(ArvoreBB_Curso **raiz, Curso info)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_curso_cria(info);
    else
    {
        if (info.cod < (*raiz)->info.cod)
            inseriu = arvorebb_curso_add(&(*raiz)->esquerdo, info);
        else if (info.cod > (*raiz)->info.cod)
            inseriu = arvorebb_curso_add(&(*raiz)->direito, info);
        else
            inseriu = 0;
    }

    return inseriu;
}

ArvoreBB_Curso *arvorebb_curso_buscar(ArvoreBB_Curso *raiz, int codigo)
{
    ArvoreBB_Curso *retorno;

    if(raiz != NULL)
    {
        if(codigo == raiz->info.cod)
            retorno = raiz;
        else if(codigo < raiz->info.cod)
            retorno = arvorebb_curso_buscar(raiz->esquerdo, codigo);
        else if(codigo > raiz->info.cod)
            retorno = arvorebb_curso_buscar(raiz->direito, codigo);
    }
    else
        retorno = NULL;
    
    return retorno;
}

void arvorebb_curso_exibir(ArvoreBB_Curso *raiz)
{
    if(raiz != NULL)
    {
        arvorebb_curso_exibir(raiz->esquerdo);
        printf("Código: %d | Nome: %s | Períodos: %d\n", raiz->info.cod, raiz->info.nome, raiz->info.qt_periodos);
        arvorebb_curso_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreBB_Curso *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreBB_Curso *endereco_filho_unico(ArvoreBB_Curso *raiz)
{
    ArvoreBB_Curso *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreBB_Curso *menor_filho(ArvoreBB_Curso *raiz)
{
    ArvoreBB_Curso *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvorebb_curso_remover(ArvoreBB_Curso **raiz, int codigo)
{
    ArvoreBB_Curso *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.cod == codigo)
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
                arvorebb_curso_remover(&((*raiz)->direito), endereco_menor_filho->info.cod);
            }
        }
        else if (codigo < (*raiz)->info.cod)
            removeu = arvorebb_curso_remover(&((*raiz)->esquerdo), codigo);
        else if (codigo > (*raiz)->info.cod)
            removeu = arvorebb_curso_remover(&((*raiz)->direito), codigo);
    }
    else
        removeu = 0;

    return removeu;
}

// int main()
// {
//     for(int cont = 0; cont < 10; cont ++)
//     {

//         ArvoreBB_Curso *raiz = arvorebb_curso_cria();
//         Curso curso;

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};
        
//         char **nomes = (char **) malloc(sizeof(char *) * quant);
//         for(int i = 0; i < quant; i++)
//         {
//             nomes[i] = (char *) malloc(sizeof(char) * 100);
//             scanf("%s", nomes[i]);
//             while(getchar() != '\n');
//         }

//         Curso cursos[10];

//         for(int i = 0; i < quant; i++)
//         {
//             curso.cod = mat[i];
//             curso.nome = nomes[mat[i]];
//             curso.qt_periodos = mat[i] + 10;

//             cursos[i] = curso;
//             arvorebb_curso_add(&raiz, curso);
//         }

//         if(cont == 0)
//         {
//             printf("Árvore original\n");
//             arvorebb_curso_exibir(raiz);
//             printf("\n");
//         }

//         int removeu = arvorebb_curso_remover(&raiz, cursos[cont].cod);
//         if(removeu)
//             printf("\nÁrvore após remover %d\n", cursos[cont].cod);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvorebb_curso_exibir(raiz); 

//         arvorebb_curso_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }