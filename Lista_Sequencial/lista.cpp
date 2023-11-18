#include <iostream>
#include "lista.h"

void listaInit(Lista *lista)
{
    lista->fim = -1;
    /*ATRIBUI ZERO PARA TODOS OS VALORES DA LITA*/
    for( int i = 0; i < MAX_LISTA_SIZE; i++) {
        lista->dados[i] = 0;
    }
}

int listaIsEmpty(Lista *lista)
{
    if( lista->fim == -1){
        return true;
    } else {
        return false;
    }
}

int listaIsFull(Lista *lista)
{
    if( lista->fim == MAX_LISTA_SIZE -1){
        return true;
    } else {
        return false;
    }
}

int listaInsere(Lista *lista, int dado)
{
    if( !listaIsFull(lista)) {
        /*PROCURA A POSIÇÃO DE INSERÇÃO*/
        int i = 0, posicao;

        while( (lista->dados[i] != 0) && (dado > lista->dados[i]) ) {
            i++; //anota a posição
        }
        posicao = i;
        i = lista->fim;
        /*DESLOCA DADOS APOS POSIÇÃO DE INSEÇÃO */
        while( i != posicao - 1 ) {
            lista->dados[i+1] = lista->dados[i];
            i--;
        }
        /*INSERE ELEMENTO E ATUALIZA CONTROLE */
        lista->fim++;
        lista->dados[posicao] = dado;
        return true;
    } else {
        std::cout << "Overflow\n";
        return false;
    }
}

int listaRemove(Lista *lista, int dado)
{
    if( !listaIsEmpty(lista) ) {
        /*PROCURA A POSIÇÂO DO ELEMENTO*/
        int i = 0, posicao;
        while( (i <= lista->fim) && (lista->dados[i] != dado) ) {
            i++;
        }
        /*VERIFICA SE O ELEMENTO EXISTE*/
        if( i > lista->fim) {
            std::cout << "Elemento nao encontrado\n";
            return false;
        }
        /*REMOVE ELEMENTO DESLOCANDO OS DEMAIS*/
        while( i!= lista->fim) {
            lista->dados[i] = lista->dados[i+1];
            i++;
        }
        /*AJUSTA CONTROLE*/
        lista->dados[lista->fim] = 0;
        lista->fim--;
        return true;
    } else {
        std::cout << "Underflow\n";
        return false;
    }
}
