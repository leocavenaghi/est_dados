#include <iostream>
#include "fila.h"

using std::cout;

int main(){
    Fila fila;
    filaInit( &fila );

    filaEnqueue( &fila, 10);
    filaEnqueue( &fila, 1);
escreveFila( &fila );


    filaDequeue( &fila );
    filaDequeue( &fila );
escreveFila( &fila );

    filaEnqueue( &fila, 1);
    filaEnqueue( &fila, 1000);

    escreveFila( &fila );
    return 0;
}
