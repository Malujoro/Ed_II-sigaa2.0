#include <stdio.h>
#include <stdlib.h>
#include "arvore_matricula.h"

Arvore_Matricula *no_matricula_aloca()
{
    Arvore_Matricula *no;
    no = (Arvore_Matricula *) malloc(sizeof(Arvore_Matricula));
    
    if(!no)
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

// int main()
// {
//     for(int cont = 0; cont < 10; cont ++)
//     {

//         Arvore_Matricula *raiz = arvore_matricula_cria();

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

//         for(int i = 0; i < quant; i++)
//             arvore_matricula_add(&raiz, mat[i]);

//         arvore_matricula_add(&raiz, 5);

//         if(cont == 0)
//         {
//             printf("Árvore original\n");
//             arvore_matricula_exibir(raiz);
//         }

//         Arvore_Matricula *no_removido = arvore_matricula_remover(&raiz, cont);
//         if(no_removido != NULL)
//             printf("\nÁrvore após remover %d\n", no_removido->info);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvore_matricula_exibir(raiz);

//         arvore_matricula_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }