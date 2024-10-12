#ifndef EXIBIR_H
#define EXIBIR_H

#include "../lista_alunos/lista.h"
#include "../arvorebb/arvorebb.h"

void exibir_alunos_do_curso(Lista *lista, int codigo_curso);

void exibir_todos_cursos(ArvoreBB *raiz_curso);

void exibir_disciplinas_do_curso(ArvoreBB *raiz_curso);

void exibir_disciplinas_do_periodo_curso(ArvoreBB *raiz_disciplina, int periodo);

void exibir_disciplinas_do_aluno(Aluno aluno);

void exibir_disciplinas_do_periodo_aluno(ArvoreBB *raiz_nota, int periodo);

void exibir_nota_da_disciplina_aluno(Nota nota);

void exibir_historico(Aluno aluno, ArvoreBB *raiz_curso);

#endif
