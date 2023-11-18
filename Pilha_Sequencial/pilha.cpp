#include <iostream>
#include "pilha.h"

void pilhaInit(Pilha *pilha)
{
    pilha->topo = -1;
}

int pilhaIsEmpty(Pilha *pilha)
{
    if (pilha->topo == -1) {
        /*PILHA VAZIA*/
        return true;
    } else {
        return false;
    }
}

int pilhaIsFull(Pilha *pilha)
{
    if ( pilha->topo == (MAX_PILHA_SIZE - 1) ) {
        /* PILHA CHEIA*/
        return true;
    } else {
        return false;
    }
}

int pilhaPush(Pilha *pilha, int dado)
{
    if( ! pilhaIsFull(pilha) ) {
        /*INCREMENTA O TOPO E ARMAZENA O DADO*/
        pilha->dados[++pilha->topo] = dado;
        return true;
    }
    /* PILHA CHEIA */
    std::cout << "Overflow!\n";
    return false;
}

int pilhaPop(Pilha *pilha)
{
    if( ! pilhaIsEmpty(pilha) ) {
        /*REMOVE ELEMENTO DO TOPO (DECREMENTA VARIAVEL DE CONTROLE)*/
        return pilha->dados[pilha->topo--];
    } else {
        std::cout << "Underflow!\n";
        return false;
    }
}

int pilhaTop(Pilha *pilha)
{
    if ( ! pilhaIsEmpty(pilha) ) {
        /*RETORNA O ELEMENTO DO TOPO*/
        return pilha->dados[pilha->topo];
    } else {
        std::cout << "Underflow!\n";
        return false;
    }
}
