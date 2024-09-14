#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int matricula;
    char *nome;
    int codigo_curso;
    // Arvore Notas nota;
    // Arvore Matricula matricula;
} Aluno;

typedef struct no_lista
{
    Aluno info;
    struct no_lista *proximo;
} No_Lista;

typedef struct
{
    No_Lista *primeiro;
} Lista;

// Função que retorna "qual palavra vem primeiro" em uma ordem alfabética crescente
// Retorna 0 caso a primeira palavra "venha antes"
// Retorna 1 caso a segunda palavra "venha antes"
// TODO pensar em um nome melhor
int ordem_palavra(char *palavra1, char *palavra2)
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

No_Lista *no_lista_cria(Aluno aluno)
{
    No_Lista *no = (No_Lista *) malloc(sizeof(No_Lista));
    no->info = aluno;
    no->proximo = NULL;
    return no;
}

Lista *lista_cria()
{
    Lista *lista = (Lista *) malloc(sizeof(Lista));
    lista->primeiro = NULL;
    return lista;
}

void no_lista_desaloca(No_Lista **no)
{
    free(*no);
    *no = NULL;
}

void lista_desaloca(Lista **lista)
{
    No_Lista *no = (*lista)->primeiro;

    while(no != NULL)
    {
        No_Lista *aux = no->proximo;
        no_lista_desaloca(&no);
        no = aux;
    }

    free(*lista);
    *lista = NULL;
}

void lista_add_ordenado(Lista *lista, Aluno aluno)
{
    No_Lista *no = no_lista_cria(aluno);

    // Situação em que a lista está vazia,
    // ou o novo aluno será o primeiro da lista
    if(lista->primeiro == NULL || ordem_palavra(lista->primeiro->info.nome, no->info.nome))
    {
        no->proximo = lista->primeiro;
        lista->primeiro = no;
    }
    else
    {
        No_Lista *aux = lista->primeiro;

        while(aux->proximo != NULL && ordem_palavra(no->info.nome, aux->proximo->info.nome))
            aux = aux->proximo;

        no->proximo = aux->proximo;
        aux->proximo = no;
    }
}

void lista_exibir(Lista *lista)
{
    printf("Lista\n");

    No_Lista *no = lista->primeiro;
    while(no != NULL)
    {
        printf("Matrícula: %d | Nome: %s | Código do curso: %d\n", no->info.matricula, no->info.nome, no->info.codigo_curso);
        no = no->proximo;
    }
}

int main()
{
    Lista *lista = lista_cria();

    // Aluno aluno1;
    // aluno1.codigo_curso = 321;
    // aluno1.matricula = 123;
    // aluno1.nome = "Mateus";
    // lista_add_ordenado(lista, aluno1);

    // aluno1.codigo_curso = 432;
    // aluno1.matricula = 234;
    // aluno1.nome = "Lucas";
    // lista_add_ordenado(lista, aluno1);
    
    // aluno1.codigo_curso = 543;
    // aluno1.matricula = 345;
    // aluno1.nome = "João";
    // lista_add_ordenado(lista, aluno1);

    // aluno1.codigo_curso = 543;
    // aluno1.matricula = 345;
    // aluno1.nome = "Lucia";
    // lista_add_ordenado(lista, aluno1);


    char palavras[102][100] = {"Mateus", "Lucas",  "Miguel", "Sophia", "Davi", "Alice", "Arthur", "Julia", "Pedro", "Isabella", "Gabriel", "Manuela", "Bernardo", "Laura", "Lucas", "Luiza", "Matheus", "Valentina", "Rafael", "Giovanna", "Heitor", "Maria Eduarda", "Enzo", "Helena", "Guilherme", "Beatriz", "Nicolas", "Maria Luiza", "Lorenzo", "Lara", "Gustavo", "Mariana", "Felipe", "Nicole", "Samuel", "Rafaela", "João Pedro", "Heloísa", "Daniel", "Isadora", "Vitor", "Lívia", "Leonardo", "Maria Clara", "Henrique", "Ana Clara", "Theo", "Lorena", "Murilo", "Gabriela", "Eduardo", "Yasmin", "Pedro Henrique", "Isabelly", "Pietro", "Sarah", "Cauã", "Ana Julia", "Isaac", "Letícia", "Caio", "Ana Luiza", "Vinicius", "Melissa", "Benjamin", "Marina", "João", "Clara", "Lucca", "Cecília", "João Miguel", "Esther", "Bryan", "Emanuelly", "Joaquim", "Rebeca", "João Vitor", "Ana Beatriz", "Thiago", "Lavínia", "Antônio", "Vitória", "Davi Lucas", "Bianca", "Francisco", "Catarina", "Enzo Gabriel", "Larissa", "Bruno", "Maria Fernanda", "Emanuel", "Fernanda", "João Gabriel", "Amanda", "Ian", "Alícia", "Davi Luiz", "Carolina", "Rodrigo", "Agatha", "Otávio", "Gabrielly"};

    Aluno aluno1;
    for(int i = 0; i < 204; i++)
    {
        aluno1.codigo_curso = 100 + i;
        aluno1.matricula = 1000 - i;
        aluno1.nome = palavras[i % 102];
        lista_add_ordenado(lista, aluno1);
    }

    lista_exibir(lista);
    lista_desaloca(&lista);


    // int primeira = ordem_palavra(palavras[0], palavras[1]);
    // int segunda = 1 - primeira;
    // printf("[%s -> %s]\n", palavras[primeira], palavras[segunda]);
    return 0;
}