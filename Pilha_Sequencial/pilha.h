#ifndef PILHA_H
#define PILHA_H

#define MAX_PILHA_SIZE 5

typedef struct {
    int topo;
    int dados[MAX_PILHA_SIZE];
} Pilha;

void pilhaInit(Pilha *pilha);
int pilhaIsEmpty(Pilha *pilha);
int pilhaIsFull(Pilha *pilha);
int pilhaPush(Pilha *pilha, int dado);
int pilhaPop(Pilha *pilha);
int pilhaTop(Pilha *pilha);

#endif // PILHA_H
