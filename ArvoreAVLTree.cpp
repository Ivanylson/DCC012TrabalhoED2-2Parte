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
#include "ArvoreAVLTree.h"
#include "TabelaHash.h"

using namespace std;

// CONSTRUTOR / DESTRUTOR
ArvoreAVLTree::ArvoreAVLTree(TabelaHash *registros)
{
    this->raiz = NULL;
    this->registros = registros;
}

ArvoreAVLTree::~ArvoreAVLTree()
{
    this->raiz = libera(raiz);
}

// DEMAIS FUNÇÕES
bool ArvoreAVLTree::vazia()
{
    return this->raiz == NULL;
}

NoArvoreAVLTree *ArvoreAVLTree::libera(NoArvoreAVLTree *p)
{
    if (p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}

int ArvoreAVLTree::altura(NoArvoreAVLTree *raiz)
{
    if (raiz == NULL)
        return 0;
    return raiz->getAltura();
}

int ArvoreAVLTree::retornaMaior(int a, int b)
{
    return (a > b) ? a : b;
}

bool ArvoreAVLTree::menorElemento(Apontamento *candidatoInicio, Apontamento *candidatoFim)
{
    bool verificaCode = (candidatoInicio->getCode() == candidatoFim->getCode());
    if (candidatoInicio->getCode() < candidatoFim->getCode() || verificaCode)
    {
        if (verificaCode)
        {
            if (candidatoInicio->getDate() < candidatoFim->getDate())
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

// INSERÇÃO
void ArvoreAVLTree::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

NoArvoreAVLTree *ArvoreAVLTree::auxInsere(NoArvoreAVLTree *p, int val)
{
    if (p == NULL)
    {
        p = new NoArvoreAVLTree();
        p->setValor(val);
        p->setEsq(NULL);
        p->setDir(NULL);
        p->setAltura(1);
    }
    else if (menorElemento(registros->getRegistroFromTable(val), registros->getRegistroFromTable(p->getValor())))
    {
        p->setEsq(auxInsere(p->getEsq(), val));
    }
    else if (!menorElemento(registros->getRegistroFromTable(val), registros->getRegistroFromTable(p->getValor())))
    {
        p->setDir(auxInsere(p->getDir(), val));
    }
    else
        return p;

    p->setAltura(1 + retornaMaior(altura(p->getEsq()), altura(p->getDir())));

    int fb = calculaFB(p);

    // Rotação dupla a Esquerda
    if (fb == 2 && calculaFB(p->getDir()) == -1)
    {
        p->setDir(rotacaoDireita(p->getDir()));
        return rotacaoEsquerda(p);
    }

    // Rotação dupla a direita
    if (fb == -2 && calculaFB(p->getEsq()) == 1)
    {
        p->setEsq(rotacaoEsquerda(p->getEsq()));
        return rotacaoDireita(p);
    }

    // Rotação a Esquerda
    if (fb == 2 && (calculaFB(p->getDir()) == 1 || calculaFB(p->getDir()) == 0))
        return rotacaoEsquerda(p);

    // Rotação a Direita
    if (fb == -2 && (calculaFB(p->getEsq()) == -1 || calculaFB(p->getEsq()) == 0))
        return rotacaoDireita(p);

    return p;
}

// BUSCA
void ArvoreAVLTree::busca(string code, int &totalCasos, int &comparacoes)
{
    auxBusca(raiz, code, totalCasos,comparacoes);
}

void ArvoreAVLTree::auxBusca(NoArvoreAVLTree *p, string code, int &totalCasos, int &comparacoes)
{
    if (p != NULL)
    {
        comparacoes += 1;
        if (code == this->registros->getRegistroFromTable(p->getValor())->getCode())
        {
            totalCasos += this->registros->getRegistroFromTable(p->getValor())->getCases();
            auxBusca(p->getEsq(), code, totalCasos, comparacoes);
            auxBusca(p->getDir(), code, totalCasos, comparacoes);
        }

        else if (code < this->registros->getRegistroFromTable(p->getValor())->getCode())
        {
            comparacoes += 1;
            auxBusca(p->getEsq(), code, totalCasos, comparacoes);
        }

        else
        {
            comparacoes += 1;
            auxBusca(p->getDir(), code, totalCasos, comparacoes);
        }
    }
}

// IMPRESSÃO NO TERMINAL
void ArvoreAVLTree::imprime(TabelaHash *registros)
{
    imprimePorNivel(raiz, 0, registros);
}

void ArvoreAVLTree::imprimePorNivel(NoArvoreAVLTree *p, int nivel, TabelaHash *registros)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << registros->getRegistroFromTable(p->getValor())->getCode() << " ";
        cout << registros->getRegistroFromTable(p->getValor())->getDate() << endl;
        imprimePorNivel(p->getEsq(), nivel + 1, registros);
        imprimePorNivel(p->getDir(), nivel + 1, registros);
    }
}

// IMPRESSÃO DA ÁRVORE EM ARQUIVO
void ArvoreAVLTree::saidaArqv(ofstream &saida, TabelaHash *registros)
{
    auxSaidaArqv(raiz, 0, saida, registros);
}

void ArvoreAVLTree::auxSaidaArqv(NoArvoreAVLTree *p, int nivel, ofstream &saida, TabelaHash *registros)
{
    if (p != NULL)
    {
        saida << "( Nivel : ";
        saida << to_string(nivel);
        saida << " ) ";

        for (int i = 1; i <= nivel; i++)
            saida << "--";

        saida << registros->getRegistroFromTable(p->getValor())->getCode();
        saida << " ";
        saida << registros->getRegistroFromTable(p->getValor())->getDate();
        saida << endl;
        auxSaidaArqv(p->getEsq(), nivel + 1, saida, registros);
        auxSaidaArqv(p->getDir(), nivel + 1, saida, registros);
    }
}

// CALCULA O FATOR DE BALANCEAMENTO
int ArvoreAVLTree::calculaFB(NoArvoreAVLTree *no)
{
    if (no == NULL)
        return 0;
    else
        return altura(no->getDir()) - altura(no->getEsq());
}

//ROTAÇÕES
NoArvoreAVLTree *ArvoreAVLTree::rotacaoEsquerda(NoArvoreAVLTree *no)
{
    // Q = P->dir
    NoArvoreAVLTree *noDir = no->getDir();

    NoArvoreAVLTree *noEsq = noDir->getEsq();

    noDir->setEsq(no);
    no->setDir(noEsq);

    no->setAltura((retornaMaior(altura(no->getEsq()), altura(no->getDir())) + 1));
    noDir->setAltura((retornaMaior(altura(noDir->getEsq()), altura(noDir->getDir())) + 1));

    return noDir;
}

NoArvoreAVLTree *ArvoreAVLTree::rotacaoDireita(NoArvoreAVLTree *no)
{
    NoArvoreAVLTree *noEsq = no->getEsq();
    NoArvoreAVLTree *noDir = noEsq->getDir();

    noEsq->setDir(no);
    no->setEsq(noDir);

    no->setAltura((retornaMaior(altura(no->getEsq()), altura(no->getDir())) + 1));
    noEsq->setAltura((retornaMaior(altura(noEsq->getEsq()), altura(noEsq->getDir())) + 1));

    return noEsq;
}
