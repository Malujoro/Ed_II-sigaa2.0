#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef struct curso
{
    int cod;
    char *nome;
    int qt_periodos;
    struct arvoreavl *arvavl_disciplina;
} Curso;

typedef struct disciplina
{
    int codigo_disciplina;
    char *nome_disciplina;
    int periodo;
    int carga_horaria;
} Disciplina;

typedef struct nota
{
    int codigo_disciplina;
    int semestre;
    float nota_final;
} Nota;

union Data {
    int matricula;
    Curso curso;
    Disciplina disciplina;
    Nota nota;
};

typedef struct arvoreavl
{
    union Data info;
    int altura;
    struct arvoreavl *esquerdo;
    struct arvoreavl *direito;
} ArvoreAVL;

/*
    Função para alocar um nó da árvore
    Retorna o endereço do nó alocado
*/
ArvoreAVL *no_aloca();

/*
    Função para criar o nó da árvore
    Tem como parâmetro a informação do nó 
    Retorna o endereço do nó criado
*/
ArvoreAVL *no_cria(union Data info);

/*
    Função para criar a árvore
    Retorna a "árvore vazia" (null)
*/
ArvoreAVL *arvoreavl_cria();

/*
    Função para desalocar a árvore
    Tem como parâmetro a referência da raiz da árvore
*/
void arvoreavl_desaloca(ArvoreAVL **raiz);
void arvoreavl_curso_desaloca(ArvoreAVL **raiz);
void arvoreavl_disciplina_desaloca(ArvoreAVL **raiz);

/*
    Função para adicionar uma informação na árvore (criando um nó)
    Tem como parâmetro a referência da raiz da árvore e a informação a ser adicionada
    Retorna 1 caso a adição tenha sido feita com sucesso, e 0 caso o código já exista na árvore
*/
int arvoreavl_add(ArvoreAVL **raiz, union Data info);

/*
    Função para buscar um nó da árvore
    Tem como parâmetro o código a ser buscado
    Caso encontre, retorna o código. Caso não, retorna Null
*/
ArvoreAVL *arvoreavl_buscar(ArvoreAVL *raiz, int codigo);

/*
    Função para exibir a árvore no formato "em ordem"
    Tem como parâmetro o endereço da raiz da árvore
*/
void arvoreavl_exibir(ArvoreAVL *raiz);

/*
    Função para exibir a árvore de cursos no formato "em ordem"
    Tem como parâmetro o endereço da raiz da árvore
*/
void arvoreavl_curso_exibir(ArvoreAVL *raiz);

/*
    Função para exibir uma disciplina
    Tem como parâmetro a própria disciplina
*/
void disciplina_exibir(Disciplina disciplina);

/*
    Função para exibir a árvore de disciplinas no formato "em ordem"
    Tem como parâmetro o endereço da raiz da árvore
*/
void arvoreavl_disciplina_exibir(ArvoreAVL *raiz);

/*
    Função para exibir uma nota
    Tem como parâmetro a própria nota
*/
void nota_exibir(Nota nota);

/*
    Função para exibir a árvore de notas no formato "em ordem"
    Tem como parâmetro o endereço da raiz da árvore
*/
void arvoreavl_nota_exibir(ArvoreAVL *raiz);

/*
    Função para remover um nó da árvore
    Tem como parâmetro a referência da raiz da árvore e o código a ser removida
    Retorna o nó removido (ou null caso não encontre)
*/
int arvoreavl_remover(ArvoreAVL **raiz, int codigo);

/*
    Função para contar quantos nós uma árvore possui
    Tem como parâmetro o endereço da raiz da árvore
    Retorna a quantidade de nós
*/
int arvoreavl_total_nos(ArvoreAVL *raiz);

#endif