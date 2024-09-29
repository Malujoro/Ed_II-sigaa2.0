#ifndef CADASTRO_H
#define CADASTRO_H

void cadastrar_aluno(Lista **lista, ArvoreBB_Curso *raiz);

void cadastrar_curso(ArvoreBB_Curso **raiz);

void cadastrar_disciplina(ArvoreBB_Curso *raiz);

void cadastrar_matricula(Lista *lista, ArvoreBB_Curso *raiz);

void cadastrar_notas(Lista *lista);

#endif
