## Como executar os arquivos .exe?
Como os executaveis não tem ponto de input ao final do arquivo não é possível executar simplesmente clicando duas vezes sobre ele.

Para executar os executáveis navegue até a pasta do projeto desejado com um terminal e digite ./mainx64 para visualizar as informações

# Especificações do compilador
Using built-in specs.
COLLECT_GCC=C:\Flex Windows\gcc\bin\g++.exe
COLLECT_LTO_WRAPPER=c:/flex windows/gcc/bin/../libexec/gcc/mingw32/4.7.2/lto-wrapper.exe
Target: mingw32
Configured with: ../gcc-4.7.2/configure --enable-languages=c,c++,ada,fortran,objc,obj-c++ --disable-sjlj-exceptions --with-dwarf2 --enable-shared --enable-libgomp --disable-win32-registry --enable-libstdcxx-debug --disable-build-poststage1-with-cxx --enable-version-specific-runtime-libs --build=mingw32 --prefix=/mingw
Thread model: win32
gcc version 4.7.2 (GCC)

# Exemplo de comandos utilizados para compilação
g++ -std=c++11 -c pilha.cpp -o pilha.o
g++ -std=c++11 -c expressao.cpp -o expressao.o
g++ -std=c++11 -c main.cpp -o main.o
g++ -std=c++11 pilha.o expressao.o main.o -o mainx64.exe