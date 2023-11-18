#include <iostream>
#include "fila.h"

void filaInit(Fila *fila)
{
    fila->comeco = nullptr;
    fila->fim = nullptr;
}

int filaIsEmpty(Fila *fila)
{
    if( fila->comeco == nullptr) {
        return true;
    } else {
        return false;
    }
}

void filaEnqueue(Fila *fila, int n)
{
    /*CRIA NOVO NO*/
    No *novo = new No;
    novo->valor = n;
    novo->proximo = nullptr;

    /*SE A FILA ESTAVA VAZIA APONTA O COMEÇO PARA NOVO ELEMENTO*/
    if(filaIsEmpty(fila)) {
        fila->comeco = novo;
    }
    /*APONTA ULTIMO ELEMENTO (SE EXISTIR) PARA O NOVO*/
    if( fila->fim != nullptr ) {
        fila->fim->proximo = novo;
    }
    /*APONTA FINAL DA FILA PARA NOVO ELEMENTO*/
    fila->fim = novo;
}

void filaDequeue(Fila *fila)
{
    if( filaIsEmpty(fila) ) {
        std::cout << "Fila Vazia!\n";
    } else {
        /*ARMAZENA NO A SER RETIRADO EM VARIAVEL AUXILIAR*/
        No *aux = fila->comeco;

        /*APONTA COMEÇO DA FILA PARA SEGUNDO ELEMENTO*/
        fila->comeco = aux->proximo;
        /*VERIFICA SE A FILA FICOU VAZIA*/
        if (fila->comeco == nullptr) {
            fila->fim = nullptr;
        }

        std::cout << "Valor " << aux->valor << " retirado da fila!\n";
        delete aux;
    }
}

void escreveFila(Fila *fila)
{
    if(filaIsEmpty(fila)) {
        std::cout << "Fila Vazia!\n";
    } else{
        std::cout << "FILA:\n";
        /*PERCORRE A FILA DO PRIMEIRO AU ULTIMO NÓ*/
        for(No *no = fila->comeco; no != nullptr; no = no->proximo) {
            std::cout << no->valor << "\t";
        }
        std::cout << "\n";
    }
}
