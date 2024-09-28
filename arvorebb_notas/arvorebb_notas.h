typedef struct nota
{
    int codigo_disciplina;
    int semestre;
    float nota_final;
    int carga_horaria;
} Nota;

typedef struct arvorebb_nota
{
    Nota info;
    struct arvorebb_nota *esquerdo;
    struct arvorebb_nota *direito;
} ArvoreBB_Nota;

/*
    Função para alocar um nó da árvore de notas
    Retorna o endereço do nó alocado
*/
ArvoreBB_Nota *no_nota_aloca();

/*
    Função para criar o nó da árvore de notas
    Tem como parâmetro a struct da nota 
    Retorna o endereço do nó criado
*/
ArvoreBB_Nota *no_nota_cria(Nota nota);

/*
    Função para criar a árvore de notas
    Retorna a "árvore vazia" (null)
*/
ArvoreBB_Nota *arvorebb_nota_cria();

/*
    Função para desalocar a árvore de notas
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_nota_desaloca(ArvoreBB_Nota **raiz);

/*
    Função para adicionar uma informação na árvore de notas (criando um nó)
    Tem como parâmetro a referência da raiz da árvore e a struct da nota a ser adicionada
*/
int arvorebb_nota_add(ArvoreBB_Nota **raiz, Nota nota);

/*
    Função para exibir a árvore de notas no formato "em ordem"
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_nota_exibir(ArvoreBB_Nota *raiz);

/*
    Função para remover um nó da árvore de notas
    Tem como parâmetro a referência da raiz da árvore e a struct da nota a ser removida
    Retorna o nó removido (ou null caso não encontre)
*/
int arvorebb_nota_remover(ArvoreBB_Nota **raiz, int codigo_disciplina);