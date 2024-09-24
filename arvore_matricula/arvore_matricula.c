#include <stdio.h>
#include <stdlib.h>
#include "arvore_matricula.h"

Arvore_Matricula *no_matricula_aloca()
{
    Arvore_Matricula *no;
    no = (Arvore_Matricula *)malloc(sizeof(Arvore_Matricula));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de matrículas");
        exit(EXIT_FAILURE);
    }

    return no;
}

Arvore_Matricula *no_matricula_cria(int codigo_disciplina)
{
    Arvore_Matricula *no;
    no = no_matricula_aloca();

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
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvore_matricula_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvore_matricula_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

int arvore_matricula_add(Arvore_Matricula **raiz, int codigo_disciplina)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_matricula_cria(codigo_disciplina);
    else
    {
        if (codigo_disciplina < (*raiz)->info)
            inseriu = arvore_matricula_add(&((*raiz)->esquerdo), codigo_disciplina);
        else if (codigo_disciplina > (*raiz)->info)
            inseriu = arvore_matricula_add(&((*raiz)->direito), codigo_disciplina);
        else
            inseriu = 0;
    }

    return inseriu;
}

void arvore_matricula_exibir(Arvore_Matricula *raiz)
{
    if (raiz != NULL)
    {
        arvore_matricula_exibir(raiz->esquerdo);
        printf("%d -> ", raiz->info);
        arvore_matricula_exibir(raiz->direito);
    }
}

Arvore_Matricula *endereco_filho(Arvore_Matricula *raiz)
{
    Arvore_Matricula *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

Arvore_Matricula **menor_filho_direita(Arvore_Matricula **raiz)
{
    Arvore_Matricula **aux;
    aux = &((*raiz)->direito);

    while ((*aux)->esquerdo != NULL)
        aux = &((*aux)->esquerdo);

    return aux;
}

Arvore_Matricula *arvore_matricula_remover_no(Arvore_Matricula **raiz, int codigo_disciplina)
{
    Arvore_Matricula *no_removido;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info == codigo_disciplina)
        {
            Arvore_Matricula *aux;

            // Caso de nenhum filho
            if (((*raiz)->esquerdo == NULL) && ((*raiz)->direito == NULL))
                aux = NULL;
            // Caso de 1 filho
            else if (((*raiz)->esquerdo == NULL) || ((*raiz)->direito == NULL))
                aux = endereco_filho(*raiz);
            // Caso de 2 filhos
            else
            {
                Arvore_Matricula **filho;
                filho = menor_filho_direita(raiz);
                aux = *filho;
                *filho = endereco_filho(aux);
                aux->esquerdo = (*raiz)->esquerdo;
                aux->direito = (*raiz)->direito;
            }

            no_removido = *raiz;
            *raiz = aux;
        }
        else if (codigo_disciplina < (*raiz)->info)
            no_removido = arvore_matricula_remover_no(&((*raiz)->esquerdo), codigo_disciplina);
        else if (codigo_disciplina > (*raiz)->info)
            no_removido = arvore_matricula_remover_no(&((*raiz)->direito), codigo_disciplina);
    }
    else
        no_removido = NULL;

    return no_removido;
}

int main()
{
    for (int cont = 0; cont < 10; cont++)
    {

        Arvore_Matricula *raiz = arvore_matricula_cria();

        int quant = 10;
        int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

        for (int i = 0; i < quant; i++)
            arvore_matricula_add(&raiz, mat[i]);

        if (cont == 0)
        {
            printf("Árvore original\n");
            arvore_matricula_exibir(raiz);
            printf("\n");
        }

        Arvore_Matricula *no_removido = arvore_matricula_remover_no(&raiz, cont);
        if (no_removido != NULL)
            printf("\nÁrvore após remover %d\n", no_removido->info);
        else
            printf("\nÁrvore após remover [Elemento não encontrado]\n");
        arvore_matricula_exibir(raiz);

        arvore_matricula_desaloca(&raiz);
        printf("\n\n");
    }
    return 0;
}