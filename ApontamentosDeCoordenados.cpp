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
#include "ApontamentosDeCoordenados.h"

using namespace std;

ApontamentosDeCoordenados::ApontamentosDeCoordenados()
{
    this->stateCode;
    this->capital;
    this->cityCode;
    this->cityName;
    this->latitude;
    this->longitude;
}

ApontamentosDeCoordenados::~ApontamentosDeCoordenados() {}

int ApontamentosDeCoordenados::getStateCode()
{
    return this->stateCode;
}
string ApontamentosDeCoordenados::getCityCode()
{
    return this->cityCode;
}
string ApontamentosDeCoordenados::getCityName()
{
    return this->cityName;
}
double ApontamentosDeCoordenados::getLatitude()
{
    return this->latitude;
}
double ApontamentosDeCoordenados::getLongitude()
{
    return this->longitude;
}
bool ApontamentosDeCoordenados::getCapital()
{
    return this->capital;
}

void ApontamentosDeCoordenados::setStateCode(int stateCode)
{
    this->stateCode = stateCode;
}
void ApontamentosDeCoordenados::setCityCode(string cityCode)
{
    this->cityCode = cityCode;
}
void ApontamentosDeCoordenados::setCityName(string cityName)
{
    this->cityName = cityName;
}
void ApontamentosDeCoordenados::setLatitude(double latitude)
{
    this->latitude = latitude;
}
void ApontamentosDeCoordenados::setLongitude(double longitude)
{
    this->longitude = longitude;
}
void ApontamentosDeCoordenados::setCapital(bool capital)
{
    this->capital = capital;
}
