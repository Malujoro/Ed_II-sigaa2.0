#ifndef ARVOREBB_MATRICULA_H
#define ARVOREBB_MATRICULA_H

typedef struct arvorebb_matricula
{
    int info;
    struct arvorebb_matricula *esquerdo;
    struct arvorebb_matricula *direito;
} ArvoreBB_Matricula;

/*
    Função para alocar um nó da árvore de disciplinas
    Retorna o endereço do nó alocado
*/
ArvoreBB_Matricula *no_matricula_aloca();

/*
    Função para criar o nó da árvore de disciplinas
    Tem como parâmetro o código da disciplina 
    Retorna o endereço do nó criado
*/
ArvoreBB_Matricula *no_matricula_cria(int codigo_disciplina);

/*
    Função para criar a árvore de disciplinas
    Retorna a "árvore vazia" (null)
*/
ArvoreBB_Matricula *arvorebb_matricula_cria();

/*
    Função para desalocar a árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_matricula_desaloca(ArvoreBB_Matricula **raiz);

/*
    Função para adicionar uma informação na árvore de disciplinas (criando um nó)
    Tem como parâmetro a referência da raiz da árvore e o código da disciplina a ser adicionada
*/
int arvorebb_matricula_add(ArvoreBB_Matricula **raiz, int codigo_disciplina);

/*
    Função para exibir a árvore de disciplinas no formato "em ordem"
    Tem como parâmetro a referência da raiz da árvore
*/
void arvorebb_matricula_exibir(ArvoreBB_Matricula *raiz);

/*
    Função para remover um nó da árvore de disciplinas
    Tem como parâmetro a referência da raiz da árvore e o código da disciplina a ser removida
    Retorna o nó removido (ou null caso não encontre)
*/
int arvorebb_matricula_remover(ArvoreBB_Matricula **raiz, int codigo_disciplina);

#endif