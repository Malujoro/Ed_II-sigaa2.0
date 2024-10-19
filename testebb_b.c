#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvorebb/arvorebb.h"

typedef double tempo_tipo;

tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo) (fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}

union Data preencher_no_nota(int i)
{
    union Data info;
    info.nota.codigo_disciplina = i;
    info.nota.nota_final = (i % 100) / 10;
    info.nota.semestre = (i % 8) + 1;
    return info;
}

ArvoreBB *montar_arvore_crescente(int quant)
{
    ArvoreBB *arvore;
    arvore = arvorebb_cria();

    for(int i = 1; i <= quant; i++)
    {
        union Data info = preencher_no_nota(i * 10);
        arvorebb_add(&arvore, info);
    }

    return arvore;
}

ArvoreBB *montar_arvore_decrescente(int quant)
{
    ArvoreBB *arvore;
    arvore = arvorebb_cria();

    for(int i = quant; i > 0; i--)
    {
        union Data info = preencher_no_nota(i * 10);
        arvorebb_add(&arvore, info);
    }

    return arvore;
}

ArvoreBB *montar_arvore_aleatoria(int quant)
{
    ArvoreBB *arvore;
    arvore = arvorebb_cria();

    int tam = 0, num;
    while(tam < quant)
    {
        num = (rand() % quant) + 1;
        union Data info = preencher_no_nota(num * 10);
        tam += arvorebb_add(&arvore, info);
    }

    return arvore;
}

tempo_tipo calcular_tempo_medio(ArvoreBB *arvore, int codigo, int repeticoes)
{
    tempo_tipo media = 0;
    for(int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        tempo_tipo tempo_gasto;

        inicio = clock();

        arvorebb_buscar(arvore, codigo);

        fim = clock();

        media += calcula_tempo(inicio, fim);
    }
    media /= repeticoes;
    return media;
}

int main()
{
    srand(1);

    int quant_nos = 10000, repeticoes = 30;

    int codigos[3] = {1000, 50000, 100000};

    ArvoreBB *arvore_crescente, *arvore_decrescente, *arvore_aleatoria;
    arvore_crescente = montar_arvore_crescente(quant_nos);
    arvore_decrescente = montar_arvore_decrescente(quant_nos);
    arvore_aleatoria = montar_arvore_aleatoria(quant_nos);
    
    for(int i = 0; i < 3; i++)
    {
        printf("Codigo escolhido: %d\n", codigos[i]);
        tempo_tipo media_crescente = calcular_tempo_medio(arvore_crescente, codigos[i], repeticoes);
        tempo_tipo media_decrescente = calcular_tempo_medio(arvore_decrescente, codigos[i], repeticoes);
        tempo_tipo media_aleatoria = calcular_tempo_medio(arvore_aleatoria, codigos[i], repeticoes);

        printf("[Crescente] Tempo médio de execução: %lf microssegundos\n", media_crescente);
        printf("[Decrescente] Tempo médio de execução: %lf microssegundos\n", media_decrescente);
        printf("[Aleatória] Tempo médio de execução: %lf microssegundos\n\n", media_aleatoria);
    }
    
    return 0;
}