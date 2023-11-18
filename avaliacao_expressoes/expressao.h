#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#include <string>

int Prioridade(char *operador);
std::string infixaToPosfixa(std::string expressao);
int avalia(std::string posfixa);

#endif // EXPRESSAO_H
