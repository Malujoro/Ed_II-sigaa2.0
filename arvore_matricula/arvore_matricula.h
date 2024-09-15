typedef struct no_matricula
{
    int info;
    struct no_matricula *esquerdo;
    struct no_matricula *direito;
} No_Matricula;

typedef struct arvore_matricula
{
    No_Matricula *raiz;
} Arvore_Matricula;

No_Matricula *no_matricula_cria(int matricula);

Arvore_Matricula *arvore_matricula_cria();

void no_matricula_desaloca(No_Matricula **no);

void arvore_matricula_desaloca(Arvore_Matricula **arvore_matricula);

void arvore_matricula_add(Arvore_Matricula *arvore_matricula, int matricula);

void arvore_matricula_exibir(No_Matricula *raiz);

No_Matricula *arvore_matricula_remover_no_esquerdo(No_Matricula *raiz);
No_Matricula *arvore_matricula_remover_no_direito(No_Matricula *raiz);
No_Matricula *arvore_matricula_remover_no_raiz(Arvore_Matricula *arvore);
No_Matricula *arvore_matricula_remover(Arvore_Matricula *arvore, int matricula);