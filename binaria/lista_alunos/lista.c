#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int compara_string_crescente(char *palavra1, char *palavra2)
{
    int i = 0, retorno;

    while(palavra1[i] != '\0' && palavra2[i] != '\0' && palavra1[i] == palavra2[i])
        i++;

    if(palavra1[i] == '\0' || palavra1[i] < palavra2[i])
        retorno = 0;
    else
        retorno = 1;

    return retorno;
}

Lista *no_lista_aloca()
{
    Lista *no;
    no = (Lista *) malloc(sizeof(Lista));
    
    if(!no)
    {
        printf("Erro ao alocar nó da lista de alunos");
        exit(EXIT_FAILURE);
    }

    return no;
}

Lista *no_lista_cria(Aluno aluno)
{
    Lista *no;
    no = no_lista_aloca();
    no->info = aluno;
    no->proximo = NULL;
    return no;
}

Lista *lista_cria()
{
    return NULL;
}

void lista_desaloca(Lista **lista)
{
    if(*lista != NULL)
    {
        if((*lista)->proximo != NULL)
            lista_desaloca(&(*lista)->proximo);

        free((*lista)->info.nome);
        (*lista)->info.nome = NULL;

        arvorebb_desaloca(&((*lista)->info.arvbb_matricula));
        arvorebb_desaloca(&((*lista)->info.arvbb_nota));

        free(*lista);
        *lista = NULL;
    }
}

void lista_add_ordenado(Lista **lista, Aluno aluno)
{
    Lista *no;
    no = no_lista_cria(aluno);

    // Situação em que a lista está vazia,
    // ou o novo aluno será o primeiro da lista
    if((*lista) == NULL || compara_string_crescente((*lista)->info.nome, no->info.nome))
    {
        no->proximo = (*lista);
        (*lista) = no;
    }
    else
    {
        Lista *aux;
        aux = (*lista);

        while(aux->proximo != NULL && compara_string_crescente(no->info.nome, aux->proximo->info.nome))
            aux = aux->proximo;

        no->proximo = aux->proximo;
        aux->proximo = no;
    }
}

void aluno_exibir(Aluno aluno)
{
    printf("Matrícula: %d | Nome: %s | Código do curso: %d\n", aluno.matricula, aluno.nome, aluno.codigo_curso);
}

void lista_exibir(Lista *lista)
{
    printf("Lista\n");

    Lista *no;
    no = lista;
    while(no != NULL)
    {
        aluno_exibir(no->info);
        no = no->proximo;
    }
}
 
Lista *lista_alunos_buscar(Lista *lista, int matricula)
{
    Lista *aluno = lista;
    
    while(aluno != NULL && aluno->info.matricula != matricula)
        aluno = aluno->proximo;

    return aluno;
}