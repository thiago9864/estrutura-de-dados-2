/**
    Universidade Federal de Juiz de Fora
    No.h
    Propósito: Implementação de um no generico para as arvores.

    @author Thiago Almeida
    @version 1.0 18/10/19
*/

#ifndef NO_H
#define NO_H

#include <iostream>

using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de BubbleSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class No
{
    public:
        No(int N){
            this->N = N;
            if(this->N > 0){
                //só aloca os vetores se for uma arvore B, que vem com N>0
                this->key = new T[N-1];
                this->child = new No[N];
            }
            this->isLeaf=false;
            this->n=0;
            this->parent=NULL;
            this->color = 1;//o nó começa sempre como vermelho
            this->leftChild = NULL;
            this->rightChild = NULL;
        };
        ~No(){
            delete[] key;
            delete[] child;
            key = NULL;
            child = NULL;
            parent = NULL;
            leftChild = NULL;
            rightChild = NULL;
        };   

        //parametros correspondentes a arvore B
        int N; //numero de elementos do nó
        int *key; //vetor que armazena as chaves
        No* child; //vetor com os filhos
        int n; //conta o número de filhos no vetor de filhos

        //parametros comuns
        bool isLeaf; // true se for nó folha
        No* parent; //ponteiro para o nó superior
        T value; //Valor ou objeto armazenado

        //parametros correspondentes a arvore Rubro-Negra
        int color; //0: Preto, 1: Vermelho
        No *leftChild; //Filho a esquerda
        No *rightChild; //Filho a direita
};

#endif // NO_H
