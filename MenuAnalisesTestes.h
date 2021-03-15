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
/**Bibliotecas**/
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

/**Arquivos**/
#include "ArvoreQuadTree.h"
#include "Apontamento.h"
#include "TabelaHash.h"
#include "ArvoreBTree.h"
#include "ArvoreAVLTree.h"
#define TAMANHOREG 1431490;

using namespace std;
/**
Etapa 3: Implementação de estruturas de dados balanceadas

Em seguida, você irá implementar duas estruturas de dados em árvore: árvore AVL e árvore B. Para cada uma delas, adote como chave um valor inteiro id. Você deverá implementar operações de inserção e busca (não há necessidade de implementar a remoção). Cada nó deve armazenar somente o valor inteiro mencionado acima, que corresponderá ao código hash de um registro, mas a ordenação da árvore será determinada pelo par (código da cidade, data). As outras informações do registro, quando necessárias, serão acessadas através da tabela hash (vide Etapa 5).

Etapa 4: Módulo de testes

O próximo passo é verificar que as suas estruturas de dados estão corretas. Esse módulo deve conter funções para exibir as estruturas geradas pelas seguintes operações:

Inserção de N cidades na quad tree
Inserção de N registros na tabela hash
Inserção de N chaves na árvore AVL
Inserção de N chaves na árvore B

Apresente cada uma das operações como opções de um menu, para que o usuário possa executá-las fornecendo N como entrada. Para estes testes, dependendo do valor de N, você deverá exibir a saída no console ou salvá-la em um arquivo. Se N <= 20, utilize a saída em console. Caso contrário, utilize a saída em arquivo.


Etapa 5: Análise das estruturas balanceadas

Nesta etapa, você irá comparar o desempenho da operação de busca nas estruturas implementadas. Para cada estrutura, o seu programa deverá selecionar conjuntos de N registros aleatórios da tabela hash e inseri-los na estrutura. Você deverá inserir apenas o código hash na árvore. Os outros campos do registro serão obtidos acessando a posição correspondente na tabela hash. Após as inserções, você deverá realizar as duas buscas indicadas abaixo.

S1) Obter o total de casos de uma cidade;
S2) Obter o total de casos nas cidades contidas no intervalo [(x0, y0), (x1, y1)], onde x0 e x1 são latitudes e y0 e y1 são longitudes.

Note que, para a busca S2, será necessário combinar os dados da quad tree com os dados da árvore balanceada, ou seja, você deverá primeiro obter a lista de cidades no intervalo e depois procurá-las na estrutura. Os totais de casos podem ser obtidos consultando o registro na tabela hash. Permita ao usuário fornecer os dados necessários para as buscas S1 e S2.

Durante as buscas, deverão ser computados o total de comparações de chaves realizadas. Além disso, os tempos de execução das inserções e das buscas deverão ser medidos. Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M diferentes conjuntos de N registros aleatórios. Minimamente, utilize M = 5. Ao final, compute as médias de cada uma das métricas (comparações e tempo). Salve todos os resultados obtidos em um arquivo saida.txt, contendo tanto os resultados individuais quanto a média final.

Você deverá realizar a simulação descrita acima para os seguintes valores de N:

10.000
50.000
100.000
500.000
1.000.000

Assim, em resumo, para cada valor de N, você deve importar M conjuntos distintos de N registros aleatórios, realizar B buscas e computar métricas conforme especificado. As estruturas de dados que devem ser implementadas são as seguintes:

Árvore AVL
Árvore B (d = 20)
Árvore B (d = 200)

Considere que a ordem d da árvore B representa o número mínimo de chaves em cada nó (exceto a raiz), conforme visto em sala de aula. Não há necessidade de se manter preso aos valores de d especificados acima, o grupo pode adotar valores diferentes (ou mais que dois valores) para os testes. Tenha o cuidado, no entanto, de escolher valores de d que permitam avaliar a diferença no desempenho para árvores de ordem baixa e árvores de ordem alta.


**/

/**Cabeçalho**/
void prefacioTrabalho() ///Capa do trabalho
{
    cout << "Trabalho de Estrutura de Dados 2 (UFJF/ICE/DCC) 2020.3(ERE)" << endl;
    cout << "Grupo:" << endl;
    cout << "Beatriz cunha Rodrigues" << endl;
    cout << "Ivanylson Honorio Gonçalves" << endl;
    cout << "João Pedro Sequeto Nascimento" << endl;
    cout << "Observação: Para executar o código segue abaixo: " << endl;
    cout << "MAC/LINUX:  clear && g++ -std=c++11 *.h *.cpp -o main && ./main .csv " << endl;
    cout << "WINDOWS:    cls & g++ -std=c++11 *.h *.cpp -o main & main.exe " << endl;
    cout << endl;
}
/** Funções**/
vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

void removeAccents(string &str)
{
    string accent_chars = "ÁÀÃÂÇáàãâçÉÊéêÍíÑÓÔÕñóôõÚÜúü";
    string unnacent_chars = "AAAAAAAACCaaaaaaaaccEEEEeeeeIIiiNNOOOOOOnnooooooUUUUuuuu";
    for (int j = 0; str[j] != *"\0"; j++)
    {
        for (int i = 0; i < accent_chars.size(); i = i + 1)
        {
            if (str[j] == accent_chars[i])
            {
                if (str[j + 1] == accent_chars[i + 1])
                {
                    str[j] = unnacent_chars[i];
                    if (str[j] == *"\0")
                    {
                        break;
                    }
                    str.erase(str.begin() + j + 1);
                    break;
                }
                else
                {
                    i++;
                }
            }
        }
        if (str[j] == ' ' && (str[j + 1] >= 'a' && str[j + 1] <= 'z'))
        {
            str[j + 1] = str[j + 1] + 'A' - 'a';
        }
    }
}

void leLinha(ArvoreQuadTree &quad, ifstream &arq, int linhas)
{
    string str;
    string code;
    for (int i = 0; getline(arq, str); i++)
    {
        if (i != 0)
        {
            ApontamentosDeCoordenados *registroCoordenado = new ApontamentosDeCoordenados();
            vector<string> stringDados = split(str, ',');
            registroCoordenado->setStateCode(atoi(stringDados[0].c_str()));
            code = stringDados[1];
            code = code.erase(code.size() - 1);
            registroCoordenado->setCityCode(code);
            removeAccents(stringDados[2]);
            registroCoordenado->setCityName(stringDados[2]);

            registroCoordenado->setLatitude(stod(stringDados[3].c_str()));
            registroCoordenado->setLongitude(stod(stringDados[4].c_str()));

            if (stringDados[5] == "FALSE")
            {
                registroCoordenado->setCapital(false);
            }
            else
            {
                registroCoordenado->setCapital(true);
            }
            NoArvoreQuadTree *no = new NoArvoreQuadTree(registroCoordenado);
            quad.insert(no);

            if (i == linhas)
            {
                break;
            }
        }
    }
}

int leLinhaArquivoProcessadoPraN(vector<Apontamento> &registros, ifstream &arq, int n)
{
    TabelaHash *hash = new TabelaHash(1431490);
    string str;
    int cases, deaths, cont = 0;
    for (int i = 0; getline(arq, str); i++)
    {
        if (i != 0)
        {
            Apontamento *registra = new Apontamento();

            vector<string> stringDados = split(str, ',');

            cases = atoi(stringDados[4].c_str());
            deaths = atoi(stringDados[5].c_str());

            registra->setDate(stringDados[0]);
            registra->setState(stringDados[1]);
            registra->setName(stringDados[2]);
            registra->setCode(stringDados[3].substr(0, 6));
            registra->setCases(cases);
            registra->setDeaths(deaths);

            registros.push_back(*registra);

            if (i == n)
            {
                break;
            }
        }
        cont++;
    }
    cout << "Leitura do arquivo brazil_covid19_cities_processado.csv finalizada." << endl
         << endl;
    return cont;
}

void salvarArquivo(vector<Apontamento> &registros, ofstream &saida)
{
    saida << "date,state,name,code,cases,deaths" << endl;
    for (int i = 0; i < registros.size(); i++)
    {
        saida << registros[i].getDate() << ",";
        saida << registros[i].getState() << ",";
        saida << registros[i].getName() << ",";
        saida << registros[i].getCode() << ",";
        saida << registros[i].getCases() << ",";
        saida << registros[i].getDeaths() << endl;
    }
}

void moduloTesteAlgoritmos(string path, int id, int numeroRegistros)
{
    int identificaOrdenacao;

    cout << endl;

    cout << "Escolha a estrutura de dados" << endl;
    cout << "[1] QuadTree " << endl;
    cout << "[2] HashTable " << endl;
    cout << "[3] AVLTree " << endl;
    cout << "[4] BTree " << endl;
    cout << "[0] Sair " << endl;

    do
    {
        cin >> identificaOrdenacao;

    }
    while (identificaOrdenacao < 0 && identificaOrdenacao > 4);

    if (identificaOrdenacao == 1)
    {
        vector<ApontamentosDeCoordenados> vet;
        ArvoreQuadTree quad;
        path = path + "brazil_cities_coordinates.csv";
        ifstream arquivo;
        arquivo.open(path, ios::in);
        leLinha(quad, arquivo, numeroRegistros);
        arquivo.close();
        if (id == 1)
        {
            quad.imprimePorNivel(quad.getRaiz(), 0);
        }
        else if (id == 2)
        {
            ofstream saida("Resultados/SaidaArvoreQuadTree.txt");
            quad.ImprimeArquivoTexto(quad.getRaiz(), 0, saida);
        }
    }
    else if (identificaOrdenacao == 2)
    {
        vector<Apontamento> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, numeroRegistros);
        TabelaHash *hash = new TabelaHash(tam);
        int hashIndex;
        for (int i = 0; i < tam; i++)
            hash->insert(&registros[i]);
        if(id == 1)
        {
            //printa no console
            for (int i = 0; i < tam; i++)
            {
                hashIndex = hash->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());
                cout  << hash->getRegistroFromTable(hashIndex)->getDate() << ",";
                cout << hash->getRegistroFromTable(hashIndex)->getState() << ",";
                cout << hash->getRegistroFromTable(hashIndex)->getName() << ",";
                cout << hash->getRegistroFromTable(hashIndex)->getCode() << ",";
                cout << hash->getRegistroFromTable(hashIndex)->getCases() << ",";
                cout << hash->getRegistroFromTable(hashIndex)->getDeaths() << endl;
            }

        }
        else
        {
            ofstream saida("Resultados/Hash.txt");
            saida << "date,state,name,code,cases,deaths" << endl;
            for (int i = 0; i < tam; i++)
            {
                hashIndex = hash->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());
                saida << hash->getRegistroFromTable(hashIndex)->getDate() << ",";
                saida << hash->getRegistroFromTable(hashIndex)->getState() << ",";
                saida << hash->getRegistroFromTable(hashIndex)->getName() << ",";
                saida << hash->getRegistroFromTable(hashIndex)->getCode() << ",";
                saida << hash->getRegistroFromTable(hashIndex)->getCases() << ",";
                saida << hash->getRegistroFromTable(hashIndex)->getDeaths() << endl;
            }
        }

    }
    else if (identificaOrdenacao == 3 || identificaOrdenacao == 4)
    {
        vector<Apontamento> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int hashIndex;
        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, numeroRegistros);
        TabelaHash *hash = new TabelaHash(tam);

        ArvoreAVLTree *AVL = new ArvoreAVLTree(hash);
        int ordem = 1;
        if (identificaOrdenacao == 4)
        {
            cout << "Criar arvore B de ordem "; // ordem par
            cin >> ordem;
            ordem = ordem / 2;
        }

        ArvoreBTree *arvb = new ArvoreBTree(ordem, hash);

        for (int i = 0; i < tam; i++)
        {
            if (i == numeroRegistros)
            {
                break;
            }
            hash->insert(&registros[i]);
            hashIndex = hash->searchFromCodeAndDate(registros[i].getCode(), registros[i].getDate());

            if (identificaOrdenacao == 3)
            {
                AVL->insere(hashIndex);
            }
            else
            {
                arvb->insere(hashIndex);
            }
        }

        if (id == 1)
        {
            if (identificaOrdenacao == 3)
            {
                AVL->imprime(hash);
            }
            else
            {
                arvb->getRaiz()->print(hash, 0);
            }
        }
        else if (id == 2)
        {
            if (identificaOrdenacao == 3)
            {
                ofstream saida("Resultados/ArvoreAVLTree.txt");
                cout << "Saida no arquivo .txt" << endl;
                AVL->saidaArqv(saida, hash);
            }
            else
            {
                ofstream saida("Resultados/ArvoreBTree.txt");
                arvb->getRaiz()->salvaArquivo(hash, 0, saida);
            }
        }
        return;
    }
    else if (identificaOrdenacao == 0)
        return;
}

void moduloTeste(string path)
{
    int id;
    do
    {
        int n;
        cout << "------------------------------" << endl;
        cout << "Digite o numero de registros:" << endl;
        cin >> n;
        if (n <= 20)
        {
            moduloTesteAlgoritmos(path, 1, n);
            return;
        }
        else if (n > 20)
        {
            moduloTesteAlgoritmos(path, 2, n);
            return;
        }
    }
    while (id != 0);
}

int menu()
{
    int selecao;
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Modulo de testes" << endl;
    cout << "[2] Analise das estruturas balanceadas" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void analiseParaMRegistros(TabelaHash *hash, vector<ApontamentosDeCoordenados> registrosCoordenados, vector<Apontamento> registros, int m, ofstream &saida, string codigo)
{
    clock_t timeStart, timeStop;
    vector<Apontamento> registros2;
    registros2 = registros;

    double tempoMediaAvl = 0;
    double tempoMediaBtree20 = 0;
    double tempoMediaBtree200 = 0;

    double tempoMedioBuscaAvl = 0;
    double tempoMedioBuscaBtree20 = 0;
    double tempoMedioBuscaBtree200 = 0;

    double totalCasosMedioAvl = 0;
    double totalCasosMedioBtree20 = 0;
    double totalCasosMedioBtree200 = 0;

    double comparacaoMediaBuscaBTree20 = 0;
    double comparacaoMediaBuscaBTree200 = 0;
    double comparacaoMediaBuscaAvl = 0;

    double tempoMedioBuscaAvlS2 = 0;
    double tempoMedioBuscaBtree20S2 = 0;
    double tempoMedioBuscaBtree200S2 = 0;

    double totalCasosMedioAvlS2 = 0;
    double totalCasosMedioBtree20S2 = 0;
    double totalCasosMedioBtree200S2 = 0;

    double comparacaoMediaBuscaBTree20S2 = 0;
    double comparacaoMediaBuscaBTree200S2 = 0;
    double comparacaoMediaBuscaAvlS2 = 0;

    for (int i = 0; i < 5; i++)
    {
        ArvoreAVLTree *avlTree = new ArvoreAVLTree(hash);
        ArvoreBTree *Btree20 = new ArvoreBTree(10, hash);
        ArvoreBTree *Btree200 = new ArvoreBTree(100, hash);


        int comparacaoBuscaBtree20 = 0;
        int comparacaoBuscaBtree200 = 0;
        int comparacaoBuscaAVLtree = 0;

        int totalCasosBtree20 = 0;
        int totalCasosBtree200 = 0;
        int totalCasosAVLtree = 0;

        int comparacaoBuscaBtree20S2 = 0;
        int comparacaoBuscaBtree200S2 = 0;
        int comparacaoBuscaAVLtreeS2 = 0;

        int totalCasosBtree20S2 = 0;
        int totalCasosBtree200S2 = 0;
        int totalCasosAVLtreeS2 = 0;

        random_shuffle(registros2.begin(), registros2.end());

        //AVL
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            avlTree->insere(index);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore AVL :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;

        tempoMediaAvl += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);

        timeStart = clock();
        avlTree->busca(codigo, totalCasosAVLtree, comparacaoBuscaAVLtree);
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S1 Arvore AVL : " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos da cidade selecionada: " << totalCasosAVLtree << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaAVLtree << " para " << m << " registros" << endl;

        tempoMedioBuscaAvl += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        comparacaoMediaBuscaAvl += comparacaoBuscaAVLtree;
        totalCasosMedioAvl += totalCasosAVLtree;

        timeStart = clock();
        for (int i = 0; i < registrosCoordenados.size(); i++)
        {
            avlTree->busca(registrosCoordenados[i].getCityCode(), totalCasosAVLtreeS2, comparacaoBuscaAVLtreeS2);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S2 Arvore AVL : " << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos das cidades no intervalo selecionado: " << totalCasosAVLtreeS2 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaAVLtreeS2 << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMedioBuscaAvlS2 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        comparacaoMediaBuscaAvlS2 += comparacaoBuscaAVLtreeS2;
        totalCasosMedioAvlS2 += totalCasosAVLtreeS2;

        //BTree20
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            Btree20->insere(index);
        }

        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;

        tempoMediaBtree20 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);

        //S1
        timeStart = clock();
        Btree20->calculaTotalCasosCidade(Btree20->getRaiz(), codigo, comparacaoBuscaBtree20, totalCasosBtree20);
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S1 Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos da cidade selecionada: " << totalCasosBtree20 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree20 << " para " << m << " registros" << endl;

        tempoMedioBuscaBtree20 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree20 += totalCasosBtree20;
        comparacaoMediaBuscaBTree20 += comparacaoBuscaBtree20;

        //S2
        timeStart = clock();
        for (int i = 0; i < registrosCoordenados.size(); i++)
        {
            Btree20->calculaTotalCasosCidade(Btree20->getRaiz(), registrosCoordenados[i].getCityCode(), comparacaoBuscaBtree20S2, totalCasosBtree20S2);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S2 Arvore B de ordem 20 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos das cidades no intervalo selecionado: " << totalCasosBtree20S2 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree20S2 << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMedioBuscaBtree20S2 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree20S2 += totalCasosBtree20S2;
        comparacaoMediaBuscaBTree20S2 += comparacaoBuscaBtree20S2;

        //BTree200
        timeStart = clock();
        for (int i = 0; i < m; i++)
        {
            int index = hash->searchFromCodeAndDate(registros2[i].getCode(), registros2[i].getDate());
            Btree200->insere(index);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de insercao Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;

        tempoMediaBtree200 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);

        //S1
        timeStart = clock();
        Btree200->calculaTotalCasosCidade(Btree200->getRaiz(), codigo, comparacaoBuscaBtree200, totalCasosBtree200);
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos da cidade selecionada: " << totalCasosBtree200 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree200 << " para " << m << " registros" << endl;

        tempoMedioBuscaBtree200 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree200 += totalCasosBtree200;
        comparacaoMediaBuscaBTree200 += comparacaoBuscaBtree200;

        //S2
        timeStart = clock();
        for (int i = 0; i < registrosCoordenados.size(); i++)
        {
            Btree200->calculaTotalCasosCidade(Btree200->getRaiz(), registrosCoordenados[i].getCityCode(), comparacaoBuscaBtree200S2, totalCasosBtree200S2);
        }
        timeStop = clock();

        saida << "Tempo de execução do algoritmo de busca S2 Arvore B de ordem 200 :" << ((double)(timeStop - timeStart) / CLOCKS_PER_SEC) << " para " << m << " registros" << endl;
        saida << "Total de casos das cidades no intervalo selecionado: " << totalCasosBtree200S2 << " para " << m << " registros" << endl;
        saida << "Numero de comparacoes durante a execução : " << comparacaoBuscaBtree200S2 << " para " << m << " registros" << endl
              << endl
              << endl;

        tempoMedioBuscaBtree200S2 += ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        totalCasosMedioBtree200S2 += totalCasosBtree200S2;
        comparacaoMediaBuscaBTree200S2 += comparacaoBuscaBtree200S2;
    }

    saida << "MEDIAS" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore AVL : " << tempoMediaAvl / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S1 Arvore AVL : " << tempoMedioBuscaAvl / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaAvl / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos durante a execução : " << totalCasosMedioAvl / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S2 Arvore AVL : " << tempoMedioBuscaAvlS2 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos das cidades no intervalo selecionado: " << totalCasosMedioAvlS2 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaAvlS2 / 5 << " para " << m << " registros" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore B de ordem 20 : " << tempoMediaBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S1 Arvore B de ordem 20 : " << tempoMedioBuscaBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaBTree20 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos durante a execução : " << totalCasosMedioBtree20 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S2 Arvore B de ordem 20 : " << tempoMedioBuscaBtree20S2 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos das cidades no intervalo selecionado: " << totalCasosMedioBtree20S2 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaBTree20S2 / 5 << " para " << m << " registros" << endl
          << endl
          << endl;

    saida << "Tempo de execução médio do algoritmo de insercao Arvore B de ordem 200 : " << tempoMediaBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S1 Arvore B de ordem 200 : " << tempoMedioBuscaBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaBTree200 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos durante a execução : " << totalCasosMedioBtree200 / 5 << " para " << m << " registros" << endl;
    saida << "Tempo de execução médio do algoritmo de Busca S2 Arvore B de ordem 200 : " << tempoMedioBuscaBtree200S2 / 5 << " para " << m << " registros" << endl;
    saida << "Media do total de casos das cidades no intervalo selecionado: " << totalCasosMedioBtree200S2 / 5 << " para " << m << " registros" << endl;
    saida << "Numero de comparacoes médio durante a execução : " << comparacaoMediaBuscaBTree200S2 / 5 << " para " << m << " registros" << endl
          << endl
          << endl
          << endl
          << endl;
}

void seleciona(int selecao, string path)
{
    vector<Apontamento> registros;
    switch (selecao)
    {
    case 1:
    {
        moduloTeste(path);
        break;
    }

    case 2:
    {
        int arr[5] = {10000, 50000, 100000, 500000, 1000000};
        vector<Apontamento> registros;
        string caminho = path;
        caminho += "brazil_covid19_cities_processado.csv";
        ifstream arquivoProcessado;
        arquivoProcessado.open(caminho, ios::in);

        int hashIndex;
        int tam = leLinhaArquivoProcessadoPraN(registros, arquivoProcessado, 1431490);

        ofstream saida("Analise das estruturas.txt");
        TabelaHash *hash = new TabelaHash(1431490);

        for (int i = 0; i < tam; i++)
        {
            hash->insert(&registros[i]);
        }

        ArvoreQuadTree quad;
        string caminho2 = path + "brazil_cities_coordinates.csv";
        ifstream arquivo;
        arquivo.open(caminho2, ios::in);
        leLinha(quad, arquivo, 5571);
        arquivo.close();

        string codigo;
        double latitude1;
        double longitude1;
        double latitude2;
        double longitude2;

        cout << "Digite o codigo da cidade para S1:" << endl;
        cin >> codigo;
        cout << "Digite a maior latitude 1 para S2:" << endl;
        cin >> latitude1;
        cout << "Digite a maior longitude 1 para S2:" << endl;
        cin >> longitude1;
        cout << "Digite a menor latitude 2 para S2:" << endl;
        cin >> latitude2;
        cout << "Digite a menor longitude 2 para S2:" << endl;
        cin >> longitude2;

        vector<ApontamentosDeCoordenados> registrosCoordenados;

        quad.retornaRegistrosNasCoordenadas(registrosCoordenados, quad.getRaiz(), latitude1, longitude1, latitude2, longitude2);

        for (int i = 0; i < 5; i++)
        {
            analiseParaMRegistros(hash, registrosCoordenados, registros, arr[i], saida, codigo);
        }
        break;
    }

    default:
        break;
    }
}

void mainMenu(string path)
{
	    prefacioTrabalho();

    int selecao = menu();
    while (selecao != 0)
    {
        seleciona(selecao, path);
        selecao = menu();
    }
}
