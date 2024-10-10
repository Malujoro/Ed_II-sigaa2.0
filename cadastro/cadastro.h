#ifndef CADASTRO_H
#define CADASTRO_H

#include "../lista_alunos/lista.h"
#include "../arvorebb_curso/arvorebb_curso.h"

void cadastrar_aluno(Lista **lista, ArvoreBB_Curso *raiz);

void cadastrar_curso(ArvoreBB_Curso **raiz);

void cadastrar_disciplina(ArvoreBB_Curso *raiz);

void cadastrar_matricula(Lista *lista, ArvoreBB_Curso *raiz);

void cadastrar_notas(Lista *lista);

#endif
