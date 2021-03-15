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
#include <fstream>
#include "NoArvoreBTree.h"
#include "EntradaHash.h"

using namespace std;


/**
Altura de uma árvore B

O número de acessos ao disco exigidos para a maioria das operações em uma árvore B é proporcional a altura da árvore B.

Como criar uma árvore vazia

Para construir uma árvore B, primeiro criamos um nó raiz vazio,e depois inserimos novas chaves. Esses procedimentos alocam uma página de disco para ser usada como um novo nó no tempo O(1)

As operações básicas sobre uma árvore B são a busca, inserção e remoção de chaves.

Busca
A busca de uma chave k em uma árvore B é muito parecido com uma busca em árvore binária, exceto pelo fato de que, em vez de tomar uma decisão de ramificação binária ou de “duas vias” em cada nó, tomamos uma decisão de ramificação de várias vias, de acordo com o número de filhos do nó. Em cada nó interno x, tomamos uma decisão de ramificação de (n[x] + 1) vias.

Esse método toma como entrada um ponteiro para o nó de raiz de uma subárvore e uma chave k a ser pesquisada.

nserção
A operação de inserção, inicialmente com a árvore vazia, deve garantir que o nó raiz será criado. Criado o nó raiz, a inserção das próximas chaves seguem o mesmo procedimento: busca-se a posição correta da chave em um nó folha e insere a chave garantindo a ordenação destas. Após feito isso, considerando a abordagem de inserção de baixo para cima (Bottom-up) na árvore B, podem ocorrer duas situações:

Página folha está com um número menor de chaves do que o máximo permitido (d-1): Nesse caso apenas inserimos a chave de maneira ordenada na página
Página folha completa ou com o número máximo de chaves permitido (d-1): Nesse caso ocorre o overflow da página em questão e é necessário a operação de split para manter o balanceamento da árvore.
Primeiramente escolhe-se um valor intermediário na sequência ordenada de chaves da página incluindo-se a nova chave que deveria ser inserida. Este valor é exatamente uma chave que ordenada com as chaves da página estará no meio da sequência.
Cria-se uma nova página e os valores maiores do que a chave intermediária são armazenados nessa nova página e os menores continuam na página anterior (operação de split).
Esta chave intermediária escolhida deverá ser inserido na página pai, na qual poderá também sofrer overflow ou deverá ser criada caso em que é criada uma nova página raiz. Esta série de overflows pode se propagar para toda a árvore B, o que garante o seu balanceamento na inserção de chaves.
Uma abordagem melhorada para a inserção é a de cima para baixo (Top-down) que utiliza uma estratégia parecida com a inserção de baixo para cima, a lógica para a inserção das próximas chaves (levando em consideração que a raiz já está criada) é a seguinte: busca-se a posição correta da chave em um nó, porém durante a busca da posição correta todo nó que estiver com o número máximo de chaves (d-1) é feita a operação de split, adicionando o elemento intermediário na sequência ordenada de chaves da página no pai e separando os elementos da página em outras duas novas páginas, onde uma vai conter os elementos menores que o elemento intermediário e a outra os elementos maiores que ele, a inserção será feita em um nó folha somente após todo o processo de split e insere a chave garantindo a ordenação destas. Esta abordagem melhorada previne de ter que ficar fazendo chamadas sucessivas ao pai do nó, o que pode ser caro se o pai estiver na memória secundária

Split
A função do split é dividir o nó em duas partes e "subir" o valor central do nó para um nó acima ou, caso o nó que sofreu o split seja a raiz, criar uma nova raiz com um novo nó. O que ocorre quando é feito um split:

Primeiramente calcula-se qual a mediana dos valores do nó, no caso o valor central do nó. Sendo tamanho = quantidade de elementos no nó, mediana = tamanho/2 e usamos a mediana para acessar o elemento que se encontra no centro do nó, no caso valor_central = valores[mediana];
É testado se o nó que sofreu split tem pai, caso não, cria-se um novo nó apenas com o valor valor_central e o define como a nova raiz. São criados mais dois nós, cada um irá conter os valores do nó que estavam antes da mediana e depois da mediana. Um nó terá os valores menores que o valor_central e ficará na primeira posição dos filhos da nova raiz, e o outro nó terá os valores maiores que o valor_central e ficará na segunda posição dos filhos da nova raiz;
Caso o nó tenha pai, adicionamos o valor_central ao nó pai. Caso o nó pai já esteja cheio, este também vai sofrer split após a inserção do valor nele. E da mesma forma que criamos dois nós para o caso do nó não ter pai, criaremos dois nós que conterão os valores menores e maiores que o valor_central. O nó com os menores valores ficará posicionado como filho do lado esquerdo do valor_central e o nó com os maiores valores ficará posicionado como filho do lado direito do valor_central. Por exemplo: Caso o valor_central seja inserido na posição 0 do array de valores do nó pai, o nó filho com os menores valores ficará na posição 0 do array de filhos, e o nó com os maiores valores ficará na posição 1 do array de filhos.

**/


/**
O termo estrutura de dados é utilizado para referenciar diferentes formas de representação de
dados. A escolha de uma determinada estrutura para representar um conjunto de dados relacionados
deve-se, principalmente, ao tipo de operações que serão realizadas sobre o mesmo, usando uma
manipulação otimizada em relação ao tempo necessário para efetuar as operações e á área de
armazenamento requisitada para guardar estes dados.
 A entidade elementar de uma estrutura de dados é o nodo (nó). Um nodo é diferenciado pelo
seu endereço relativo dentro da estrutura e pode ser constituído de um ou vários campos.
**/
NoArvoreBTree::NoArvoreBTree(int tamanho, bool folha)
{
    this->folha = folha;
    this->ordem = tamanho;

    this->n = 0;

    this->keys = new int[2 * ordem - 1];
    this->filhos = new NoArvoreBTree *[2 * ordem];
}

NoArvoreBTree::~NoArvoreBTree()
{
}

int NoArvoreBTree::getOrdem()
{
    return this->ordem;
}

void NoArvoreBTree::setN(int i)
{
    this->n = i;
}

int NoArvoreBTree::getN()
{
    return this->n;
}

bool NoArvoreBTree::getFolha()
{
    return this->folha;
}

void NoArvoreBTree::setFolha(bool trueOrfalse)
{
    this->folha = trueOrfalse;
}

int *NoArvoreBTree::getKeys()
{
    return this->keys;
}

void NoArvoreBTree::setKeys(int key, int position)
{
    this->keys[position] = key;
}

NoArvoreBTree **NoArvoreBTree::getFilhos()
{
    return this->filhos;
}

void NoArvoreBTree::setFilhos(NoArvoreBTree *filho, int i)
{
    this->filhos[i] = filho;
}

void NoArvoreBTree::salvaArquivo(TabelaHash *registros, int nivel, ofstream &saida)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->salvaArquivo(registros, nivel + 1,saida);

        saida << "( Nivel : " ;
        saida << nivel;
        saida << " ) ";
        saida << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
        saida << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->salvaArquivo(registros, nivel + 1,saida);
}

void NoArvoreBTree::print(TabelaHash *registros, int nivel)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!folha)
            filhos[i]->print(registros, nivel + 1);
        cout << "( Nivel : " << nivel << " ) ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getCode() << " ";
        cout << registros->getRegistroFromTable(getKeys()[i])->getDate() << endl;
    }

    if (!folha)
        filhos[i]->print(registros, nivel + 1);
}
