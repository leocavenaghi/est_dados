#include <iostream>
#include "arvore_avl.h"

int main()
{
    No * raiz = nullptr;
//    raiz = insere(raiz, 10);
//    raiz = insere(raiz, 20);
//    raiz = insere(raiz, 30);
//    raiz = insere(raiz, 40);
//    raiz = insere(raiz, 50);
//    raiz = insere(raiz, 25);
//
//    raiz = insere(raiz, 42);
//    raiz = insere(raiz, 45);
    raiz = insere(raiz, 9);
    raiz = insere(raiz, 5);
    raiz = insere(raiz, 10);
    raiz = insere(raiz, 0);
    raiz = insere(raiz, 6);
    raiz = insere(raiz, 11);
    raiz = insere(raiz, -1);
    raiz = insere(raiz, 1);
    raiz = insere(raiz, 2);

    std::cout << "Arvore AVL em preOrdem:\n";
    imprimePreOrdem(raiz);

    raiz = deletar(raiz, 1);
    std::cout << "\nArvore AVL em preOrdem depois de deletar:\n";
    imprimePreOrdem(raiz);

    return 0;
}
