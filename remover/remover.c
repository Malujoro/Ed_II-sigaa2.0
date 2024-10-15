#include <stdio.h>
#include <stdlib.h>
#include "remover.h"
#include "../lista_alunos/lista.h"
#include "../arvorebb/arvorebb.h"

int remover_disciplina_sem_alunos(ArvoreBB **raiz_disciplina, int codigo_disciplina, Lista *lista)
{
    int removeu = 0;
    int naoTemAluno = 1;
    Lista *aux = lista;

    while(aux != NULL && naoTemAluno)
    {
        if(arvorebb_buscar(aux->info.arvbb_matricula, codigo_disciplina) || arvorebb_buscar(aux->info.arvbb_nota, codigo_disciplina))
            naoTemAluno = 0;
        
        aux = aux->proximo;
    }
    
    if(naoTemAluno)
        removeu = arvorebb_remover(raiz_disciplina, codigo_disciplina);

    return removeu; 
}

int remover_matricula_aluno(Lista *aluno, int codigo_matricula)
{
    return arvorebb_remover(&(aluno->info.arvbb_matricula), codigo_matricula);
}