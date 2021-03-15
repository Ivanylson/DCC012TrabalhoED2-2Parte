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
#ifndef NOARVOREQUADTREE_H_INCLUDED
#define NOARVOREQUADTREE_H_INCLUDED

#include <string>
#include "ApontamentosDeCoordenados.h"

using namespace std;
/**
O termo estrutura de dados é utilizado para referenciar diferentes formas de representação de
dados. A escolha de uma determinada estrutura para representar um conjunto de dados relacionados
deve-se, principalmente, ao tipo de operações que serão realizadas sobre o mesmo, usando uma
manipulação otimizada em relação ao tempo necessário para efetuar as operações e á área de
armazenamento requisitada para guardar estes dados.
 A entidade elementar de uma estrutura de dados é o nodo (nó). Um nodo é diferenciado pelo
seu endereço relativo dentro da estrutura e pode ser constituído de um ou vários campos. 
**/
class NoArvoreQuadTree
{

private:
    ApontamentosDeCoordenados *registroCoordenado;
    double coordX;
    double coordY;
    NoArvoreQuadTree *pai;
    NoArvoreQuadTree *ne;
    NoArvoreQuadTree *nw;
    NoArvoreQuadTree *sw;
    NoArvoreQuadTree *se;

public:
    NoArvoreQuadTree(ApontamentosDeCoordenados *registro);
    ~NoArvoreQuadTree();
    ApontamentosDeCoordenados getRegistroCoordenado();
    double getCoordX();
    double getCoordY();
    NoArvoreQuadTree getPai();
    NoArvoreQuadTree *getNe();
    NoArvoreQuadTree *getNw();
    NoArvoreQuadTree *getSw();
    NoArvoreQuadTree *getSe();
    void setRegistroCoordenado(ApontamentosDeCoordenados *registro);
    void setCoordX(double x);
    void setCoordY(double y);
    void setPai(NoArvoreQuadTree *no);
    void setNe(NoArvoreQuadTree *no);
    void setNw(NoArvoreQuadTree *no);
    void setSw(NoArvoreQuadTree *no);
    void setSe(NoArvoreQuadTree *no);
};
#endif // NOARVOREQUADTREE_H_INCLUDED
