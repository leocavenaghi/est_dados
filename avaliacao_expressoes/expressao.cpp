#include "expressao.h"
#include "pilha.h"

int Prioridade(char caracter) {
    switch( caracter ){
        case '(':
            return 1;
            break;
        case '+':
        case '-':
            return 2;
            break;
        case '*':
        case '/':
            return 3;
            break;
    }
}

std::string infixaToPosfixa(std::string expressao)
{
    Pilha pilha;
    iniciaPilha( &pilha );

    std::string posfixa;

    for (int i = 0; i < expressao.length() ; i++) {
        if(isalnum(expressao[i]) ) {
            posfixa += expressao[i];
        } else {
            if( expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/' ) {
                while( !isEmpty(&pilha)
                      && ( Prioridade(top(&pilha)) >= Prioridade(expressao[i]) )
                ) {
                    posfixa += pop( &pilha );
                }
                push( &pilha, expressao[i] );
            } else {
                if(expressao[i] == '(') {
                    push( &pilha, expressao[i] );
                } else {
                    if( expressao[i] == ')') {
                        while( top(&pilha) != '(' ) {
                            posfixa += pop(&pilha);
                        }
                        pop( &pilha );
                    }
                }
            }
        }
    }
    while( !isEmpty(&pilha) ) {
        posfixa += pop( &pilha );
    }
    return posfixa;
}

int avalia(std::string posfixa)
{
    Pilha pilha;
    iniciaPilha( &pilha );
    int a,b;

    for(int i = 0; i < posfixa.length(); i++) {
        if( isdigit(posfixa[i]) ) {
            push( &pilha, posfixa[i] );
        } else {
            b = pop( &pilha ) - '0';
            a = pop( &pilha ) - '0';
            switch(posfixa[i]) {
                case '+':
                    push( &pilha, a+b + '0');
                    break;
                case '-':
                    push( &pilha, a-b + '0');
                    break;
                case '*':
                    push( &pilha, a*b + '0');
                    break;
                case '/':
                    push( &pilha, a/b + '0');
                    break;
            }
        }
    }
    return pop( &pilha ) - '0';
}
