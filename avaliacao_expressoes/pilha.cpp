#include "pilha.h"

void iniciaPilha(Pilha *pilha )
{
    pilha->topo = nullptr;
}

bool isEmpty(Pilha *pilha)
{
    return (pilha->topo == nullptr);
}

void push(Pilha *pilha, char operador)
{
    No *novo = new No;
    novo->operador = operador;
    novo->proximo = pilha->topo;

    pilha->topo = novo;
}

char top(Pilha *pilha)
{
    return (pilha->topo->operador);
}

char pop(Pilha *pilha)
{
    No *aux = pilha->topo;

    pilha->topo = pilha->topo->proximo;
    char operador = aux->operador;
    delete(aux);

    return operador;
}
