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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <math.h>
#include <algorithm>
#include <chrono>
#include "MenuAnalisesTestes.h"

/**
Etapa 1: Carregamento do arquivo de cidades

Sua primeira tarefa será fazer a leitura dos dados do arquivo brazil_cities_coordinates.csv e armazená-los em uma quad tree. O arquivo CSV contém 5.571 registros. Lembre-se que a quad tree é muito similar a uma árvore binária de busca padrão, com a exceção de que cada nó da quad tree possui 4 filhos, e não apenas 2.


Etapa 2: Carregamento do arquivo pré-processado de casos

Nesta etapa, você irá importar o arquivo pré-processado pelo seu grupo no Trabalho 1 (brazil_covid19_cities_processado.csv), contendo o total de casos diários para cada cidade. O arquivo CSV contém 1.431.490 registros. Você deverá armazenar estes registros em uma tabela hash. Dimensione a tabela adequadamente e utilize uma função de hash que permita uma boa distribuição de chaves na tabela. Escolha também uma técnica para tratamento de colisões. Utilize como chave o par (código da cidade, data).


**/
using namespace std;


int main(int argc, char const *argv[])
{

    string path = argv[1];
    mainMenu(path);

    return 0;
}
