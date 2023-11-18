#ifndef PILHA_H
#define PILHA_H

typedef struct no {
    int valor;
    struct no *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

void pilhaInit(Pilha *pilha);
int pilhaIsEmpty(Pilha *pilha);
void pilhaPush(Pilha *pilha, int n);
void pilhaTop(Pilha *pilha );
int pilhaPop(Pilha *pilha );
void escrevePilha( Pilha *pilha );


#endif // PILHA_H
