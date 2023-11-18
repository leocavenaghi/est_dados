#include <iostream>
#include "fila.h"

void filaInit(Fila * fila)
{
	fila->comeco = 0;
	fila->fim = 0;
	fila->tamanho = 0;
}

int filaIsEmpty(Fila * fila)
{
	if (fila->tamanho == 0) {
		return true;
	} else {
		return false;
	}
}

int filaIsFull(Fila * fila)
{
	if (fila->tamanho == MAX_FILA_SIZE) {
		return true;
	} else {
		return false;
	}
}

int incremento(int posicao)
{
    posicao = posicao + 1;
    if ( posicao > MAX_FILA_SIZE -1 ) {
        /*INDICE DO VETOR COMEÇA EM 0*/
        posicao = 0;
    }
    return posicao;
}

int filaEnqueue(Fila * fila, int dado)
{
	if( ! filaIsFull(fila) ) {
		fila->dados[fila->fim] = dado;
		fila->fim = incremento(fila->fim);
		fila->tamanho++;
	} else {
		std::cout << "Overflow\n";
		return false;
	}
}
int filaDequeue(Fila * fila)
{
	if ( ! filaIsEmpty(fila) ) {
        int valor = fila->dados[fila->comeco];
        fila->comeco = incremento(fila->comeco);
        fila->tamanho--;
		return valor;
	} else {
		std::cout << "Underflow\n";
		return false;
	}
}
