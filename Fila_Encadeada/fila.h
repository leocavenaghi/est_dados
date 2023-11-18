#ifndef FILA_H

#define FILA_H

typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct {
    No *comeco, *fim;
} Fila;

void filaInit(Fila *fila);
int filaIsEmpty(Fila *fila);
void filaEnqueue(Fila *fila, int n);
void filaDequeue(Fila *fila);
void escreveFila(Fila *fila);

#endif // FILA_H
