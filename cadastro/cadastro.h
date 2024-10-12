#ifndef CADASTRO_H
#define CADASTRO_H

#include "../lista_alunos/lista.h"
#include "../arvorebb/arvorebb.h"

void cadastrar_aluno(Lista **lista, ArvoreBB *raiz_curso);

void cadastrar_curso(ArvoreBB **raiz_curso);

void cadastrar_disciplina(ArvoreBB *raiz_curso);

void cadastrar_matricula(Lista *lista, ArvoreBB *raiz_curso);

void cadastrar_notas(Lista *lista);

#endif