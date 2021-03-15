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
#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include <list>
#include "EntradaHash.h"
using namespace std;

/**
Na apresentação da estrutura de tabelas, a busca por uma chave ocorre sempre através de comparações. Uma alternativa de busca em tabelas dá-se através do cálculo da posição que uma chave ocupa na tabela através de uma função. Esse tipo de função que mapeia um símbolo para valores inteiros é denominado função hash e o tipo de tabela manipulada dessa forma é uma tabela hash.

A grande vantagem na utilização da tabela hash está no desempenho -- enquanto a busca linear tem complexidade temporal $ O(N)$ e a busca binária tem complexidade $ O(\log N)$, o tempo de busca na tabela hash é praticamente independente do número de chaves armazenadas na tabela, ou seja, tem complexidade temporal $ O(1)$. Aplicando a função hash no momento de armazenar e no momento de buscar a chave, a busca pode se restringir diretamente àquela posição da tabela gerada pela função.

Idealmente, cada chave processada por uma função hash geraria uma posição diferente na tabela. No entanto, na prática existem sinônimos -- chaves distintas que resultam em um mesmo valor de hashing. Quando duas ou mais chaves sinônimas são mapeadas para a mesma posição da tabela, diz-se que ocorre uma colisão.

Uma boa função hash deve apresentar duas propriedades básicas: seu cálculo deve ser rápido e deve gerar poucas colisões. Além disso, é desejável que ela leve a uma ocupação uniforme da tabela para conjuntos de chaves quaisquer. Duas funções hash usuais são descritas a seguir:

Meio do quadrado.
Nesse tipo de função, a chave é interpretada como um valor numérico que é elevado ao quadrado. Os $ r$ bits no meio do valor resultante são utilizados como o endereço em uma tabela com $ 2^r$ posições.
Divisão.
Nesse tipo de função, a chave é interpretada como um valor numérico que é dividido por um valor $ M$. O resto dessa divisão inteira, um valor entre 0 e $ M-1$, é considerado o endereço em uma tabela de $ M$ posições. Para reduzir colisões, é recomendável que $ M$ seja um número primo.
Como nem sempre a chave é um valor inteiro que possa ser diretamente utilizado, a técnica de folding pode ser utilizada para reduzir uma chave a um valor inteiro. Nessa técnica, a chave é dividida em segmentos de igual tamanho (exceto pelo último deles, eventualmente) e cada segmento é considerado um valor inteiro. A soma de todos os valores assim obtidos será a entrada para a função hash.

O processamento de tabelas hash demanda a existência de algum mecanismo para o tratamento de colisões. As formas mais usuais de tratamento de colisão são por endereçamento aberto ou por encadeamento.

Na técnica de tratamento de colisão por endereçamento aberto, a estratégia é utilizar o próprio espaço da tabela que ainda não foi ocupado para armazenar a chave que gerou a colisão. Quando a função hash gera para uma chave uma posição que já está ocupada, o procedimento de armazenamento verifica se a posição seguinte também está ocupada; se estiver ocupada, verifica a posição seguinte e assim por diante, até encontrar uma posição livre. (Nesse tipo de tratamento, considera-se a tabela como uma estrutura circular, onde a primeira posição sucede a última posição.) A entrada é então armazenada nessa posição. Se a busca termina na posição inicialmente determinada pela função hash, então a capacidade da tabela está esgotada e uma mensagem de erro é gerada.

No momento da busca, essa varredura da tabela pode ser novamente necessária. Se a chave buscada não está na posição indicada pela função hashing e aquela posição está ocupada, a chave pode eventualmente estar em outra posição na tabela. Assim, é necessário verificar se a chave não está na posição seguinte. Se, por sua vez, essa posição estiver ocupada com outra chave, a busca continua na posição seguinte e assim por diante, até que se encontre a chave buscada ou uma posição sem nenhum símbolo armazenado.
**/
class TabelaHash
{
private:
    EntradaHash **table;
    int tableSize, currentSize;

public:
    TabelaHash(int size);
    ~TabelaHash();

    void insert(Apontamento *registro);
    void remove(int key);
    int searchFromKey(int key);                          // return the hashIndex
    int searchFromCodeAndDate(string code, string date); // return the hashIndex
    int hashCode(int key, int i);
    int mixKeysRegister(Apontamento *registro); // returns a int that can be "hashed"
    int mixKeys(string code, string date);
    int getCurrentSize()
    {
        return currentSize;
    };

    Apontamento *getRegistroFromTable(int key);
};
#endif // TABELAHASH_H_INCLUDED

