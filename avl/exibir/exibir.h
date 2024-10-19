#ifndef EXIBIR_H
#define EXIBIR_H

#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"

void exibir_alunos_do_curso(Lista *lista, int codigo_curso);

void exibir_todos_cursos(ArvoreAVL *raiz_curso);

void exibir_disciplinas_do_curso(ArvoreAVL *raiz_curso);

void exibir_disciplinas_do_periodo_curso(ArvoreAVL *raiz_disciplina, int periodo);

void exibir_disciplinas_do_aluno(Aluno aluno);

void exibir_disciplinas_do_periodo_aluno(ArvoreAVL *raiz_nota, int periodo);

void exibir_nota_da_disciplina_aluno(Aluno aluno, int codigo, ArvoreAVL *raiz_curso);

void exibir_historico(Aluno aluno, ArvoreAVL *raiz_curso);

#endif
