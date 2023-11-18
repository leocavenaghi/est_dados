#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

typedef struct no{
    int chave;
    int altura;
    struct no *esquerda;
    struct no *direita;
} No;

int max(int a, int b);
int altura(No *subArvore);
No* novoNo(int chave);
No* rotacaoDireita(No *y);
No* rotacaoEsquerda(No *x);
int verificaBalanceamento(No *subArvore);
No* insere(No * raiz, int valor);
No * deletar(No * raiz, int chave);
void imprimePreOrdem(No *raiz);

#endif // ARVORE_AVL_H
