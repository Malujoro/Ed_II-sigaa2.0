typedef struct aluno
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

typedef struct lista
{
    No_Lista *primeiro;
} Lista;

// Função que retorna "qual palavra vem primeiro" em uma ordem alfabética crescente
// Retorna 0 caso a primeira palavra "venha antes"
// Retorna 1 caso a segunda palavra "venha antes"
// TODO pensar em um nome melhor
int ordem_palavra(char *palavra1, char *palavra2);

No_Lista *no_lista_cria(Aluno aluno);

Lista *lista_cria();

void no_lista_desaloca(No_Lista **no);

void lista_desaloca(Lista **lista);

void lista_add_ordenado(Lista *lista, Aluno aluno);

void lista_exibir(Lista *lista);