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

*/
#ifndef APONTAMENTO_H_INCLUDED
#define APONTAMENTO_H_INCLUDED
#include <string>

using namespace std;

class Apontamento
{

private:

    string date;
    string state;
    string name;
    string code;
    int cases;
    int deaths;

public:

    Apontamento();
    ~Apontamento();
    void setDate(string date);
    void setState(string state);
    void setName(string name);
    void setCode(string code);
    void setCases(int cases);
    void setDeaths(int deaths);

    string& getDate();
    string& getState();
    string& getName();
    string& getCode();
    int& getCases();
    int& getDeaths();

};

#endif // APONTAMENTO_H_INCLUDED
