#include <stdio.h>
#include <stdlib.h>
#include "remover.h"
#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"

int remover_disciplina_sem_alunos(ArvoreAVL **raiz_disciplina, int codigo_disciplina, Lista *lista)
{
    int removeu = 0;
    int naoTemAluno = 1;
    Lista *aux = lista;

    while(aux != NULL && naoTemAluno)
    {
        if(arvoreavl_buscar(aux->info.arvavl_matricula, codigo_disciplina) || arvoreavl_buscar(aux->info.arvavl_nota, codigo_disciplina))
            naoTemAluno = 0;
        
        aux = aux->proximo;
    }
    
    if(naoTemAluno)
        removeu = arvoreavl_remover(raiz_disciplina, codigo_disciplina);

    return removeu; 
}

int remover_matricula_aluno(Lista *aluno, int codigo_matricula)
{
    return arvoreavl_remover(&(aluno->info.arvavl_matricula), codigo_matricula);
}