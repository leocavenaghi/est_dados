#ifndef LISTA_H
#define LISTA_H

#define MAX_LISTA_SIZE 5

typedef struct {
    int fim;
    int dados[MAX_LISTA_SIZE];
} Lista;

void listaInit(Lista * lista);
int listaIsEmpty(Lista * lista);
int listaIsFull(Lista * lista);
int listaInsere(Lista * lista, int dado);
int listaRemove(Lista * lista, int dado);

#endif // LISTA_H
