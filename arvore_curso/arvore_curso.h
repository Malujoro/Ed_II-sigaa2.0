#include <stdio.h>

typedef struct curso
{
    int cod;
    char *nome;
    int qt_periodos;
    //Arvore_Disciplinas disciplinas    <--(Importar .h<?>)
} Curso;

typedef struct no_curso
{
    Curso info;
    No_Curso *esquerdo;
    No_Curso *direito;
} No_Curso;

No_Curso *no_curso_cria(int codigo, char *nome, int qt_per);

No_Curso *arvore_curso_cria();

void arvore_curso_desaloca(No_Curso **raiz);

void arvore_curso_add(No_Curso **raiz, Curso *info);

void exibir_arvore_curso(No_Curso *raiz);

No_Curso *arvore_curso_remover_no(No_Curso **raiz);

No_Curso *remover_arvore_curso(No_Curso **raiz, Curso *curso);
