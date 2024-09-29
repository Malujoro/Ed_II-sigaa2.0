#ifndef ARVOREBB_DISCIPLINA_H
#define ARVOREBB_DISCIPLINA_H

typedef struct disciplina
{
    int codigo_disciplina;
    char *nome_disciplina;
    int periodo;
    int carga_horaria;
} Disciplina;

typedef struct arvorebb_disciplina
{
    Disciplina info;
    struct arvorebb_disciplina *esquerdo;
    struct arvorebb_disciplina *direito;
} ArvoreBB_Disciplina;

/*
    Função para alocar um nó da árvore de disciplinas
    Retorna o endereço do nó alocado
*/
ArvoreBB_Disciplina *no_disciplina_aloca();

/*
    Função para criar o nó da árvore de disciplinas
    Tem como parâmetro a struct da disciplina 
    Retorna o endereço do nó criado
*/
ArvoreBB_Disciplina *no_disciplina_cria(Disciplina disciplina);

/*
    Função para criar a árvore de disciplinas
    Retorna a "árvore vazia" (null)
*/
ArvoreBB_Disciplina *arvorebb_disciplina_cria();

/*
    Função para desalocar a árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_disciplina_desaloca(ArvoreBB_Disciplina **raiz);

/*
    Função para adicionar uma informação na árvore de disciplinas (criando um nó)
    Tem como parâmetro a referência da raiz da árvore e a struct da disciplina a ser adicionada
*/
int arvorebb_disciplina_add(ArvoreBB_Disciplina **raiz, Disciplina disciplina);

/*
    Função para exibir a árvore de disciplinas no formato "em ordem"
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_disciplina_exibir(ArvoreBB_Disciplina *raiz);

ArvoreBB_Disciplina *arvorebb_disciplina_buscar(ArvoreBB_Disciplina *raiz, int codigo);

/*
    Função para remover um nó da árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore e a struct da disciplina a ser removida
    Retorna o nó removido (ou null caso não encontre)
*/
int arvorebb_disciplina_remover(ArvoreBB_Disciplina **raiz, int codigo_disciplina);

#endif