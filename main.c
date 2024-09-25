#include <stdio.h>
#include "lista_alunos/lista.h"
#include "arvorebb_matricula/arvorebb_matricula.h"
#include "arvorebb_disciplina/arvorebb_disciplina.h"
#include "arvorebb_curso/arvorebb_curso.h"

int main()
{
    for(int cont = 0; cont < 10; cont ++)
    {

        ArvoreBB_Disciplina *raiz = arvorebb_disciplina_cria();
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
            arvorebb_disciplina_add(&raiz, disciplina);
        }

        if(cont == 0)
        {
            printf("Árvore original\n");
            arvorebb_disciplina_exibir(raiz);
        }

        int removeu = arvorebb_disciplina_remover(&raiz, disciplinas[cont].codigo_disciplina);
        if(removeu)
            printf("\nÁrvore após remover %d\n", disciplinas[cont].codigo_disciplina);
        else
            printf("\nÁrvore após remover [Elemento não encontrado]\n");
        arvorebb_disciplina_exibir(raiz);

        arvorebb_disciplina_desaloca(&raiz);
        printf("\n\n");
    }
    return 0;
}