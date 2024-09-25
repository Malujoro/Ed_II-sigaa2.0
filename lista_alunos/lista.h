typedef struct aluno
{
    int matricula;
    char *nome;
    int codigo_curso;
    // Arvore Notas nota;
    // Arvore Matricula matricula;
} Aluno;

typedef struct lista
{
    Aluno info;
    struct lista *proximo;
} Lista;

// Função que retorna se duas palavras estão em "ordem alfabética crescente"
// Tem como parâmetro as palavras a serem comparadas
// Retorna 0 caso a PRIMEIRA palavra "venha antes" (na ordem alfabética)
// Retorna 1 caso a SEGUNDA palavra "venha antes" (na ordem alfabética)
int compara_string_crescente(char *palavra1, char *palavra2);

// Função para alocar um nó da lista de alunos
// Retorna o endereço do nó alocado
Lista *no_lista_aloca();

// Função para criar o nó da lista de alunos
// Tem como parâmetro a struct do aluno 
// Retorna o endereço do nó criado
Lista *no_lista_cria(Aluno aluno);

// Função para criar a lista de alunos
// Retorna a "lista vazia" (null)
Lista *lista_cria();

// Função para desalocar a lista de alunos
// Tem como parâmetro a referência do primeiro elemento da lista
void lista_desaloca(Lista **lista);

// Função para adicionar uma informação na lista de alunos (criando um nó)
// Tem como parâmetro a referência do primeiro elemento da lista e a struct do aluno a ser adicionada
void lista_add_ordenado(Lista **lista, Aluno aluno);

// Função para exibir a lista de alunos no formato "em ordem"
// Tem como parâmetro a referência do primeiro elemento da lista
void lista_exibir(Lista *lista);