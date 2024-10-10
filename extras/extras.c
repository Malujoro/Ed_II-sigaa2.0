#include <stdio.h>
#include <stdlib.h>
#include "extras.h"

char *alocar_str(int tam)
{
    char *vetor = (char *) malloc(sizeof(char) * tam);

    if(!vetor)
    {
        printf("Erro ao alocar vetor de char");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

void limpa_buffer()
{
    while(getchar() != '\n');
}

void leia_int(char *texto, int *variavel)
{
    printf("%s", texto);
    scanf("%d", variavel);
    limpa_buffer();
}

void leia_str(char *texto, char *variavel)
{
    printf("%s", texto);
    scanf("%[^\n]s", variavel);
    limpa_buffer();
}

void leia_float(char *texto, float *variavel)
{
    printf("%s", texto);
    scanf("%f", variavel);
    limpa_buffer();
}
