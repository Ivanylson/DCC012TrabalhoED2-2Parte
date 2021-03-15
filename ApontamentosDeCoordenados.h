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
#ifndef APONTAMENTOSDECOORDENADOS_H_INCLUDED
#define APONTAMENTOSDECOORDENADOS_H_INCLUDED
#include <string>

using namespace std;

class ApontamentosDeCoordenados
{

private:
    int stateCode;
    string cityCode;
    string cityName;
    double latitude;
    double longitude;
    bool capital;

public:
    ApontamentosDeCoordenados();
    ~ApontamentosDeCoordenados();
    int getStateCode();
    string getCityCode();
    string getCityName();
    double getLatitude();
    double getLongitude();
    bool getCapital();
    void setStateCode(int stateCode);
    void setCityCode(string cityCode);
    void setCityName(string cityName);
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setCapital(bool capital);
};
#endif // APONTAMENTOSDECOORDENADOS_H_INCLUDED
