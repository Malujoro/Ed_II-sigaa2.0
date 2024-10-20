#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

ArvoreAVL *no_aloca()
{
    ArvoreAVL *no;
    no = (ArvoreAVL *)malloc(sizeof(ArvoreAVL));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore de matrículas");
        exit(EXIT_FAILURE);
    }

    return no;
}

ArvoreAVL *no_cria(union Data info)
{
    ArvoreAVL *no;
    no = no_aloca();

    no->info = info;
    no->altura = 0;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

ArvoreAVL *arvoreavl_cria()
{
    return NULL;
}

void arvoreavl_desaloca(ArvoreAVL **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvoreavl_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvoreavl_desaloca(&((*raiz)->direito));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvoreavl_curso_desaloca(ArvoreAVL **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvoreavl_curso_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvoreavl_curso_desaloca(&((*raiz)->direito));
        
        free((*raiz)->info.curso.nome);
        (*raiz)->info.curso.nome = NULL;

        arvoreavl_disciplina_desaloca(&((*raiz)->info.curso.arvavl_disciplina));

        free(*raiz);
        *raiz = NULL;
    }
}

void arvoreavl_disciplina_desaloca(ArvoreAVL **raiz)
{
    if ((*raiz) != NULL)
    {
        if ((*raiz)->esquerdo != NULL)
            arvoreavl_disciplina_desaloca(&((*raiz)->esquerdo));

        if ((*raiz)->direito != NULL)
            arvoreavl_disciplina_desaloca(&((*raiz)->direito));

        free((*raiz)->info.disciplina.nome_disciplina);
        (*raiz)->info.disciplina.nome_disciplina = NULL;

        free(*raiz);
        *raiz = NULL;
    }
}

int retornar_altura(ArvoreAVL *raiz)
{
    return raiz == NULL ? -1 : raiz->altura;
}

void atualizar_altura(ArvoreAVL *raiz)
{
    if(raiz != NULL)
    {
        int altura_esquerda = retornar_altura(raiz->esquerdo);
        int altura_direita = retornar_altura(raiz->direito);
        
        raiz->altura = (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
    }
}

void rotacao_esquerda(ArvoreAVL **raiz)
{
    ArvoreAVL *aux;

    aux = (*raiz)->direito;
    (*raiz)->direito = aux->esquerdo;
    aux->esquerdo = (*raiz);
    (*raiz) = aux;

    atualizar_altura(*raiz);
    atualizar_altura((*raiz)->esquerdo);
}

void rotacao_direita(ArvoreAVL **raiz)
{
    ArvoreAVL *aux;

    aux = (*raiz)->esquerdo;
    (*raiz)->esquerdo = aux->direito;
    aux->direito = (*raiz);
    (*raiz) = aux;

    atualizar_altura(*raiz);
    atualizar_altura((*raiz)->direito);
}

int fator_balanceamento(ArvoreAVL *raiz)
{
    return retornar_altura(raiz->esquerdo) - retornar_altura(raiz->direito);
}

void balancear_avl(ArvoreAVL **raiz)
{
    if(*raiz != NULL)
    {
        int fb = fator_balanceamento(*raiz);

        // Pendente para direita
        if(fb == -2)
        {
            if(fator_balanceamento((*raiz)->direito) > 0)
                rotacao_direita(&((*raiz)->direito));
            rotacao_esquerda(raiz);
        }
        // Pendente para esquerda
        else if(fb == 2)
        {
            if(fator_balanceamento((*raiz)->esquerdo) < 0)
                rotacao_esquerda(&((*raiz)->esquerdo));
            rotacao_direita(raiz);  
        }
    }
}

int arvoreavl_add(ArvoreAVL **raiz, union Data info)
{
    int inseriu = 1;

    if ((*raiz) == NULL)
    {
        (*raiz) = no_cria(info);
    }
    else
    {
        if (info.matricula < (*raiz)->info.matricula)
            inseriu = arvoreavl_add(&((*raiz)->esquerdo), info);
        else if (info.matricula > (*raiz)->info.matricula)
            inseriu = arvoreavl_add(&((*raiz)->direito), info);
        else
            inseriu = 0;

        balancear_avl(raiz);
        atualizar_altura(*raiz);
    }

    return inseriu;
}

ArvoreAVL *arvoreavl_buscar(ArvoreAVL *raiz, int codigo)
{
    ArvoreAVL *retorno;

    if(raiz != NULL)
    {
        if(codigo == raiz->info.matricula)
            retorno = raiz;
        else if(codigo < raiz->info.matricula)
            retorno = arvoreavl_buscar(raiz->esquerdo, codigo);
        else if(codigo > raiz->info.matricula)
            retorno = arvoreavl_buscar(raiz->direito, codigo);
    }
    else
        retorno = NULL;
    
    return retorno;
}

void arvoreavl_exibir(ArvoreAVL *raiz)
{
    if (raiz != NULL)
    {
        printf("%d | ", raiz->info.matricula);
        arvoreavl_exibir(raiz->esquerdo);
        arvoreavl_exibir(raiz->direito);
    }
}

void arvoreavl_curso_exibir(ArvoreAVL *raiz)
{
    if(raiz != NULL)
    {
        arvoreavl_curso_exibir(raiz->esquerdo);
        printf("Código: %d | Nome: %s | Períodos: %d\n", raiz->info.curso.cod, raiz->info.curso.nome, raiz->info.curso.qt_periodos);
        arvoreavl_curso_exibir(raiz->direito);
    }
}

void disciplina_exibir(Disciplina disciplina)
{
    printf("Código: %d | Nome: %s | Período: %d | Carga horária: %d\n", disciplina.codigo_disciplina,
    disciplina.nome_disciplina, disciplina.periodo, disciplina.carga_horaria);
}

void arvoreavl_disciplina_exibir(ArvoreAVL *raiz)
{
    if (raiz != NULL)
    {
        arvoreavl_disciplina_exibir(raiz->esquerdo);
        disciplina_exibir(raiz->info.disciplina);
        arvoreavl_disciplina_exibir(raiz->direito);
    }
}

void nota_exibir(Nota nota)
{
    printf("Código: %d | Semestre: %d | Nota final: %.1f\n", nota.codigo_disciplina, nota.semestre, nota.nota_final);
}

void arvoreavl_nota_exibir(ArvoreAVL *raiz)
{
    if (raiz != NULL)
    {
        arvoreavl_nota_exibir(raiz->esquerdo);
        nota_exibir(raiz->info.nota);
        arvoreavl_nota_exibir(raiz->direito);
    }
}

static int no_folha(ArvoreAVL *raiz)
{
    return raiz->esquerdo == NULL && raiz->direito == NULL;
}

static ArvoreAVL *endereco_filho_unico(ArvoreAVL *raiz)
{
    ArvoreAVL *filho;

    if (raiz->esquerdo == NULL)
        filho = raiz->direito;
    else if (raiz->direito == NULL)
        filho = raiz->esquerdo;
    else
        filho = NULL;

    return filho;
}

static ArvoreAVL *menor_filho(ArvoreAVL *raiz)
{
    ArvoreAVL *aux;
    aux = raiz;

    while (aux->esquerdo != NULL)
        aux = aux->esquerdo;

    return aux;
}

int arvoreavl_remover(ArvoreAVL **raiz, int codigo)
{
    ArvoreAVL *aux, *endereco_filho, *endereco_menor_filho;
    int removeu = 1;

    if ((*raiz) != NULL)
    {
        if ((*raiz)->info.matricula == codigo)
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
                arvoreavl_remover(&((*raiz)->direito), endereco_menor_filho->info.matricula);
            }
        }
        else if (codigo < (*raiz)->info.matricula)
            removeu = arvoreavl_remover(&((*raiz)->esquerdo), codigo);
        else if (codigo > (*raiz)->info.matricula)
            removeu = arvoreavl_remover(&((*raiz)->direito), codigo);

        balancear_avl(raiz);
        atualizar_altura(*raiz);
    }
    else
        removeu = 0;

    return removeu;
}

int arvoreavl_total_nos(ArvoreAVL *raiz)
{
    int quant = 0;
    if(raiz != NULL)
    {
        quant += 1;
        quant += arvoreavl_total_nos(raiz->esquerdo);
        quant += arvoreavl_total_nos(raiz->direito);
    }
    return quant;
}

// int main()
// {
//     ArvoreAVL *raiz = arvoreavl_cria();

//     int quant = 9;
//     int mat[] = {1000, 3000, 2000, 2300, 4000, 2500, 2400, 2600, 2350};
//     union Data info;

//     for (int i = 0; i < quant; i++)
//     {
//         info.matricula = mat[i];
//         arvoreavl_add(&raiz, info);
//         printf("\nÁrvore após inserir %d\n", info.matricula);
//         arvoreavl_exibir(raiz);
//     }

//     arvoreavl_desaloca(&raiz);
//     printf("\n\n");
//     return 0;
// }