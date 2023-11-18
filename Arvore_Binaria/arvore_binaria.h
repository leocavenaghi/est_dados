#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct arvore
{
    char dado;
    struct arvore *esquerda;
    struct arvore *direita;
    struct arvore *pai;
} Arvore;

Arvore * novaArvore( char valor );
Arvore * insereArvore( Arvore *no, char valor );
Arvore * buscaArvore( Arvore *no, char procurado );
void removeArvore( Arvore *raiz, char valor);
void destroiArvore( Arvore *no );

void imprimeEmOrdem( Arvore *no );
void imprimePreOrdem( Arvore *no );
void imprimePosOrdem( Arvore *no );
void imprimeEmNivel( Arvore *no );



#endif // ARVORE_BINARIA_H
