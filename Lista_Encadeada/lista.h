#ifndef LISTA_H
#define LISTA_H

/*estrutura do nó*/
typedef struct no {
    int valor;
    struct no * proximo;
} No;

typedef struct lista {
    No * primeiro;
} Lista;

void listaInit(Lista *lista);
void escreveLista(Lista *lista);
int listaIsEmpty(Lista *lista);
void listaInsere(Lista *lista, int n);
void listaRemove(Lista *lista, int n);

#endif // LISTA_H
