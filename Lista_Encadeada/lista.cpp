#include <iostream>
#include "lista.h"

void listaInit(Lista *lista)
{
    /*INICIA A LISTA VAZIA*/
    lista->primeiro = nullptr;
}

void escreveLista(Lista *lista) {
    if (listaIsEmpty(lista) ) {
        std::cout << "Lista Vazia!\n";
        return;
    }

    No *pNo;
    for( pNo = lista->primeiro; pNo != nullptr; pNo = pNo->proximo){
        std::cout << pNo->valor << "\t";
    }
    std::cout << "\n";
}

int listaIsEmpty(Lista *lista)
{
    if(lista->primeiro == nullptr) {
        return true;
    } else {
        return false;
    }
}

void listaInsere(Lista *lista, int n)
{
    /*ALOCA MEMÓRIA PARA O NOVO NÓ (PONTEIRO)*/
    No *novo = new No;
    novo->valor = n;
    novo->proximo = nullptr;

    /*ACHA O LOCAL PARA INSERÇÃO (ORDENADA)*/
    No *pAnterior, *pAtual;
    pAnterior = nullptr;
    pAtual = lista->primeiro;

    while ( (pAtual != nullptr) && (pAtual->valor < n) ) {
        pAnterior = pAtual;
        pAtual =pAtual->proximo;
    }

    /*INSERE NOVO NÓ NO COMEÇO*/
    if( pAtual == lista->primeiro ) {
        novo->proximo = pAtual;
        lista->primeiro = novo;
    } else {
        /*INSERE NOVO NÓ ENTRE pAnterior E pAtual*/
        novo->proximo = pAtual;
        pAnterior->proximo = novo;
    }
}

void listaRemove(Lista *lista, int n)
{
    /*PROCURA O ELEMENTO*/
    No *pAnterior, *pAtual;
    pAnterior = nullptr;
    pAtual = lista->primeiro;

    while ( (pAtual != nullptr) && (pAtual->valor != n) ) {
        pAnterior = pAtual;
        pAtual =pAtual->proximo;
    }

    /*VERIFICA SE O ELEMENTO EXISTE NA LISTA*/
    if ( pAtual == nullptr ) {
        std::cout << "Elemento nao existe na lista\n";
    } else {
        if ( pAtual == lista->primeiro) {/*REMOVE DO INICIO*/
            lista->primeiro = pAtual->proximo;
        } else { /*REMOVE DO MEIO DA LISTA*/
            pAnterior->proximo = pAtual->proximo;
        }
        delete(pAtual); //libera memória
    }
}
