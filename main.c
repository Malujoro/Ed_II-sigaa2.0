#include <stdio.h>
#include "lista_alunos/lista.h"

int main()
{
    Lista *lista = lista_cria();

    // Aluno aluno1;
    // aluno1.codigo_curso = 321;
    // aluno1.matricula = 123;
    // aluno1.nome = "Mateus";
    // lista_add_ordenado(lista, aluno1);

    // aluno1.codigo_curso = 432;
    // aluno1.matricula = 234;
    // aluno1.nome = "Lucas";
    // lista_add_ordenado(lista, aluno1);
    
    // aluno1.codigo_curso = 543;
    // aluno1.matricula = 345;
    // aluno1.nome = "João";
    // lista_add_ordenado(lista, aluno1);

    // aluno1.codigo_curso = 543;
    // aluno1.matricula = 345;
    // aluno1.nome = "Lucia";
    // lista_add_ordenado(lista, aluno1);


    char palavras[102][100] = {"Mateus", "Lucas",  "Miguel", "Sophia", "Davi", "Alice", "Arthur", "Julia", "Pedro", "Isabella", "Gabriel", "Manuela", "Bernardo", "Laura", "Lucas", "Luiza", "Matheus", "Valentina", "Rafael", "Giovanna", "Heitor", "Maria Eduarda", "Enzo", "Helena", "Guilherme", "Beatriz", "Nicolas", "Maria Luiza", "Lorenzo", "Lara", "Gustavo", "Mariana", "Felipe", "Nicole", "Samuel", "Rafaela", "João Pedro", "Heloísa", "Daniel", "Isadora", "Vitor", "Lívia", "Leonardo", "Maria Clara", "Henrique", "Ana Clara", "Theo", "Lorena", "Murilo", "Gabriela", "Eduardo", "Yasmin", "Pedro Henrique", "Isabelly", "Pietro", "Sarah", "Cauã", "Ana Julia", "Isaac", "Letícia", "Caio", "Ana Luiza", "Vinicius", "Melissa", "Benjamin", "Marina", "João", "Clara", "Lucca", "Cecília", "João Miguel", "Esther", "Bryan", "Emanuelly", "Joaquim", "Rebeca", "João Vitor", "Ana Beatriz", "Thiago", "Lavínia", "Antônio", "Vitória", "Davi Lucas", "Bianca", "Francisco", "Catarina", "Enzo Gabriel", "Larissa", "Bruno", "Maria Fernanda", "Emanuel", "Fernanda", "João Gabriel", "Amanda", "Ian", "Alícia", "Davi Luiz", "Carolina", "Rodrigo", "Agatha", "Otávio", "Gabrielly"};

    Aluno aluno1;
    for(int i = 0; i < 204; i++)
    {
        aluno1.codigo_curso = 100 + i;
        aluno1.matricula = 999 - i;
        aluno1.nome = palavras[i % 102];
        lista_add_ordenado(lista, aluno1);
    }

    lista_exibir(lista);
    lista_desaloca(&lista);

    // int primeira = ordem_palavra(palavras[0], palavras[1]);
    // int segunda = 1 - primeira;
    // printf("[%s -> %s]\n", palavras[primeira], palavras[segunda]);
    return 0;
}