#include <iostream>
#include "arvore_binaria.h"

int main()
{
    Arvore * raiz = novaArvore('f');
    insereArvore( raiz, 'b');
    insereArvore( raiz, 'a');
    insereArvore( raiz, 'd');
    insereArvore( raiz, 'c');
    insereArvore( raiz, 'e');
    insereArvore( raiz, 'g');
    insereArvore( raiz, 'i');
    insereArvore( raiz, 'h');

    std::cout << "Percurso em ordem:\n";
    imprimeEmOrdem( raiz );

    std::cout << "\nPercurso pre ordem:\n";
    imprimePreOrdem( raiz );
    std::cout << "\nPercurso pos ordem:\n";
    imprimePosOrdem( raiz );

    std::cout << "\nPercurso em nivel:\n";
    imprimeEmNivel( raiz );


    removeArvore(raiz, 'g');
    Arvore *subarvore = buscaArvore(raiz, 'i');
    destroiArvore(subarvore);
    std::cout << "\nPercurso em ordem apos destruicao da subarvore:\n";
    imprimeEmOrdem( raiz );
    return 0;
}
