typedef struct curso
{
    int cod;
    char *nome;
    int qt_periodos;
    //Arvore_Disciplinas disciplinas    <--(Importar .h<?>)
} Curso;

typedef struct arvorebb_curso
{
    Curso info;
    struct arvorebb_curso *esquerdo;
    struct arvorebb_curso *direito;
} ArvoreBB_Curso;

ArvoreBB_Curso *no_curso_cria(int codigo, char *nome, int qt_per);

ArvoreBB_Curso *arvorebb_curso_cria();

void arvorebb_curso_desaloca(ArvoreBB_Curso **raiz);

int arvorebb_curso_add(ArvoreBB_Curso **raiz, Curso *info);

void arvorebb_curso_exibir(ArvoreBB_Curso *raiz);

int arvorebb_curso_remover(ArvoreBB_Curso **raiz, int codigo);