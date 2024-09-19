#include <stdio.h>
#include "lista_alunos/lista.h"
#include "arvore_matricula/arvore_matricula.h"

int main()
{
    for(int cont = 0; cont < 10; cont ++)
    {

        Arvore_Matricula *raiz = arvore_matricula_cria();

        int quant = 10;
        int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

        for(int i = 0; i < quant; i++)
            arvore_matricula_add(&raiz, mat[i]);

        arvore_matricula_add(&raiz, 5);

        if(cont == 0)
        {
            printf("Árvore original\n");
            arvore_matricula_exibir(raiz);
        }

        Arvore_Matricula *no_removido = arvore_matricula_remover(&raiz, cont);
        if(no_removido != NULL)
            printf("\nÁrvore após remover %d\n", no_removido->info);
        else
            printf("\nÁrvore após remover [Elemento não encontrado]\n");
        arvore_matricula_exibir(raiz);

        arvore_matricula_desaloca(&raiz);
        printf("\n\n");
    }
    return 0;
}