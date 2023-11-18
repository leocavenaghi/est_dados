#ifndef FILA_H
#define FILA_H

#define MAX_FILA_SIZE 5

typedef struct {
    int tamanho, comeco, fim;
    int dados[MAX_FILA_SIZE];
} Fila;

void filaInit(Fila * fila);
int filaIsEmpty(Fila * fila);
int filaIsFull(Fila * fila);
int filaEnqueue(Fila * fila, int dado);
int filaDequeue(Fila * fila);

#endif // FILA_H
