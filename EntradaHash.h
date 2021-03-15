/**
    UNIVERSIDADE FEDERAL DE JUIZ DE FORA
    INSTITUTO DE CIÊNCIAS EXATAS
    DEPARTAMENTO DA CIẼNCIA DA COMPUTAÇÃO

    TRABALHO DE ESTRUTURA DE DADOS 2(||) - 2020.3 (ERE)
    PROF.DR.MARCELO CANIATO RENHE

    GRUPO:
    BEATRIZ CUNHA RODRIGUES        MAT 201776038
    IVANYLSON HONORIO GONÇALVES    MAT 201776002
    JOÃO PEDRO SEQUETO NASCIMENTO  MAT 201776022

    Principal
    main.cpp
    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 *.h *.cpp -o main && ./main Arquivos/
    WINDOWS:    cls & g++ -std=c++11 *.h *.cpp -o main.exe && ./main.exe Arquivos/
**/
#ifndef ENTRADAHASH_H_INCLUDED
#define ENTRADAHASH_H_INCLUDED

#include "Apontamento.h"

using namespace std;

class EntradaHash
{
private:
    int hashIndex;
    Apontamento* registro;
public:
    EntradaHash(int hashIndex,Apontamento* registro);
    ~EntradaHash();
    int getHashIndex();
    Apontamento* getRegistro();
};

#endif // ENTRADAHASH_H_INCLUDED
