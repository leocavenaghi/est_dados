#include <iostream>
#include "pilha.h"

using std::cout;

int main(){
    Pilha pilha;
    pilhaInit( &pilha );
    pilhaTop( &pilha );
    pilhaPush( &pilha, 10);
    pilhaPush( &pilha, 100);
    pilhaPush( &pilha, 5);
    escrevePilha( &pilha );
    cout << pilhaPop( &pilha ) << " Desempilhado!\n";
    pilhaPop( &pilha );
    pilhaPop( &pilha );
    pilhaTop( &pilha );
    pilhaPush( &pilha, 111);
    escrevePilha( &pilha );

    return 0;
}
