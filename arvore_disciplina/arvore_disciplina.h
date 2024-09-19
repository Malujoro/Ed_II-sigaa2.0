typedef struct disciplina
{
    int codigo_disciplina;
    char *nome_disciplina;
    int periodo;
    int carga_horaria;
} Disciplina;

typedef struct arvore_disciplina
{
    Disciplina info;
    struct arvore_disciplina *esquerdo;
    struct arvore_disciplina *direito;
} Arvore_Disciplina;

// Função para alocar um nó da árvore de disciplinas
// Retorna o endereço do nó alocado
Arvore_Disciplina *no_disciplina_aloca();

// Função para criar o nó da árvore de disciplinas
// Tem como parâmetro a struct da disciplina 
// Retorna o endereço do nó criado
Arvore_Disciplina *no_disciplina_cria(Disciplina disciplina);

// Função para criar a árvore de disciplinas
// Retorna a "árvore vazia" (null)
Arvore_Disciplina *arvore_disciplina_cria();

// Função para desalocar a árvore de disciplinas
// Tem como parâmetro a referência da raiz da árvore
void arvore_disciplina_desaloca(Arvore_Disciplina **raiz);

// Função para adicionar uma informação na árvore de disciplinas (criando um nó)
// Tem como parâmetro a referência da raiz da árvore e a struct da disciplina a ser adicionada
void arvore_disciplina_add(Arvore_Disciplina **raiz, Disciplina disciplina);

// Função para exibir a árvore de disciplinas no formato "em ordem"
// Tem como parâmetro a referência da raiz da árvore
void arvore_disciplina_exibir(Arvore_Disciplina *raiz);

// Função para remover o nó da árvore de disciplinas
// Tem como parâmetro a referência da raiz da árvore
// Retorna o nó removido (ou null caso não encontre)
Arvore_Disciplina *arvore_disciplina_remover_no(Arvore_Disciplina **raiz);

// Função para remover um nó da árvore de disciplinas
// Tem como parâmetro a referência da raiz da árvore e a struct da disciplina a ser removida
// Retorna o nó removido (ou null caso não encontre)
Arvore_Disciplina *arvore_disciplina_remover(Arvore_Disciplina **raiz, Disciplina disciplina);