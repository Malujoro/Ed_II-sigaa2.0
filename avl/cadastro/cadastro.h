#ifndef CADASTRO_H
#define CADASTRO_H

#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"

void cadastrar_aluno(Lista **lista, ArvoreAVL *raiz_curso);

void cadastrar_curso(ArvoreAVL **raiz_curso);

void cadastrar_disciplina(ArvoreAVL *raiz_curso);

void cadastrar_matricula(Lista *lista, ArvoreAVL *raiz_curso);

void cadastrar_notas(Lista *lista);

#endif