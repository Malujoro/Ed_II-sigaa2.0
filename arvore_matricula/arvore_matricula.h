typedef struct no_matricula
{
    int info;
    struct no_matricula *esquerdo;
    struct no_matricula *direito;
} No_Matricula;

No_Matricula *no_matricula_cria(int matricula);
No_Matricula *arvore_matricula_cria();
void arvore_matricula_desaloca(No_Matricula **raiz);

void arvore_matricula_add(No_Matricula **raiz, int matricula);

void arvore_matricula_exibir(No_Matricula *raiz);

No_Matricula *arvore_matricula_remover_no(No_Matricula **raiz);
No_Matricula *arvore_matricula_remover(No_Matricula **raiz, int matricula);