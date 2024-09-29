#include <stdio.h>
#include <stdlib.h>
#include "arvorebb_disciplina.h"

ArvoreBB_Disciplina *no_disciplina_aloca()
{
    ArvoreBB_Disciplina *no;
    no = (ArvoreBB_Disciplina *)malloc(sizeof(ArvoreBB_Disciplina));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de disciplinas");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreBB_Disciplina *no_disciplina_cria(Disciplina disciplina)
{
    ArvoreBB_Disciplina *no;
    no = no_disciplina_aloca();

    no->info = disciplina;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

ArvoreBB_Disciplina *arvorebb_disciplina_cria()
{
    return NULL;
}

void arvorebb_disciplina_desaloca(ArvoreBB_Disciplina **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvorebb_disciplina_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvorebb_disciplina_desaloca(&((*raiz)->direito));

        free((*raiz)->info.nome_disciplina);
        (*raiz)->info.nome_disciplina = NULL;

        free(*raiz);
        *raiz = NULL;
    }
}

int arvorebb_disciplina_add(ArvoreBB_Disciplina **raiz, Disciplina disciplina)
{
    int inseriu = 1;
    if ((*raiz) == NULL)
        (*raiz) = no_disciplina_cria(disciplina);
    else
    {
        if (disciplina.codigo_disciplina < (*raiz)->info.codigo_disciplina)
            arvorebb_disciplina_add(&(*raiz)->esquerdo, disciplina);
        else if (disciplina.codigo_disciplina > (*raiz)->info.codigo_disciplina)
            arvorebb_disciplina_add(&(*raiz)->direito, disciplina);
        else
            inseriu = 0;
    }

    return inseriu;
}

ArvoreBB_Disciplina *arvorebb_disciplina_buscar(ArvoreBB_Disciplina *raiz, int codigo)
{
    ArvoreBB_Disciplina *retorno;

    if(raiz != NULL)
    {
        if(codigo == raiz->info.codigo_disciplina)
            retorno = raiz;
        else if(codigo < raiz->info.codigo_disciplina)
            retorno = arvorebb_disciplina_buscar(raiz->esquerdo, codigo);
        else if(codigo > raiz->info.codigo_disciplina)
            retorno = arvorebb_disciplina_buscar(raiz->direito, codigo);
    }
    else
        retorno = NULL;
    
    return retorno;
}

void arvorebb_disciplina_exibir(ArvoreBB_Disciplina *raiz)
{
    if (raiz != NULL)
    {
        arvorebb_disciplina_exibir(raiz->esquerdo);
        printf("Código: %d \n", raiz->info.codigo_disciplina);
        printf("Nome da disciplina: %s\n", raiz->info.nome_disciplina);
        printf("Período: %d\n", raiz->info.periodo);
        printf("Carga horária: %d\n\n", raiz->info.carga_horaria);
        arvorebb_disciplina_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreBB_Disciplina *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreBB_Disciplina *endereco_filho_unico(ArvoreBB_Disciplina *raiz)
{
    ArvoreBB_Disciplina *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreBB_Disciplina *menor_filho(ArvoreBB_Disciplina *raiz)
{
    ArvoreBB_Disciplina *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvorebb_disciplina_remover(ArvoreBB_Disciplina **raiz, int codigo_disciplina)
{
    ArvoreBB_Disciplina *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.codigo_disciplina == codigo_disciplina)
        {
            if (no_folha(*raiz))
            {
                aux = *raiz;
                *raiz = NULL;
                free(aux);
            }
            else if ((endereco_filho = endereco_filho_unico(*raiz)) != NULL)
            {
                aux = *raiz;
                *raiz = endereco_filho;
                free(aux);
            }
            else
            {
                endereco_menor_filho = menor_filho((*raiz)->direito);
                (*raiz)->info = endereco_menor_filho->info;
                arvorebb_disciplina_remover(&((*raiz)->direito), endereco_menor_filho->info.codigo_disciplina);
            }
        }
        else if (codigo_disciplina < (*raiz)->info.codigo_disciplina)
            removeu = arvorebb_disciplina_remover(&((*raiz)->esquerdo), codigo_disciplina);
        else if (codigo_disciplina > (*raiz)->info.codigo_disciplina)
            removeu = arvorebb_disciplina_remover(&((*raiz)->direito), codigo_disciplina);
    }
    else
        removeu = 0;

    return removeu;
}

int main()
{
    for(int cont = 0; cont < 10; cont ++)
    {

        ArvoreBB_Disciplina *raiz = arvorebb_disciplina_cria();
        Disciplina disciplina;

        int quant = 10;
        int mat[] = {3, 1, 5, 2, 8, 6, 9, 0, 4, 7};

        char **nomes = (char **) malloc(sizeof(char *) * quant);
        for(int i = 0; i < quant; i++)
        {
            nomes[i] = (char *) malloc(sizeof(char) * 100);
            scanf("%s", nomes[i]);
            while(getchar() != '\n');
        }
        Disciplina disciplinas[10];

        for(int i = 0; i < quant; i++)
        {
            disciplina.codigo_disciplina = mat[i];
            disciplina.nome_disciplina = nomes[mat[i]];
            disciplina.periodo = mat[i] + 10;
            disciplina.carga_horaria = mat[i] + 100;

            disciplinas[i] = disciplina;
            arvorebb_disciplina_add(&raiz, disciplina);
        }

        if(cont == 0)
        {
            printf("Árvore original\n");
            arvorebb_disciplina_exibir(raiz);
            printf("\n");
        }

        int removeu = arvorebb_disciplina_remover(&raiz, disciplinas[cont].codigo_disciplina);
        if(removeu)
            printf("\nÁrvore após remover %d\n", disciplinas[cont].codigo_disciplina);
        else
            printf("\nÁrvore após remover [Elemento não encontrado]\n");
        arvorebb_disciplina_exibir(raiz); 

        arvorebb_disciplina_desaloca(&raiz);
        printf("\n\n");
    }
    return 0;
}