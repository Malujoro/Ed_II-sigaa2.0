#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore/arvore.h"

typedef double tempo_tipo;

tempo_tipo calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((tempo_tipo) (fim - inicio)) / CLOCKS_PER_SEC * 1000 * 1000;
}

union Data preencher_no_curso(int i)
{
    union Data info;
    info.curso.cod = i;
    info.curso.nome = "a";
    info.curso.qt_periodos = (i % 10) + 1;
    info.curso.arvbb_disciplina = arvorebb_cria();
    return info;
}

ArvoreBB *montar_arvore_crescente(int quant)
{
    ArvoreBB *arvore;
    arvore = arvorebb_cria();

    for(int i = 1; i <= quant; i++)
    {
        union Data info = preencher_no_curso(i * 10);
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
        union Data info = preencher_no_curso(i * 10);
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
        union Data info = preencher_no_curso(num * 10);
        tam += arvorebb_add(&arvore, info);
    }

    return arvore;
}

tempo_tipo calcular_tempo_medio(ArvoreBB **arvore, union Data info, int repeticoes)
{
    tempo_tipo media = 0;
    for(int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        int adicionou;
        tempo_tipo tempo_gasto;

        inicio = clock();

        adicionou = arvorebb_add(arvore, info);

        fim = clock();
        
        if(adicionou)
            arvorebb_remover(arvore, info.curso.cod);

        tempo_gasto = calcula_tempo(inicio, fim);
        printf("Tempo médio de execução: %lf microssegundos\n", tempo_gasto);
        media += tempo_gasto;
    }
    media /= repeticoes;
    return media;
}

int main()
{
    srand(1);

    int quant_nos = 10000, repeticoes = 30;

    int valores[3] = {1001, 50001, 100001};

    ArvoreBB *arvore_crescente, *arvore_decrescente, *arvore_aleatoria;
    arvore_crescente = montar_arvore_crescente(quant_nos);
    arvore_decrescente = montar_arvore_decrescente(quant_nos);
    arvore_aleatoria = montar_arvore_aleatoria(quant_nos);
    
    for(int i = 0; i < 3; i++)
    {
        union Data info = preencher_no_curso(valores[i]);
        printf("Valor escolhido: %d\n", valores[i]);

        tempo_tipo media_crescente = calcular_tempo_medio(&arvore_crescente, info, repeticoes);
        printf("[Crescente] Tempo médio de execução: %lf microssegundos\n\n", media_crescente);

        tempo_tipo media_decrescente = calcular_tempo_medio(&arvore_decrescente, info, repeticoes);

        printf("[Decrescente] Tempo médio de execução: %lf microssegundos\n\n", media_decrescente);

        tempo_tipo media_aleatoria = calcular_tempo_medio(&arvore_aleatoria, info, repeticoes);
        printf("[Aleatória] Tempo médio de execução: %lf microssegundos\n\n", media_aleatoria);

    }

    arvorebb_desaloca(&arvore_crescente);
    arvorebb_desaloca(&arvore_decrescente);
    arvorebb_desaloca(&arvore_aleatoria);

    return 0;
}