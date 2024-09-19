#include <stdio.h>
#include "lista_alunos/lista.h"
#include "arvore_matricula/arvore_matricula.h"
#include "arvore_disciplina/arvore_disciplina.h"

int main()
{
    for(int cont = 0; cont < 10; cont ++)
    {

        Arvore_Disciplina *raiz = arvore_disciplina_cria();
        Disciplina disciplina;

        int quant = 10;
        int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};
        char nomes[][100] = {"Alef", "Emilly", "Flávio", "Gabriel", "Ghabriel", "Jonas", "Marcio", "Mateus","Rayssa","Walisson"};
        Disciplina disciplinas[10];

        for(int i = 0; i < quant; i++)
        {
            disciplina.codigo_disciplina = mat[i];
            disciplina.nome_disciplina = nomes[mat[i]];
            disciplina.periodo = mat[i] + 10;
            disciplina.carga_horaria = mat[i] + 100;

            disciplinas[i] = disciplina;
            arvore_disciplina_add(&raiz, disciplina);
        }

        if(cont == 0)
        {
            printf("Árvore original\n");
            arvore_disciplina_exibir(raiz);
        }

        Arvore_Disciplina *no_removido = arvore_disciplina_remover(&raiz, disciplinas[cont]);
        if(no_removido != NULL)
            printf("\nÁrvore após remover %d\n", no_removido->info.codigo_disciplina);
        else
            printf("\nÁrvore após remover [Elemento não encontrado]\n");
        arvore_disciplina_exibir(raiz);

        arvore_disciplina_desaloca(&raiz);
        printf("\n\n");
    }
    return 0;
}