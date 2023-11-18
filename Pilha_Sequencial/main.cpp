#include <iostream>
#include "pilha.h"

using namespace std;

int main(){
    /* CRIA E INICIALIZA UMA PILHA*/
    Pilha p;
    pilhaInit(&p);

    /* VERIFICA O ELEMENTO DO TOPO*/
    cout << pilhaTop(&p) << "\n";

    /* INSERE ELEMENTOS NA PILHA*/
    pilhaPush(&p, 1);
    pilhaPush(&p, 2);
    pilhaPush(&p, 3);
    pilhaPush(&p, 4);
    pilhaPush(&p, 5);

    cout << "Pilha cheia? " << pilhaIsFull(&p) << "\n";
    pilhaPush(&p, 6);

    /* RETIRA 4 ELEMENTOS DA PILHA */
    for (int i = 0; i<3; i++) {
        if ( !pilhaIsEmpty(&p) )
            pilhaPop(&p);
    }

    /* INSERE ELEMENTOS NA PILHA*/
    pilhaPush(&p, 7);
    pilhaPush(&p, 8);

    /* VERIFICA O ELEMENTO DO TOPO*/
    if( !pilhaIsEmpty(&p) )
        cout << pilhaTop(&p) << "\n";

    return 0;
}
