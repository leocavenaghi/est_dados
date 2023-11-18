#include <iostream>
#include <string>
#include "pilha.h"
#include "expressao.h"

using std::cin;
using std::cout;
using std::string;

int main()
{
    string expressao;
    cin >> expressao;

    string posfixa = infixaToPosfixa(expressao);
    cout << "Forma infixa: " << expressao << "\n";
    cout << "Forma posfixa: " << posfixa << "\n";

    cout << "Resultado: " << avalia(posfixa);

    return 0;
}
