#ifndef REMOVER_H
#define REMOVER_H

#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"

int remover_disciplina_sem_alunos(ArvoreBB **raiz_disciplina, int codigo_disciplina, Lista *lista);

int remover_matricula_aluno(Lista *aluno, int codigo_matricula);

#endif