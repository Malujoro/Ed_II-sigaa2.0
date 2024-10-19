#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

ArvoreBB *no_aloca()
{
    ArvoreBB *no;
    no = (ArvoreBB *)malloc(sizeof(ArvoreBB));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de matrículas");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreBB *no_cria(union Data info)
{
    ArvoreBB *no;
    no = no_aloca();

    no->info = info;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

ArvoreBB *arvorebb_cria()
{
    return NULL;
}

void arvorebb_desaloca(ArvoreBB **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvorebb_curso_desaloca(ArvoreBB **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_curso_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_curso_desaloca(&((*raiz)->direito));
        
        free((*raiz)->info.curso.nome);
        (*raiz)->info.curso.nome = NULL;

        arvorebb_disciplina_desaloca(&((*raiz)->info.curso.arvbb_disciplina));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvorebb_disciplina_desaloca(ArvoreBB **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_disciplina_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_disciplina_desaloca(&((*raiz)->direito));

        free((*raiz)->info.disciplina.nome_disciplina);
        (*raiz)->info.disciplina.nome_disciplina = NULL;

        free(*raiz);
        *raiz = NULL;
    }
}

int arvorebb_add(ArvoreBB **raiz, union Data info)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_cria(info);
    else
    {
        if (info.matricula < (*raiz)->info.matricula)
            inseriu = arvorebb_add(&((*raiz)->esquerdo), info);
        else if (info.matricula > (*raiz)->info.matricula)
            inseriu = arvorebb_add(&((*raiz)->direito), info);
        else
            inseriu = 0;
    }

    return inseriu;
}

ArvoreBB *arvorebb_buscar(ArvoreBB *raiz, int codigo)
{
    ArvoreBB *retorno;

    if(raiz != NULL)
    {
        if(codigo == raiz->info.matricula)
            retorno = raiz;
        else if(codigo < raiz->info.matricula)
            retorno = arvorebb_buscar(raiz->esquerdo, codigo);
        else if(codigo > raiz->info.matricula)
            retorno = arvorebb_buscar(raiz->direito, codigo);
    }
    else
        retorno = NULL;
    
    return retorno;
}

void arvorebb_exibir(ArvoreBB *raiz)
{
    if (raiz != NULL)
    {
        arvorebb_exibir(raiz->esquerdo);
        printf("%d | ", raiz->info.matricula);
        arvorebb_exibir(raiz->direito);
    }
}

void arvorebb_curso_exibir(ArvoreBB *raiz)
{
    if(raiz != NULL)
    {
        arvorebb_curso_exibir(raiz->esquerdo);
        printf("Código: %d | Nome: %s | Períodos: %d\n", raiz->info.curso.cod, raiz->info.curso.nome, raiz->info.curso.qt_periodos);
        arvorebb_curso_exibir(raiz->direito);
    }
}

void disciplina_exibir(Disciplina disciplina)
{
    printf("Código: %d | Nome: %s | Período: %d | Carga horária: %d\n", disciplina.codigo_disciplina,
    disciplina.nome_disciplina, disciplina.periodo, disciplina.carga_horaria);
}

void arvorebb_disciplina_exibir(ArvoreBB *raiz)
{
    if (raiz != NULL)
    {
        arvorebb_disciplina_exibir(raiz->esquerdo);
        disciplina_exibir(raiz->info.disciplina);
        arvorebb_disciplina_exibir(raiz->direito);
    }
}

void nota_exibir(Nota nota)
{
    printf("Código: %d | Semestre: %d | Nota final: %.1f\n", nota.codigo_disciplina, nota.semestre, nota.nota_final);
}

void arvorebb_nota_exibir(ArvoreBB *raiz)
{
    if (raiz != NULL)
    {
        arvorebb_nota_exibir(raiz->esquerdo);
        nota_exibir(raiz->info.nota);
        arvorebb_nota_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreBB *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreBB *endereco_filho_unico(ArvoreBB *raiz)
{
    ArvoreBB *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreBB *menor_filho(ArvoreBB *raiz)
{
    ArvoreBB *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvorebb_remover(ArvoreBB **raiz, int codigo)
{
    ArvoreBB *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.matricula == codigo)
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
                arvorebb_remover(&((*raiz)->direito), endereco_menor_filho->info.matricula);
            }
        }
        else if (codigo < (*raiz)->info.matricula)
            removeu = arvorebb_remover(&((*raiz)->esquerdo), codigo);
        else if (codigo > (*raiz)->info.matricula)
            removeu = arvorebb_remover(&((*raiz)->direito), codigo);
    }
    else
        removeu = 0;

    return removeu;
}

int arvorebb_total_nos(ArvoreBB *raiz)
{
    int quant = 0;
    if(raiz != NULL)
    {
        quant += 1;
        quant += arvorebb_total_nos(raiz->esquerdo);
        quant += arvorebb_total_nos(raiz->direito);
    }
    return quant;
}

// int main()
// {
//     for (int cont = 0; cont < 10; cont++)
//     {
//         ArvoreBB *raiz = arvorebb_cria();

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};
//         union Data info;

//         for (int i = 0; i < quant; i++)
//         {
//             info.matricula = mat[i];
//             arvorebb_add(&raiz, info);
//         }

//         if (cont == 0)
//         {
//             printf("Árvore original\n");
//             arvorebb_exibir(raiz);
//             printf("\n");
//         }

//         int removeu = arvorebb_remover(&raiz, cont);
//         if (removeu)
//             printf("\nÁrvore após remover %d\n", cont);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvorebb_exibir(raiz);

//         arvorebb_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }