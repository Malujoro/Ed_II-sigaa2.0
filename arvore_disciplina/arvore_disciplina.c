#include <stdio.h>
#include <stdlib.h>
#include "arvore_disciplina.h"

Arvore_Disciplina *no_disciplina_aloca()
{
    Arvore_Disciplina *no;
    no = (Arvore_Disciplina *)malloc(sizeof(Arvore_Disciplina));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de disciplinas");
        exit(EXIT_FAILURE);
    }

    return no;
}

Arvore_Disciplina *no_disciplina_cria(Disciplina disciplina)
{
    Arvore_Disciplina *no;
    no = no_disciplina_aloca();

    no->info = disciplina;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

Arvore_Disciplina *arvore_disciplina_cria()
{
    return NULL;
}

void arvore_disciplina_desaloca(Arvore_Disciplina **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvore_disciplina_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvore_disciplina_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvore_disciplina_add(Arvore_Disciplina **raiz, Disciplina disciplina)
{
    if ((*raiz) == NULL)
        (*raiz) = no_disciplina_cria(disciplina);
    else
    {
        if (disciplina.codigo_disciplina < (*raiz)->info.codigo_disciplina)
            arvore_disciplina_add(&(*raiz)->esquerdo, disciplina);
        else
            arvore_disciplina_add(&(*raiz)->direito, disciplina);
    }
}

void arvore_disciplina_exibir(Arvore_Disciplina *raiz)
{
    if (raiz != NULL)
    {
        arvore_disciplina_exibir(raiz->esquerdo);
        printf("Código: %d \n", raiz->info.codigo_disciplina);
        printf("Nome da disciplina: %s\n", raiz->info.nome_disciplina);
        printf("Período: %d\n", raiz->info.periodo);
        printf("Carga horária: %d\n\n", raiz->info.carga_horaria);
        arvore_disciplina_exibir(raiz->direito);
    }
}

Arvore_Disciplina *arvore_disciplina_remover_no(Arvore_Disciplina **raiz)
{
    Arvore_Disciplina *no;
    no = (*raiz);

    // Caso de 2 filhos
    if (no->esquerdo != NULL && no->direito != NULL)
    {
        if (no->direito->esquerdo != NULL)
        {
            Arvore_Disciplina *aux;
            aux = no->direito;
            while (aux->esquerdo->esquerdo != NULL)
                aux = aux->esquerdo;

            (*raiz) = arvore_disciplina_remover_no(&(aux->esquerdo));
        }
        else
            (*raiz) = arvore_disciplina_remover_no(&(no->direito));

        (*raiz)->esquerdo = no->esquerdo;
        (*raiz)->direito = no->direito;
    }
    // Caso de 1 filho (esquerdo)
    else if (no->esquerdo != NULL)
        (*raiz) = no->esquerdo;
    // Caso de 1 filho (direito)
    else if (no->direito != NULL)
        (*raiz) = no->direito;
    // Caso de nenhum filho
    else
        (*raiz) = NULL;

    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

Arvore_Disciplina *arvore_disciplina_remover(Arvore_Disciplina **raiz, Disciplina disciplina)
{
    Arvore_Disciplina *no;
    no = NULL;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.codigo_disciplina == disciplina.codigo_disciplina)
            no = arvore_disciplina_remover_no(&(*raiz));
        else if (disciplina.codigo_disciplina < (*raiz)->info.codigo_disciplina)
            no = arvore_disciplina_remover(&((*raiz)->esquerdo), disciplina);
        else if (disciplina.codigo_disciplina > (*raiz)->info.codigo_disciplina)
            no = arvore_disciplina_remover(&((*raiz)->direito), disciplina);
    }

    return no;
}

// int main()
// {
//     for(int cont = 0; cont < 10; cont ++)
//     {

//         Arvore_Disciplina *raiz = arvore_disciplina_cria();
//         Disciplina disciplina;

//         int quant = 10;
//         int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};
//         char nomes[][100] = {"Alef", "Emilly", "Flávio", "Gabriel", "Ghabriel", "Jonas", "Marcio", "Mateus","Rayssa","Walisson"};
//         Disciplina disciplinas[10];

//         for(int i = 0; i < quant; i++)
//         {
//             disciplina.codigo_disciplina = mat[i];
//             disciplina.nome_disciplina = nomes[mat[i]];
//             disciplina.periodo = mat[i] + 10;
//             disciplina.carga_horaria = mat[i] + 100;

//             disciplinas[i] = disciplina;
//             arvore_disciplina_add(&raiz, disciplina);
//         }

//         if(cont == 0)
//         {
//             printf("Árvore original\n");
//             arvore_disciplina_exibir(raiz);
//         }

//         Arvore_Disciplina *no_removido = arvore_disciplina_remover(&raiz, disciplinas[cont]);
//         if(no_removido != NULL)
//             printf("\nÁrvore após remover %d\n", no_removido->info.codigo_disciplina);
//         else
//             printf("\nÁrvore após remover [Elemento não encontrado]\n");
//         arvore_disciplina_exibir(raiz);

//         arvore_disciplina_desaloca(&raiz);
//         printf("\n\n");
//     }
//     return 0;
// }