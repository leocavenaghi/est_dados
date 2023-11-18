#include <iostream>
#include <cstddef>
#include "arvore_avl.h"

int max(int a, int b)
{
    return (a > b)? a : b;
}

int altura(No *subArvore)
{
    if( subArvore == nullptr ){
        /*ARVORE VAZIA -> ALTURA ZERO*/
        return 0;
    }
    return subArvore->altura;
}

No* novoNo(int chave)
{
    No * novo = new No;

    novo->chave = chave;
    novo->esquerda = nullptr;
    novo->direita = nullptr;
    novo->altura = 1; /*FOLHA -> ALTURA 1*/

    return novo;
}
No* rotacaoDireita(No *y)
{
    No * x = y->esquerda;
    No * T2 = x->direita;

    /*ROTAÇÃO*/
    x->direita = y;
    y->esquerda = T2;

    /*ATUALIZA ALTURAS*/
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No* rotacaoEsquerda(No *x)
{
    No * y = x->direita;
    No * T2 = y->esquerda;

    /*ROTAÇÃO*/
    y->esquerda = x;
    x->direita = T2;

    /*ATUALIZA ALTURAS*/
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int verificaBalanceamento(No *subArvore)
{
    if( subArvore == nullptr ) {
        return 0;
    }
    return altura(subArvore->esquerda) - altura(subArvore->direita);
}
No* insere(No * raiz, int valor)
{
    /*1 INSERCAO NORMAL DE ARVORE BINARIA DE BUSCA*/
    if (raiz == nullptr)
        return novoNo(valor);

    if (valor < raiz->chave) {
        raiz->esquerda = insere(raiz->esquerda, valor);
    } else if (valor > raiz->chave) {
        raiz->direita = insere(raiz->direita, valor);
    } else { /*NOSSA ARVORE DE BUSCA NAO ACEITARA CHAVES IGUAIS*/
        return raiz;
    }

    /*2 ATUALIZAR A ALTURA DOS ANCESTRAIS DO NÓ*/
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

    /*3 VERIFICA O FATOR DE BALANCEAMENTO*/
    int balanco = verificaBalanceamento(raiz);

    /*BALANCO > 1 ARVORE ESQUERDA MAIS ALTA*/
    //ROTACAO SIMPLES
    if(balanco > 1 && valor < raiz->esquerda->chave)
        return rotacaoDireita(raiz);
    //ROTACAO DUPLA
    if(balanco > 1 && valor > raiz->esquerda->chave) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    /*BALANCO < -1 ARVORE DIREITA MAIS ALTA*/
    //ROTACAO SIMPLES
    if(balanco < -1 && valor > raiz->direita->chave)
        return rotacaoEsquerda(raiz);
    //ROTACAO DUPLA
    if(balanco < -1 && valor < raiz->direita->chave) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    /*ARVORE BALANCEADA MESMO APOS INSERCAO*/
    return raiz;
}

No * noMenorValor( No * subArvore )
{
    No * atual = subArvore;

    while (atual->esquerda != nullptr)
        atual = atual->esquerda;

    return atual;
}

No * deletar(No * raiz, int chave)
{
    /*1 REMOCAO NORMAL DE ARVORE BINARAIA DE BUSCA*/
    if (raiz == nullptr)
        return raiz;
    if( chave < raiz->chave ) {
        raiz->esquerda = deletar(raiz->esquerda, chave);
    } else if ( chave > raiz->chave ) {
        raiz->direita = deletar(raiz->direita, chave);
    } else { /*CHAVE A SER DELETADA ENCONTRADA*/
        if( (raiz->esquerda == nullptr) || (raiz->direita == nullptr) ) {
            /*NÓ NÃO POSSUA UM DOS FILHOS*/
            No * tmp = (raiz->esquerda) ? raiz->esquerda : raiz->direita;
            /*NO FOLHA -> NADA A SER FEITO*/
            if (tmp == nullptr ) {
                tmp = raiz;
                raiz = nullptr;
            } else { /*POSSUI APENAS 1 FILHO*/
                *raiz = *tmp; /*ALTERA O ENDERECO DE MEMORIA APONTADO*/
            }
            /*LIBERA MEMORIA*/
            delete tmp;
        } else { /*POSSUI 2 FILHOS*/
            No * tmp = noMenorValor( raiz->direita );
            raiz->chave = tmp->chave;
            raiz->direita = deletar(raiz->direita, tmp->chave);
        }
    }
    if (raiz == nullptr )
        return raiz;

    /*2 ATUALIZA ALTURA DO NÓ*/
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

    /*3 VERIFICA BALANCEAMENTO DO NO*/
    int balanco = verificaBalanceamento(raiz);

    //REALIZA ROTACAO CASO ESTEJA DESBALANCEADO
    if (balanco > 1 && verificaBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    if (balanco > 1 && verificaBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balanco < -1 && verificaBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    if(balanco < -1 && verificaBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void imprimePreOrdem(No * raiz)
{
    if( raiz == nullptr ) return;

    std::cout << raiz->chave << " altura => " << raiz->altura << "\n";
    imprimePreOrdem( raiz->esquerda );
    imprimePreOrdem( raiz->direita );
}
