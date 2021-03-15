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
#include <algorithm>
#include <fstream>
#include "ArvoreBTree.h"
#include "TabelaHash.h"

using namespace std;

ArvoreBTree::ArvoreBTree(int ordem, TabelaHash *tabela)
{
    this->registros = tabela;
    this->ordem = ordem;
}

ArvoreBTree::~ArvoreBTree()
{
}

int ArvoreBTree::getOrdem()
{
    return this->ordem;
}

NoArvoreBTree *ArvoreBTree::getRaiz()
{
    return this->raiz;
}

TabelaHash *ArvoreBTree::getHashTable()
{
    return this->registros;
}

//Retorna true se candidatoInicio seja um elemento anterior ao candidatoFim apos ordenaçao
bool ArvoreBTree::menorElemento(Apontamento *candidatoInicio, Apontamento *candidatoFim)
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

void ArvoreBTree::calculaTotalCasosCidade(NoArvoreBTree *no, string code, int &comparacoes, int &totalCasos)
{
    int i;
    for (i = 0; i < no->getN(); i++)
    {
        if (!no->getFolha())
        {
            comparacoes += 1;
            if (code <= this->getHashTable()->getRegistroFromTable(no->getKeys()[i])->getCode())
            {
                calculaTotalCasosCidade(no->getFilhos()[i], code, comparacoes, totalCasos);
            }
        }
        comparacoes += 1;
        if (this->getHashTable()->getRegistroFromTable(no->getKeys()[i])->getCode() == code)
        {
            totalCasos += this->getHashTable()->getRegistroFromTable(no->getKeys()[i])->getCases();
        }
        else if (this->getHashTable()->getRegistroFromTable(no->getKeys()[i])->getCode() > code)
        {
            comparacoes += 1;
            break;
        }
        comparacoes += 1;
    }
    if (!no->getFolha())
    {
        comparacoes += 1;
        if (i == no->getN())
        {
            if (code >= this->getHashTable()->getRegistroFromTable(no->getKeys()[i - 1])->getCode())
            {
                calculaTotalCasosCidade(no->getFilhos()[i], code, comparacoes, totalCasos);
            }
        }
        else
        {
            if (code >= this->getHashTable()->getRegistroFromTable(no->getKeys()[i ])->getCode())
            {
                calculaTotalCasosCidade(no->getFilhos()[i+1], code, comparacoes, totalCasos);
            }
        }
    }
}

void ArvoreBTree::cisaoFilho(NoArvoreBTree *raiz, int position)
{
    NoArvoreBTree *filhoRaiz = raiz->getFilhos()[position];

    NoArvoreBTree *novoNo = new NoArvoreBTree(raiz->getOrdem(), filhoRaiz->getFolha());

    for (int j = 0; j < getOrdem() - 1; j++)
    {
        novoNo->setKeys(filhoRaiz->getKeys()[j + getOrdem()], j);
    }

    if (!filhoRaiz->getFolha())
    {
        for (int j = 0; j < getOrdem(); j++)
        {
            novoNo->setFilhos(filhoRaiz->getFilhos()[j + getOrdem()], j);
        }
    }

    novoNo->setN(getOrdem() - 1);

    filhoRaiz->setN(getOrdem() - 1);

    insereNo(raiz, filhoRaiz->getKeys()[getOrdem() - 1]);

    raiz->setFilhos(novoNo, position + 1);
}

/**
Inserção
A operação de inserção, inicialmente com a árvore vazia, deve garantir que o nó raiz será criado. Criado o nó raiz, a inserção das próximas chaves seguem o mesmo procedimento: busca-se a posição correta da chave em um nó folha e insere a chave garantindo a ordenação destas. Após feito isso, considerando a abordagem de inserção de baixo para cima (Bottom-up) na árvore B, podem ocorrer duas situações:

Página folha está com um número menor de chaves do que o máximo permitido (d-1): Nesse caso apenas inserimos a chave de maneira ordenada na página
Página folha completa ou com o número máximo de chaves permitido (d-1): Nesse caso ocorre o overflow da página em questão e é necessário a operação de split para manter o balanceamento da árvore.
Primeiramente escolhe-se um valor intermediário na sequência ordenada de chaves da página incluindo-se a nova chave que deveria ser inserida. Este valor é exatamente uma chave que ordenada com as chaves da página estará no meio da sequência.
Cria-se uma nova página e os valores maiores do que a chave intermediária são armazenados nessa nova página e os menores continuam na página anterior (operação de split).
Esta chave intermediária escolhida deverá ser inserido na página pai, na qual poderá também sofrer overflow ou deverá ser criada caso em que é criada uma nova página raiz. Esta série de overflows pode se propagar para toda a árvore B, o que garante o seu balanceamento na inserção de chaves.
Uma abordagem melhorada para a inserção é a de cima para baixo (Top-down) que utiliza uma estratégia parecida com a inserção de baixo para cima, a lógica para a inserção das próximas chaves (levando em consideração que a raiz já está criada) é a seguinte: busca-se a posição correta da chave em um nó, porém durante a busca da posição correta todo nó que estiver com o número máximo de chaves (d-1) é feita a operação de split, adicionando o elemento intermediário na sequência ordenada de chaves da página no pai e separando os elementos da página em outras duas novas páginas, onde uma vai conter os elementos menores que o elemento intermediário e a outra os elementos maiores que ele, a inserção será feita em um nó folha somente após todo o processo de split e insere a chave garantindo a ordenação destas. Esta abordagem melhorada previne de ter que ficar fazendo chamadas sucessivas ao pai do nó, o que pode ser caro se o pai estiver na memória secundária.
**/
void ArvoreBTree::insereNo(NoArvoreBTree *raiz, int key)
{
    int position = raiz->getN();
    while (position > 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(raiz->getKeys()[position - 1])))
    {
        raiz->setKeys(raiz->getKeys()[position - 1], position);
        raiz->setFilhos(raiz->getFilhos()[position], position + 1);
        position--;
    }

    raiz->setFilhos(raiz->getFilhos()[position], position + 1);
    raiz->setKeys(key, position);
    raiz->setN(raiz->getN() + 1);
}

void ArvoreBTree::insere(int key)
{
    if (this->raiz == NULL)
    {
        this->raiz = new NoArvoreBTree(this->getOrdem(), true);
        this->raiz->getKeys()[0] = key;
        this->raiz->setN(1);
    }
    else
    {
        if (this->raiz->getN() == 2 * this->getOrdem() - 1)
        {
            NoArvoreBTree *novaRaiz = new NoArvoreBTree(this->getOrdem(), false);

            novaRaiz->setFilhos(raiz, 0);

            this->raiz = novaRaiz;

            cisaoFilho(novaRaiz, 0);
        }

        NoArvoreBTree *novoNo = this->raiz;

        while (!novoNo->getFolha())
        {
            int position = novoNo->getN() - 1;

            while (position >= 0 && menorElemento(registros->getRegistroFromTable(key), registros->getRegistroFromTable(novoNo->getKeys()[position])))
            {
                position--;
            }

            position++;

            if (novoNo->getFilhos()[position]->getN() == 2 * novoNo->getOrdem() - 1)
            {
                cisaoFilho(novoNo, position);

                if (menorElemento(registros->getRegistroFromTable(novoNo->getKeys()[position]), registros->getRegistroFromTable(key)))
                {
                    position++;
                }
            }

            novoNo = novoNo->getFilhos()[position];
        }

        insereNo(novoNo, key);
    }
}
