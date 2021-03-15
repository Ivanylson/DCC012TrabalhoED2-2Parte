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
#ifndef ARVOREAVLTREE_H_INCLUDED
#define ARVOREAVLTREE_H_INCLUDED

#include <fstream>
#include "NoArvoreAVLTree.h"
#include "TabelaHash.h"

using namespace std;
/**
Uma árvore binária T é denominada AVL quando, para qualquer nó de T, as alturas de suas duas subárvores, esquerda e direita, diferem em módulo de até uma unidade.


Uma árvore AVL
Pela definição fica estabelecido que todos os nós de uma árvore AVL devem respeitar a seguinte propriedade:

|hd(u) - he(u)| ≤ 1, onde hd(u) é a altura da subárvore direita do nó u e he(u) é a altura da subárvore esquerda do nó u.

O valor hd(u) - he(u) é denominado fator de balanço do nó. Quando um nó possui fator de balanço com valor -1, 0 ou 1 então o mesmo é um nó regulado. Todos os nós de uma árvore AVL são regulados, caso contrário a árvore não é AVL.
**/

/**
Balanceamento
Toda árvore AVL é balanceada, isto é, sua altura é O(log n).[5]

A vantagem do balanceamento é possibilitar que a busca seja de complexidade O(log n). Entretanto, as operações de inserção e remoção devem possuir custo similar. No caso da árvore AVL, a inserção e remoção têm custo O(log n).

Por definição, todos os nós da AVL devem ter fb = -1, 0 ou 1.

Para garantir essa propriedade, a cada inserção ou remoção o fator de balanço deve ser atualizado a partir do pai do nó inserido até a raiz da árvore. Na inserção basta encontrar o primeiro nó desregulado (fb= -2 ou fb= 2), aplicar o operação de rotação necessária, não havendo necessidade de verificar os demais nós. Na remoção a verificação deverá prosseguir até a raiz, podendo requerer mais de uma rotação.

Uma árvore AVL sempre terá um tamanho menor que[6]:  
**/

/**
Busca
A busca é a mesma utilizada em árvore binária de busca.

A busca pela chave de valor K inicia sempre pelo nó raiz da árvore.

Seja pt_u um ponteiro para o nó u sendo verificado. Caso o pt_u seja nulo então a busca não foi bem sucedida (K não está na árvore ou árvore vazia). Verificar se a chave K igual pt_u->chave (valor chave armazenado no nó u), então a busca foi bem sucedida. Caso contrário, se K < pt_u->chave então a busca segue pela subárvore esquerda; caso contrário, a busca segue pela subárvore direita.
**/

/**
Inserção
Para inserir um novo nó de valor K em uma árvore AVL é necessária uma busca por K nesta mesma árvore. Após a busca o local correto para a inserção do nó K será em uma subárvore vazia de uma folha da árvore. Depois de inserido o nó, a altura do nó pai e de todos os nós acima deve ser atualizada. Em seguida o algoritmo de rotação simples ou dupla deve ser acionado para o primeiro nó pai desregulado.
**/

/**
Remoção
O primeiro passo para remover uma chave K consiste em realizar uma busca binária a partir do nó raiz. Caso a busca encerre em uma subárvore vazia, então a chave não está na árvore e a remoção não pode ser realizada. Caso a busca encerre em um nó u o nó que contenha a chave então a remoção poderá ser realizada da seguinte forma:

Caso 1: O nó u é uma folha da árvore, apenas exclui-lo.

Caso 2: O nó u tem apenas uma subárvore, necessariamente composta de um nó folha, basta apontar o nó pai de u para a única subárvore e excluir o nó u.

Caso 3: O nó u tem duas subárvores: localizar o nó v predecessor ou sucessor de K, que sempre será um nó folha ou possuirá apenas uma subárvore; copiar a chave de v para o nó u; excluir o nó v a partir da respectiva subárvore de u.

O último passo consiste em verificar a desregulagem de todos nós a partir do pai do nó excluído até o nó raiz da árvore. Aplicar rotação simples ou dupla em cada nó desregulado
**/
class ArvoreAVLTree
{
public:
    
    ArvoreAVLTree(TabelaHash *tabela);  // CONSTRUTOR
    ~ArvoreAVLTree(); // DESTRUTOR

    bool vazia(); // VERIFICA SE A ÁRVORE ESTÁ VAZIA

    void busca(string code,int &totalCasos, int &comparacoes); // BUSCA

    void insere(int val); // INSERÇÃO

    void imprime(TabelaHash *registros); // IMPRESSÃO NO TERMINAL

    void saidaArqv(ofstream &saida, TabelaHash *registros); // IMPRESSÃO POR ARQUIVO

    int altura (NoArvoreAVLTree* raiz); // CALCULA A ALTURA DE UM NÓ

    bool menorElemento(Apontamento *candidatoInicio, Apontamento *candidatoFim);

    int retornaMaior(int a, int b);

private:
    NoArvoreAVLTree* raiz; // PONTEIRO PARA A RAIZ DA ÁRVORE
    TabelaHash *registros;

    // FUNÇÕES AUX
    void auxBusca(NoArvoreAVLTree *p, string code, int &totalCasos, int &comparacoes); // BUSCA
    NoArvoreAVLTree* auxInsere(NoArvoreAVLTree *p, int val); // INSERÇÃO
    void auxSaidaArqv(NoArvoreAVLTree *p, int nivel, ofstream &saida, TabelaHash *registros); // IMPRESSÃO POR ARQUIVO
    
    void imprimePorNivel(NoArvoreAVLTree* p, int nivel, TabelaHash *registros); // IMPRESSÃO NO TERMINAL
    
    NoArvoreAVLTree* libera(NoArvoreAVLTree *p); // AUXILIAR DO DESTRUTOR

    int calculaFB(NoArvoreAVLTree* no);
    // ROTAÇÕES
    NoArvoreAVLTree* rotacaoEsquerda(NoArvoreAVLTree* no);
    NoArvoreAVLTree* rotacaoDireita(NoArvoreAVLTree* no);
};
#endif // ARVOREAVLTREE_H_INCLUDED
