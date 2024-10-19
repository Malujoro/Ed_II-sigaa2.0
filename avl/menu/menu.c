#include <stdio.h>
#include "menu.h"
#include "../../extras/extras.h"
#include "../cadastro/cadastro.h"
#include "../exibir/exibir.h"
#include "../remover/remover.h"
#include "../lista_alunos/lista.h"
#include "../arvore/arvore.h"


void exibir_opcoes()
{
    // Opções de Cadastro
    printf("----------[Menu]----------");
    printf("\n[01] - Cadastrar aluno");
    printf("\n[02] - Cadastrar curso");
    printf("\n[03] - Cadastrar disciplina");
    printf("\n[04] - Cadastrar matrícula");
    printf("\n[05] - Cadastrar notas");
    // Opções de Exibição
    printf("\n[06] - Exibir alunos de um curso");
    printf("\n[07] - Exibir todos os cursos");
    printf("\n[08] - Exibir disciplinas de um curso");
    printf("\n[09] - Exibir disciplinas de um período");
    printf("\n[10] - Exibir disciplinas matriculadas de um aluno");
    printf("\n[11] - Exibir disciplinas de um período de um aluno");
    printf("\n[12] - Exibir nota de uma disciplina do aluno");
    // Opções de Remoção
    printf("\n[13] - Remover disciplina de um curso");
    printf("\n[14] - Remover matrícula de uma disciplina");
    // Opção de Histórico
    printf("\n[15] - Exibir histórico do aluno");
    printf("\n[00] - Sair do programa");
}

void iniciar_programa()
{
    int op, codigo, periodo, matricula, semestre;

    Lista *lista_alunos;
    lista_alunos = lista_cria();

    ArvoreAVL *arvoreavl_curso_raiz;
    arvoreavl_curso_raiz = arvoreavl_cria();

    Lista *aluno_buscado;
    aluno_buscado = NULL;

    ArvoreAVL *curso_buscado;
    curso_buscado = NULL;
    
    do
    {
        exibir_opcoes();
        leia_int("\nOpção: ", &op);
        printf("\n");

        switch(op)
        {
            case 1:
                cadastrar_aluno(&lista_alunos, arvoreavl_curso_raiz);
                break;

            case 2:
                cadastrar_curso(&arvoreavl_curso_raiz);
                break;

            case 3:
                cadastrar_disciplina(arvoreavl_curso_raiz);
                break;

            case 4:
                cadastrar_matricula(lista_alunos, arvoreavl_curso_raiz);
                break;

            case 5:
                cadastrar_notas(lista_alunos);
                break;

            case 6:
                leia_int("\nCódigo do curso: ", &codigo);
                exibir_alunos_do_curso(lista_alunos, codigo);
                break;

            case 7:
                exibir_todos_cursos(arvoreavl_curso_raiz);
                break;

            case 8:
                leia_int("\nCódigo do curso: ", &codigo);
                curso_buscado = arvoreavl_buscar(arvoreavl_curso_raiz, codigo);
                if(curso_buscado != NULL)
                    exibir_disciplinas_do_curso(curso_buscado);
                else
                    printf("\nCurso não encontrado\n");
                break;

            case 9:
                leia_int("\nCódigo do curso: ", &codigo);
                curso_buscado = arvoreavl_buscar(arvoreavl_curso_raiz, codigo);
                if(curso_buscado != NULL)
                {
                    leia_int("\nPeríodo: ", &periodo);
                    if(periodo > 0 && periodo <= curso_buscado->info.curso.qt_periodos)
                        exibir_disciplinas_do_periodo_curso(curso_buscado->info.curso.arvavl_disciplina, periodo);
                    else
                        printf("\nPeríodo inválido\n");
                }
                else
                    printf("\nCurso não encontrado\n");
                break;

            case 10:
                leia_int("\nMatrícula do aluno: ", &matricula);
                aluno_buscado = lista_alunos_buscar(lista_alunos, matricula);
                if(aluno_buscado != NULL)
                    exibir_disciplinas_do_aluno(aluno_buscado->info);
                else
                    printf("\nAluno não encontrado\n");
                break; 

            case 11:
                leia_int("\nMatrícula do aluno: ", &matricula);
                aluno_buscado = lista_alunos_buscar(lista_alunos, matricula);
                if(aluno_buscado != NULL)
                {
                    leia_int("\nSemestre do aluno: ", &semestre);
                    exibir_disciplinas_do_periodo_aluno(aluno_buscado->info.arvavl_nota, semestre);
                }
                else
                    printf("\nAluno não encontrado\n");
                break;

            case 12:
                leia_int("\nMatrícula do aluno: ", &matricula);
                aluno_buscado = lista_alunos_buscar(lista_alunos, matricula);
                if(aluno_buscado != NULL)
                {
                    leia_int("\nMatrícula da Disciplina: ", &codigo);
                    exibir_nota_da_disciplina_aluno(aluno_buscado->info, codigo, arvoreavl_curso_raiz);
                }
                else
                    printf("\nAluno não encontrado\n");
                break;

            case 13:
                leia_int("\nCódigo do curso: ", &codigo);
                curso_buscado = arvoreavl_buscar(arvoreavl_curso_raiz, codigo);
                if(curso_buscado != NULL)
                {
                    leia_int("\nCódigo da disciplina: ", &codigo);
                    if(remover_disciplina_sem_alunos(&(curso_buscado->info.curso.arvavl_disciplina), codigo, lista_alunos))
                        printf("\nDisciplina removida com sucesso\n");
                    else
                        printf("\nNão foi possível remover a disciplina\n");
                }
                else
                    printf("\nCurso não encontrado\n");
                break;

            case 14:
                leia_int("\nMatrícula do aluno: ", &matricula);
                aluno_buscado = lista_alunos_buscar(lista_alunos, matricula);
                if(aluno_buscado != NULL)
                {
                    leia_int("\nMatrícula na Disciplina: ", &matricula);
                    if(remover_matricula_aluno(aluno_buscado, matricula))
                        printf("\nMatrícula na disciplina removida com sucesso\n");
                    else
                        printf("\nMatrícula não encontrada\n");
                }
                else
                    printf("\nAluno não encontrado\n");
                break;

            case 15:
                leia_int("\nMatrícula do aluno: ", &matricula);
                aluno_buscado = lista_alunos_buscar(lista_alunos, matricula);
                if(aluno_buscado != NULL)
                    exibir_historico(aluno_buscado->info, arvoreavl_curso_raiz);
                else
                    printf("\nAluno não encontrado\n");
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpção inválida\n");
                break;
        }
        printf("\n");
    }while(op != 0);
    lista_desaloca(&lista_alunos);
    arvoreavl_curso_desaloca(&(arvoreavl_curso_raiz));
}