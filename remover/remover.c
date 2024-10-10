#include <stdio.h>
#include <stdlib.h>
#include "remover.h"
#include "../lista_alunos/lista.h"
#include "../arvorebb_matricula/arvorebb_matricula.h"
#include "../arvorebb_disciplina/arvorebb_disciplina.h"
#include "../arvorebb_curso/arvorebb_curso.h"
#include "../arvorebb_notas/arvorebb_notas.h"

int remover_disciplina_sem_alunos(ArvoreBB_Disciplina **raiz, int codigo_disciplina, Lista *lista)
{
    int removeu = 0;
    int naoTemAluno = 1;
    Lista *aux = lista;

    while(aux != NULL && naoTemAluno)
    {
        if(arvorebb_matricula_buscar(aux->info.arvbb_matricula, codigo_disciplina))
            naoTemAluno = 0;
        
        aux = aux->proximo;
    }
    
    if(naoTemAluno)
        removeu = arvorebb_disciplina_remover(raiz, codigo_disciplina);

    return removeu; 
}

int remover_matricula_aluno(Lista *aluno, int codigo_matricula)
{
    return arvorebb_matricula_remover(&(aluno->info.arvbb_matricula), codigo_matricula);
}