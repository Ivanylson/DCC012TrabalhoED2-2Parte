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
#include <string>
#include <cstdlib>
#include "NoArvoreQuadTree.h"

/**
O termo estrutura de dados é utilizado para referenciar diferentes formas de representação de
dados. A escolha de uma determinada estrutura para representar um conjunto de dados relacionados
deve-se, principalmente, ao tipo de operações que serão realizadas sobre o mesmo, usando uma
manipulação otimizada em relação ao tempo necessário para efetuar as operações e á área de
armazenamento requisitada para guardar estes dados.
 A entidade elementar de uma estrutura de dados é o nodo (nó). Um nodo é diferenciado pelo
seu endereço relativo dentro da estrutura e pode ser constituído de um ou vários campos.
**/
NoArvoreQuadTree::NoArvoreQuadTree(ApontamentosDeCoordenados *registro)
{
    this->registroCoordenado = registro;
    this->coordX = registro->getLatitude();
    this->coordY = registro->getLongitude();
    this->pai = nullptr;
    this->ne = nullptr;
    this->nw = nullptr;
    this->se = nullptr;
    this->sw = nullptr;
}
NoArvoreQuadTree::~NoArvoreQuadTree() {}

ApontamentosDeCoordenados NoArvoreQuadTree::getRegistroCoordenado()
{
    return *this->registroCoordenado;
}
double NoArvoreQuadTree::getCoordX()
{
    return this->coordX;
}
double NoArvoreQuadTree::getCoordY()
{
    return this->coordY;
}
NoArvoreQuadTree NoArvoreQuadTree::getPai()
{
    return *this->pai;
}
NoArvoreQuadTree *NoArvoreQuadTree::getNe()
{
    return this->ne;
}
NoArvoreQuadTree *NoArvoreQuadTree::getNw()
{
    return this->nw;
}
NoArvoreQuadTree *NoArvoreQuadTree::getSw()
{
    return this->sw;
}
NoArvoreQuadTree *NoArvoreQuadTree::getSe()
{
    return this->se;
}

void NoArvoreQuadTree::setRegistroCoordenado(ApontamentosDeCoordenados *registro)
{
    this->registroCoordenado = registro;
}
void NoArvoreQuadTree::setCoordX(double x)
{
    this->coordX = x;
}
void NoArvoreQuadTree::setCoordY(double y)
{
    this->coordY = y;
}
void NoArvoreQuadTree::setPai(NoArvoreQuadTree *no)
{
    this->pai = no;
}
void NoArvoreQuadTree::setNe(NoArvoreQuadTree *no)
{
    this->ne = no;
}
void NoArvoreQuadTree::setNw(NoArvoreQuadTree *no)
{
    this->nw = no;
}
void NoArvoreQuadTree::setSw(NoArvoreQuadTree *no)
{
    this->sw = no;
}
void NoArvoreQuadTree::setSe(NoArvoreQuadTree *no)
{
    this->se = no;
}
