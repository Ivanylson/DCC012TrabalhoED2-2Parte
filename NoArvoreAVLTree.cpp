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
#include <string>
#include <iostream>
#include "NoArvoreAVLTree.h"

/**
O termo estrutura de dados é utilizado para referenciar diferentes formas de representação de
dados. A escolha de uma determinada estrutura para representar um conjunto de dados relacionados
deve-se, principalmente, ao tipo de operações que serão realizadas sobre o mesmo, usando uma
manipulação otimizada em relação ao tempo necessário para efetuar as operações e á área de
armazenamento requisitada para guardar estes dados.
 A entidade elementar de uma estrutura de dados é o nodo (nó). Um nodo é diferenciado pelo
seu endereço relativo dentro da estrutura e pode ser constituído de um ou vários campos. 
**/
// CONSTRUTOR / DESTRUTOR
NoArvoreAVLTree::NoArvoreAVLTree()
{
}

NoArvoreAVLTree::~NoArvoreAVLTree()
{
}

// SETS
void NoArvoreAVLTree::setEsq(NoArvoreAVLTree *p)
{
    this->esq = p;
}

void NoArvoreAVLTree::setValor(int val)
{
    this->valor = val;
}

void NoArvoreAVLTree::setAltura(int val)
{
    this->altura = val;
}

void NoArvoreAVLTree::setDir(NoArvoreAVLTree *p)
{   
    this->dir = p;
}


// GETS
NoArvoreAVLTree* NoArvoreAVLTree::getEsq()
{
    return this->esq;
}

int NoArvoreAVLTree::getValor()
{
    return this->valor;
}

NoArvoreAVLTree* NoArvoreAVLTree::getDir()
{
    return this->dir;
}

int NoArvoreAVLTree::getAltura()
{
    return this->altura;
}