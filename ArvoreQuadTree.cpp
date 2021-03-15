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
#include <vector>
#include "ArvoreQuadTree.h"

using namespace std;
/**
Uma árvore quádrupla, às vezes quadtree, árvore Q ou QT, é um termo de ciência da computação que se refere a um método de organização de dados em quatro quadrantes. Os bancos de dados às vezes usam árvores quad para armazenar e encontrar seus registros. Esse tipo de estrutura organizacional funciona especialmente bem para encontrar um bit ou pixel específico em uma imagem bidimensional.

A árvore quádrupla segue um pouco a estrutura de dados da árvore comumente usada em ciência da computação. A estrutura de dados da árvore normal se parece com uma árvore invertida, em que um nó pai na parte superior da árvore tem um ou mais nós filhos conectados a ela. Todos os outros nós da árvore têm um nó pai e podem ter qualquer número de nós filhos, incluindo zero.

Diferentemente de uma estrutura de dados em árvore normal, uma estrutura em árvore em quadruplo exige que cada nó interno tenha exatamente quatro nós filhos. Ao ilustrar a maioria das estruturas de árvore quádrupla, você verá um nó que possui quatro nós filhos pendurados, com linhas conectando o nó pai aos seus nós filhos. A ilustração pode continuar, com mais quatro nós filhos pendurados em cada um dos quatro nós filhos originais.

Outras vezes, a ilustração de um quad tree será uma região ou um quadrado. Sempre que a região atinge sua capacidade máxima para armazenar dados, ela é dividida em quatro quadrantes. Normalmente, as regiões e os quadrantes são quadrados, embora também possam ser retângulos ou outras formas.

Uma árvore quádrupla é uma boa estrutura de dados para organizar pixels em uma foto e para organizar gráficos de computador. A imagem pode ser dividida em quadrantes e cada quadrante pode ser dividido em mais quatro. Isso pode ser repetido várias vezes até atingir o nível de pixels individuais. Se um quadrante contiver pixels com a mesma cor, não há motivo para dividir ainda mais o quadrante.

Embora os dados armazenados em uma estrutura em quatro árvores possam exigir muito espaço de armazenamento em comparação com outros métodos de organização de dados para gráficos de computador, a estrutura em quatro árvores tem várias vantagens. Primeiro, você pode excluir a fotografia ou o gráfico inteiro em uma única etapa limpando o nó raiz, que limpa todos os nós filhos também. Segundo, você pode reduzir rapidamente a resolução em uma fotografia simplesmente limpando o nível final dos nós filhos. Isso reduzirá a quantidade de espaço de armazenamento necessário. Por fim, encontrar uma área específica da fotografia para manipulação de imagem é mais fácil com a estrutura de árvore em quadruplo.

As árvores quádruplas também são usadas em algumas outras situações, incluindo a indexação espacial. Embora as árvores quádruplas sejam limitadas a imagens bidimensionais, a representação de uma imagem tridimensional pode seguir uma estrutura semelhante, chamada octree, que é a subdivisão de um cubo em oito filhos.
**/
ArvoreQuadTree::ArvoreQuadTree()
{
    this->raiz = nullptr;
}
ArvoreQuadTree::~ArvoreQuadTree() {}

NoArvoreQuadTree *ArvoreQuadTree::getRaiz()
{
    return this->raiz;
}

void ArvoreQuadTree::insert(NoArvoreQuadTree *no)
{

    if (this->raiz == nullptr)
    {
        raiz = no;
    }
    else
    {
        NoArvoreQuadTree *aux = raiz;
        while (true)
        {
            if (no->getCoordX() < aux->getCoordX())
            {
                if (no->getCoordY() < aux->getCoordY())
                {
                    if (aux->getSw() == 0)
                    {
                        aux->setSw(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getSw();
                    }
                }
                else
                {
                    if (aux->getNw() == 0)
                    {
                        aux->setNw(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getNw();
                    }
                }
            }
            else
            {
                if (no->getCoordY() < aux->getCoordY())
                {
                    if (aux->getSe() == 0)
                    {
                        aux->setSe(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getSe();
                    }
                }
                else
                {
                    if (aux->getNe() == 0)
                    {
                        aux->setNe(no);
                        break;
                    }
                    else
                    {
                        aux = aux->getNe();
                    }
                }
            }
        }
        aux = no;
    }
}
void ArvoreQuadTree::busca(double latitude, double longitude)
{

    NoArvoreQuadTree *aux = raiz;
    while (true)
    {
        if (aux->getCoordX() == latitude && aux->getCoordY() == longitude)
        {
            cout << aux->getRegistroCoordenado().getCityName();
            break;
        }
        if (latitude < aux->getCoordX())
        {
            if (longitude < aux->getCoordY())
            {
                if (aux->getSw() == 0)
                {
                    cout << "Nao encontrado";
                    break;
                }
                else
                {
                    aux = aux->getSw();
                }
            }
            else
            {
                if (aux->getNw() == 0)
                {
                    cout << "Nao encontrado";
                    break;
                }
                else
                {
                    aux = aux->getNw();
                }
            }
        }
        else
        {
            if (longitude < aux->getCoordY())
            {
                if (aux->getSe() == 0)
                {
                    cout << "Nao encontrado";
                    break;
                }
                else
                {
                    aux = aux->getSe();
                }
            }
            else
            {
                if (aux->getNe() == 0)
                {
                    cout << "Nao encontrado";
                    break;
                }
                else
                {
                    aux = aux->getNe();
                }
            }
        }
    }
}

void ArvoreQuadTree::imprimePorNivel(NoArvoreQuadTree *p, int nivel)
{
    if (p != nullptr)
    {
        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";
        cout << "(";
        cout << p->getRegistroCoordenado().getCityCode();
        cout << ", ";
        cout << p->getRegistroCoordenado().getLongitude();
        cout << ")" << endl;
        imprimePorNivel(p->getNw(), nivel + 1);
        imprimePorNivel(p->getNe(), nivel + 1);
        imprimePorNivel(p->getSw(), nivel + 1);
        imprimePorNivel(p->getSe(), nivel + 1);
    }
}

void ArvoreQuadTree::ImprimeArquivoTexto(NoArvoreQuadTree *p, int nivel, ofstream &saida)
{
    if (p != nullptr)
    {
        saida << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            saida << "--";
        saida << "(";
        saida << p->getRegistroCoordenado().getLatitude();
        saida << ", ";
        saida << p->getRegistroCoordenado().getLongitude();
        saida << ")" << endl;
        ImprimeArquivoTexto(p->getNw(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getNe(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getSw(), nivel + 1, saida);
        ImprimeArquivoTexto(p->getSe(), nivel + 1, saida);
    }
}

void ArvoreQuadTree::retornaRegistrosNasCoordenadas(vector<ApontamentosDeCoordenados> &vet, NoArvoreQuadTree *p, double latitude1, double longitude1, double latitude2, double longitude2)
{
    if (p != nullptr)
    {
        if(p->getCoordX() <= latitude1 && p->getCoordX() >= latitude2 && p->getCoordY() <= longitude1 && p->getCoordY() >= longitude2)
        {
            vet.push_back(p->getRegistroCoordenado());
        }
        retornaRegistrosNasCoordenadas(vet, p->getNw(), latitude1, longitude1, latitude2, longitude2);
        retornaRegistrosNasCoordenadas(vet, p->getNe(), latitude1, longitude1, latitude2, longitude2);
        retornaRegistrosNasCoordenadas(vet, p->getSw(), latitude1, longitude1, latitude2, longitude2);
        retornaRegistrosNasCoordenadas(vet, p->getSe(), latitude1, longitude1, latitude2, longitude2);
    }
}

