#include <iostream>
#include "fila.h"

using std::cin;
using std::cout;

int main() {
    /*CRIA E INICIALIZA FILA*/
    Fila f;
    filaInit(&f);

    cout << "Fila vazia? " << filaIsEmpty(&f) << "\n";
    cout << "Fila cheia? " << filaIsFull(&f) << "\n";

    filaEnqueue(&f,100);
    filaEnqueue(&f,21);
    filaEnqueue(&f,66);
    filaEnqueue(&f,106);
    filaEnqueue(&f,15);
    filaEnqueue(&f,10);
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";
    cout << filaDequeue(&f) << "\n";


    return 0;
}
