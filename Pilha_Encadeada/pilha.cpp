#include <iostream>
#include "pilha.h"

void pilhaInit(Pilha *pilha)
{
    pilha->topo = nullptr;
}

int pilhaIsEmpty(Pilha *pilha)
{
    if( pilha->topo == nullptr) {
        return true;
    } else {
        return false;
    }
}

void pilhaPush(Pilha *pilha, int n)
{
    /*ALOCA MEM�RIA PARA O NOVO N�*/
    No *novo = new No;

    novo->valor = n;
    novo->proximo = pilha->topo;

    pilha->topo = novo;
}
void pilhaTop(Pilha *pilha )
{
    if( pilhaIsEmpty(pilha) ) {
        std::cout << "Pilha vazia\n";
    } else {
        std::cout << "Topo = " << pilha->topo->valor << "\n";
    }
}

int pilhaPop(Pilha *pilha)
{
    /*VERIFICA PILHA VAZIA*/
    if( pilhaIsEmpty(pilha) ) {
        std::cout << "Underflow\n";
    } else {
        /*ARMAZENA O N� DO TOPO EM VARIAVEL AUXILIAR*/
        No *aux;
        aux = pilha->topo;
        /*APONTA TOPO PARA O PEN�LTIMO ELEMENTO*/
        pilha->topo = pilha->topo->proximo;
        /*ARMAZENA VALOR DO TOPO*/
        int valor = aux->valor;
        delete(aux); //LIBERA MEM�RIA
        return valor;
    }
}

void escrevePilha (Pilha *pilha)
{
    if (pilhaIsEmpty(pilha)) {
        std::cout << "Pilha Vazia!\n";
        return;
    }
    std::cout << "TOPO -> ";
    for(No *aux = pilha->topo; aux != nullptr; aux = aux->proximo){
        std::cout << aux->valor << "\n\t";
    }
    std::cout << "\n";
}
