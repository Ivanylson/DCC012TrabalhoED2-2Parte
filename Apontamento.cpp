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
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include "Apontamento.h"

using namespace std;

Apontamento::Apontamento()
{

    this->date;
    this->state;
    this->name;
    this->code;
    this->cases;
    this->deaths;
}

Apontamento::~Apontamento() {}

string& Apontamento::getDate()
{
    return this->date;
}

string& Apontamento::getState()
{
    return this->state;
}

string& Apontamento::getName()
{
    return this->name;
}

string& Apontamento::getCode()
{
    return this->code;
}

int& Apontamento::getCases()
{
    return this->cases;
}

int& Apontamento::getDeaths()
{
    return this->deaths;
}

void Apontamento::setDate(string date)
{
    this->date = date;
}

void Apontamento::setState(string state)
{
    this->state = state;
}

void Apontamento::setName(string name)
{
    this->name = name;
}

void Apontamento::setCode(string code)
{
    this->code = code;
}

void Apontamento::setCases(int cases)
{
    this->cases = cases;
}

void Apontamento::setDeaths(int deaths)
{
    this->deaths = deaths;
}
