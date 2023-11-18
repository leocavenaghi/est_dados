#include <iostream>
#include "lista.h"

using std::cout;
using std::cin;

int main(){
    Lista lista;
    listaInit( &lista );

    listaInsere(&lista,10);
    listaInsere(&lista,7);
    listaInsere(&lista,6);
    listaInsere(&lista,10);
    listaInsere(&lista,1);
    listaInsere(&lista,10);
    listaInsere(&lista,10);

    listaRemove(&lista,10);

    for(int i=0; i <= lista.fim; i++) {
        cout << i << " = " << lista.dados[i] << "\n";
    }

    return 0;
}
