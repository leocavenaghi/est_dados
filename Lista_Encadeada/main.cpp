#include <iostream>
#include "lista.h"

int main () {
    Lista lista;
    listaInit( &lista );

    escreveLista( &lista );

    listaInsere( &lista, 5);
    listaInsere( &lista, 0);
    listaInsere( &lista, 10);
    listaInsere( &lista, 8);
    listaInsere( &lista, 1);

    escreveLista( &lista );

    listaRemove( &lista, 0);
    listaRemove( &lista, 1);

    escreveLista( &lista );
    return 0;
}
