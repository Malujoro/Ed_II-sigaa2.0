#ifndef EXIBIR_H
#define EXIBIR_H

#include "../lista_alunos/lista.h"
#include "../arvorebb_curso/arvorebb_curso.h"

void exibir_alunos_do_curso(Lista *lista, int codigo_curso);

void exibir_todos_cursos(ArvoreBB_Curso *raiz);

void exibir_disciplinas_do_curso(ArvoreBB_Curso *raiz);

void exibir_disciplinas_do_periodo_curso(ArvoreBB_Disciplina *raiz, int periodo);

void exibir_disciplinas_do_aluno(Aluno aluno);

void exibir_disciplinas_do_periodo_aluno(ArvoreBB_Nota *raiz, int periodo);

void exibir_nota_da_disciplina_aluno(Nota nota);

void exibir_historico(Aluno aluno, ArvoreBB_Curso *raiz);

#endif
