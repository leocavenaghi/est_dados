#include <iostream>
#include <queue>
#include "arvore_binaria.h"

/*CRIA UM NOVO NÓ*/
Arvore * novaArvore( char valor )
{
    Arvore * no = new Arvore;
    no->dado = valor;
    no->esquerda = nullptr;
    no->direita = nullptr;
    no->pai = nullptr;

    return no;
}

Arvore * insereArvore( Arvore *no, char valor )
{
    static Arvore *p;

    /*SE ARVORE VAZIA INSERE NA RAIZ*/
    if( no == nullptr ) {
        Arvore *novo = novaArvore(valor);
        novo->pai = p;
        return novo;
    }
    /*CAMINHA NA ARVORE PARA INSERIR NA ORDEM*/
    p = no; /*NÓ PAI*/
    if( valor < no->dado ) {
        no->esquerda = insereArvore( no->esquerda, valor);
    } else {
        no->direita = insereArvore( no->direita, valor);
    }
    return no;
}

Arvore * buscaArvore( Arvore * no, char procurado)
{
    /*NÃO ENCONTROU ELEMENTO RETORNA 'VAZIO'*/
    if( no == nullptr) {
        return nullptr;
    }

    if( no->dado == procurado) {
        /*RETORNA NO QUE CONTEM ELEMENTO*/
        return no;
    } else {
        /*CAMINHA NA ARVORE DE ACORDO COM A ORDEM*/
        if( procurado < no->dado ) {
            return buscaArvore(no->esquerda, procurado);
        } else {
            return buscaArvore(no->direita, procurado);
        }
    }
}

char maiorArvore(Arvore *no)
{
    while(no->direita) {
        no = no->direita;
    }
    return no->dado;
}

char predecessorEmOrdem(Arvore *no)
{
    /*SE POSSUI FILHO ESQUERDO PEGA O MAIOR ELEMENTO*/
    if (no->esquerda)
        return maiorArvore(no->esquerda);

    Arvore *y = no->pai;
    while(no == y->esquerda) {
        no = y;
        y = no->pai;
    }

    return y->dado;
}

void removeArvore( Arvore *raiz, char valor)
{
    Arvore *no, *pai, *filho, *predecessor;
    /*LOCALIZA O NÓ A SER REMOVIDO*/
    no = buscaArvore(raiz, valor);

    /*SE FOR FOLHA APENAS REMOVE*/
    if(no->esquerda == nullptr && no->direita == nullptr) {
        /*APAGA A REFERENCIA NO NÓ PAI*/
        if(no->pai) {pai = no->pai;}
        if(no == pai->esquerda) {
            pai->esquerda = nullptr;
        }
        else if(no == pai->direita) {
            pai->direita = nullptr;
        }
        delete no;
        return;
    }

    /*SE TIVER DOIS FILHOS SUBSTITUI PELO SEU PREDECESSOR*/
    if( no->esquerda && no->direita) {
        char ch_predecessor = predecessorEmOrdem(no);
        predecessor = buscaArvore(raiz, ch_predecessor);
        if(predecessor->pai->esquerda == predecessor) {
            predecessor->pai->esquerda = nullptr;
        } else if(predecessor->pai->direita == predecessor) {
            predecessor->pai->direita = nullptr;
        }
        no->dado = predecessor->dado;
        delete predecessor;
        return;
    }

    /*APENAS UM FILHO*/
    /*SUBSTITUI PELO FILHO E DELETA*/
    if(no->esquerda) {
        filho = no->esquerda;
    } else if(no->direita) {
        filho = no->direita;
    }
    pai = no->pai;
    if(pai->esquerda && pai->esquerda == no) {
        pai->esquerda = filho;
    } else if(pai->direita && pai->direita == no) {
        pai->direita = filho;
    }
    filho->pai = pai;
    delete no;
    return;
}

void destroiArvore( Arvore *no )
{
    /*REALIZA PERCURSO PÓS-ORDEM APAGANDO NÓS*/
    if( no != nullptr ) {
        destroiArvore(no->esquerda);
        destroiArvore(no->direita);

        /*APAGA A REFERENCIA NO NÓ PAI*/
        if(no->pai && no->pai->esquerda == no) {
            no->pai->esquerda = nullptr;
        }
        if(no->pai && no->pai->direita == no) {
            no->pai->direita = nullptr;
        }

        /*LIBERA MEMÓRIA*/
        delete no;
    }
}

void imprimeEmOrdem( Arvore *no )
{
    if( no == nullptr ) return;

    imprimeEmOrdem( no->esquerda );
    std::cout << no->dado << " ";
    imprimeEmOrdem( no->direita );
}

void imprimePreOrdem( Arvore *no )
{
    if( no == nullptr ) return;

    std::cout << no->dado << " ";
    imprimePreOrdem( no->esquerda );
    imprimePreOrdem( no->direita );
}

void imprimePosOrdem( Arvore *no )
{
    if( no == nullptr ) return;

    imprimePosOrdem( no->esquerda );
    imprimePosOrdem( no->direita );
    std::cout << no->dado << " ";
}

void imprimeEmNivel( Arvore *raiz )
{
    /*ESTRUTRA FILA*/
    std::queue<Arvore*> fila;
    Arvore *no;

    if(raiz != nullptr){
        fila.push(raiz);

        while( !fila.empty() ) {
            no = fila.front();
            fila.pop();
            if( no->esquerda != nullptr) fila.push(no->esquerda);
            if( no->direita != nullptr) fila.push( no->direita );
            std::cout << no->dado << " ";
        }
    }
}
