#ifndef PILHA_H
#define PILHA_H

typedef struct no{
    char operador;
    struct no *proximo;
} No;

typedef struct pilha{
    No *topo;
} Pilha;

typedef struct no No;
typedef struct pilha Pilha;

void iniciaPilha(Pilha *pilha );
bool isEmpty(Pilha *pilha);
void push(Pilha *pilha, char operador);
char top(Pilha *pilha);
char pop(Pilha *pilha);

#endif // PILHA_H
