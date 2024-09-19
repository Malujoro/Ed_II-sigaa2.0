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
    if((*lista)->proximo != NULL)
        lista_desaloca(&(*lista)->proximo);
    free(*lista);
    *lista = NULL;
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

void lista_exibir(Lista *lista)
{
    printf("Lista\n");

    Lista *no;
    no = lista;
    while(no != NULL)
    {
        printf("Matrícula: %d | Nome: %s | Código do curso: %d\n", no->info.matricula, no->info.nome, no->info.codigo_curso);
        no = no->proximo;
    }
}

// TODO adicionar a verificação na de curso existente hora de cadastrar o aluno

// int main()
// {
//     Lista *lista = lista_cria();

//     // Aluno aluno1;
//     // aluno1.codigo_curso = 321;
//     // aluno1.matricula = 123;
//     // aluno1.nome = "Mateus";
//     // lista_add_ordenado(lista, aluno1);

//     // aluno1.codigo_curso = 432;
//     // aluno1.matricula = 234;
//     // aluno1.nome = "Lucas";
//     // lista_add_ordenado(lista, aluno1);
    
//     // aluno1.codigo_curso = 543;
//     // aluno1.matricula = 345;
//     // aluno1.nome = "João";
//     // lista_add_ordenado(lista, aluno1);

//     // aluno1.codigo_curso = 543;
//     // aluno1.matricula = 345;
//     // aluno1.nome = "Lucia";
//     // lista_add_ordenado(lista, aluno1);


//     char palavras[102][100] = {"Mateus", "Lucas",  "Miguel", "Sophia", "Davi", "Alice", "Arthur", "Julia", "Pedro", "Isabella", "Gabriel", "Manuela", "Bernardo", "Laura", "Lucas", "Luiza", "Matheus", "Valentina", "Rafael", "Giovanna", "Heitor", "Maria Eduarda", "Enzo", "Helena", "Guilherme", "Beatriz", "Nicolas", "Maria Luiza", "Lorenzo", "Lara", "Gustavo", "Mariana", "Felipe", "Nicole", "Samuel", "Rafaela", "João Pedro", "Heloísa", "Daniel", "Isadora", "Vitor", "Lívia", "Leonardo", "Maria Clara", "Henrique", "Ana Clara", "Theo", "Lorena", "Murilo", "Gabriela", "Eduardo", "Yasmin", "Pedro Henrique", "Isabelly", "Pietro", "Sarah", "Cauã", "Ana Julia", "Isaac", "Letícia", "Caio", "Ana Luiza", "Vinicius", "Melissa", "Benjamin", "Marina", "João", "Clara", "Lucca", "Cecília", "João Miguel", "Esther", "Bryan", "Emanuelly", "Joaquim", "Rebeca", "João Vitor", "Ana Beatriz", "Thiago", "Lavínia", "Antônio", "Vitória", "Davi Lucas", "Bianca", "Francisco", "Catarina", "Enzo Gabriel", "Larissa", "Bruno", "Maria Fernanda", "Emanuel", "Fernanda", "João Gabriel", "Amanda", "Ian", "Alícia", "Davi Luiz", "Carolina", "Rodrigo", "Agatha", "Otávio", "Gabrielly"};

//     Aluno aluno1;
//     for(int i = 0; i < 204; i++)
//     {
//         aluno1.codigo_curso = 100 + i;
//         aluno1.matricula = 999 - i;
//         aluno1.nome = palavras[i % 102];
//         lista_add_ordenado(&lista, aluno1);
//     }

//     lista_exibir(lista);
//     lista_desaloca(&lista);

//     // int primeira = compara_string_crescente(palavras[0], palavras[1]);
//     // int segunda = 1 - primeira;
//     // printf("[%s -> %s]\n", palavras[primeira], palavras[segunda]);
//     return 0;
// }