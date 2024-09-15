#include <stdio.h>
#include "lista_alunos/lista.h"
#include "arvore_matricula/arvore_matricula.h"

int main()
{
    Arvore_Matricula *arvore = arvore_matricula_cria();

    int quant = 10;
    int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

    for(int i = 0; i < quant; i++)
        arvore_matricula_add(arvore, mat[i]);

    printf("Árvore original\n");
    arvore_matricula_exibir(arvore->raiz);

    No_Matricula *no_removido = arvore_matricula_remover(arvore, 6);
    printf("\nÁrvore após remover %d\n", no_removido->info);
    arvore_matricula_exibir(arvore->raiz);

    arvore_matricula_desaloca(&arvore);
    return 0;
}