#ifndef REMOVER_H
#define REMOVER_H

#include "../arvorebb_disciplina/arvorebb_disciplina.h"
#include "../lista_alunos/lista.h"

int remover_disciplina_sem_alunos(ArvoreBB_Disciplina **raiz, int codigo_disciplina, Lista *lista);

int remover_matricula_aluno(Lista *aluno, int codigo_matricula);
#endif