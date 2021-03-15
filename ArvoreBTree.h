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
#ifndef ARVOREBTREE_H_INCLUDED
#define ARVOREBTREE_H_INCLUDED
#include <iostream>
#include <vector>
#include "TabelaHash.h"
#include "NoArvoreBTree.h"

using namespace std;
/**
uma árvore B é uma estrutura de dados em árvore, auto-balanceada, que armazena dados classificados e permite pesquisas, acesso sequencial, inserções e remoções em tempo logarítmico. A árvore B é uma generalização de uma árvore de pesquisa binária em que um nó pode ter mais que dois filhos. Diferente das árvores de pesquisa binária auto-balanceadas, a árvore B é bem adaptada para sistemas de armazenamento que leem e escrevem blocos de dados relativamente grandes, como discos.
**/
class ArvoreBTree
{
private:
    int ordem;
    NoArvoreBTree* raiz = NULL;
    TabelaHash *registros ;

public:
    ArvoreBTree(int ordem, TabelaHash *tabela);
    ~ArvoreBTree();

    int getOrdem();

    NoArvoreBTree* getRaiz();

    TabelaHash* getHashTable();

    bool menorElemento(Apontamento *candidatoInicio, Apontamento *candidatoFim);

    void calculaTotalCasosCidade(NoArvoreBTree* no, string code, int &comparacoes, int &totalCasos);

    void insereNo(NoArvoreBTree* raiz, int key);
    void cisaoFilho(NoArvoreBTree* raiz, int position);
    void insere(int key);

};

#endif // ARVOREBTREE_H_INCLUDED
