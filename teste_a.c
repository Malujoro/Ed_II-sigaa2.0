#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvorebb/arvorebb.h"

double calcula_tempo(clock_t inicio, clock_t fim)
{
    return ((double) (fim - inicio)) / CLOCKS_PER_SEC;
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
        union Data info = preencher_no_curso(i);
        arvorebb_add(&arvore, info);
    }

    return arvore;
}

double calcular_tempo_medio(ArvoreBB **arvore, union Data info, int repeticoes)
{
    double media = 0;
    for(int i = 0; i < repeticoes; i++)
    {
        clock_t inicio, fim;
        int adicionou;
        double tempo_gasto;

        inicio = clock();

        adicionou = arvorebb_add(arvore, info);

        fim = clock();

        if(adicionou)
            arvorebb_remover(arvore, info.curso.cod);

        tempo_gasto = calcula_tempo(inicio, fim) * 1000;

        printf("Tempo de execução: %lf milissegundos\n", tempo_gasto);
        media += tempo_gasto;
    }
    media /= repeticoes;
    return media;
}

int main()
{   
    int quant_nos = 1000, repeticoes = 30;
    ArvoreBB *arvore_crescente;
    arvore_crescente = montar_arvore_crescente(quant_nos);

    int valor = rand() % quant_nos;
    printf("Valor escolhido: %d\n", valor);
    union Data info = preencher_no_curso(valor);

    double media = calcular_tempo_medio(&arvore_crescente, info, repeticoes);
    printf("Tempo médio de execução: %lf milissegundos\n", media);
    
    return 0;
}