typedef struct arvore_matricula
{
    int info;
    struct arvore_matricula *esquerdo;
    struct arvore_matricula *direito;
} Arvore_Matricula;

/*
    Função para alocar um nó da árvore de disciplinas
    Retorna o endereço do nó alocado
*/
Arvore_Matricula *no_matricula_aloca();

/*
    Função para criar o nó da árvore de disciplinas
    Tem como parâmetro o código da disciplina 
    Retorna o endereço do nó criado
*/
Arvore_Matricula *no_matricula_cria(int codigo_disciplina);

/*
    Função para criar a árvore de disciplinas
    Retorna a "árvore vazia" (null)
*/
Arvore_Matricula *arvore_matricula_cria();

/*
    Função para desalocar a árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore
*/
void arvore_matricula_desaloca(Arvore_Matricula **raiz);

/*
    Função para adicionar uma informação na árvore de disciplinas (criando um nó)
    Tem como parâmetro a referência da raiz da árvore e o código da disciplina a ser adicionada
*/
int arvore_matricula_add(Arvore_Matricula **raiz, int codigo_disciplina);

/*
    Função para exibir a árvore de disciplinas no formato "em ordem"
    Tem como parâmetro a referência da raiz da árvore
*/
void arvore_matricula_exibir(Arvore_Matricula *raiz);

/*
    Função para remover um nó da árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore e o código da disciplina a ser removida
    Retorna o nó removido (ou null caso não encontre)
*/
Arvore_Matricula *arvore_matricula_remover_no(Arvore_Matricula **raiz, int codigo_disciplina);