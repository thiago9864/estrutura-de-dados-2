/**
    Universidade Federal de Juiz de Fora
    ArvoreRubroNegra.h
    Propósito: Classe para implementar a arvore rubro negra
    @author: Renan Nunes da Costa Gonçalves
    @version 1.0 27/10/2019
*/

#ifndef SRC_TRABALHO2_ARVORERUBRONEGRA_H
#define SRC_TRABALHO2_ARVORERUBRONEGRA_H

#include <iostream>
#include <math.h>
#include "BaseArvores.h"
#include "No.h"


template <class T> 
class ArvoreRubroNegra : protected BaseArvores{

    private:
        No<T> *root;
        int N;

    public:

        ArvoreRubroNegra()
        {
            this->root = nullptr;
        };

        ~ArvoreRubroNegra()
        {
            this->auxDestrutor(this->root);
        };

        // Função Para auxiliar o destrutor da Árvore RB
        void auxDestrutor(No<T>* p)
        {
            if(p != nullptr)
            {
                this->auxDestrutor(p->leftChild);
                this->auxDestrutor(p->rightChild);
                delete p;
            }
        };

        //Função que calcula a altura da árvore RB a partir de um Nó
        int alturaNegra(No<T>* p)
        {
            if(p == nullptr)
            {
                return 0; //Caso seja null, a altura da árvore é zero
            } else {
                //Caso contrário, verifica recursivamente a quantidade de elementos negros do lado esquerdo e direito
                //O menor entre eles é a altura negra da árvore

                int alturaEsquerda = 0, alturaDireita = 0;
                No<T>* filhoEsquerda = p->leftChild;
                No<T>* filhoDireita = p->rightChild;

                if((filhoDireita != nullptr) && (filhoEsquerda != nullptr))
                {

                    //Se ambos os filhos existirem, verifica a cor deles
                    if(filhoEsquerda->color == filhoDireita->color)
                    {
                        //1 é vermelho, 0 é preto
                        //Se ambos os filhos forem vermelhos ou pretos,verificamos a altura dos dois lados
                        alturaEsquerda = this->alturaNegra(filhoEsquerda);
                        alturaDireita = this->alturaNegra(filhoDireita);
                    } else {

                        //Caso contrário checamos qual filho é vermelho e qual é preto, verificamos a altura do filho vermelho
                        if(filhoDireita->color) //Vermelho é verdadeiro
                        {
                            alturaDireita = this->alturaNegra(filhoDireita);
                        } else { //Preto é falso
                            alturaEsquerda = this->alturaNegra(filhoEsquerda);
                        }

                    }
                } else {
                    //Se pelo menos um dos filhos não existir, verificamos ambos os lados.

                    alturaEsquerda = this->alturaNegra(filhoEsquerda);
                    alturaDireita = this->alturaNegra(filhoDireita);
                }

                //No final de cada execução da recursividade é realmente somado ao lado com maior altura negra
                if(alturaEsquerda > alturaDireita)
                    return alturaEsquerda+1;
                else 
                    return alturaDireita+1;
            }
        };


        /*Operações*/
        void leftRotate(No<int>* no)
        { 
            No<int>* p = no->rightChild;
            no->rightChild = p->leftChild;

            if(p->leftChild != nullptr)
            {
                p->leftChild->parent = no;
            }
            p->parent = no->parent;

            if(no->parent == nullptr)
            {
                this->root = p;
            } else 
            {
                if (no == (no->parent)->leftChild)
                {
                    no->parent->leftChild = p;
                } else 
                {
                    no->parent->rightChild = p;
                }
            }
            p->leftChild = no;
            no->parent = p;
        };

        void rightRotate(No<int>* n)
        {
            No<int>* p = n->leftChild;
            n->leftChild = p->rightChild;

            if(p->rightChild != nullptr)
            {
                p->rightChild->parent = n;
            }
            p->parent = n->parent;

            if(n->parent == nullptr)
            {
                this->root = p;
            } else 
            {
                if (n == (n->parent)->rightChild)
                {
                    n->parent->rightChild  = p;
                } else 
                {
                    n->parent->leftChild = p;
                }
            }
            p->rightChild = n;
            n->parent = p;
        };

        No<int>* insere(No<int>* root,No<int>* no)
        {
            insereRecursivo(root, no);

            insereReparando(no);

            root = no;
            while(root->parent != nullptr)
            {
                root = root->parent;
            }
            return root;
        };

        void insereRecursivo(No<int>* root,No<int>* no)
        {
            if(root != nullptr && no->key < root->key)
            {
                if(root->leftChild != nullptr)
                {
                    insereRecursivo(root->leftChild,no);
                    return;
                } else 
                {
                    root->leftChild = no;
                }
            } else if (root != nullptr)
            {
                if(root->rightChild != nullptr)
                {
                    insereRecursivo(root->rightChild,no);
                    return;
                } else {
                    root->rightChild = no;
                }
            }

            no->parent = root;
            no->leftChild = nullptr;
            no->rightChild = nullptr;
            no->color = 1; //Vermelho
        };

        void insereReparando(No<int>* no)
        {
            if(no->parent == nullptr)
            {
                if(getParent(no) == nullptr)
                {
                    no->color = 0; // Preto
                }

            } else if (no->parent->color == 0)
            {
                return;
            } else if (getUncle(no) != nullptr && getUncle(no)->color == 0)
            {
                getParent(no)->color = 0; //Preto
                getUncle(no)->color = 0; //Preto
                getGrandParent(no)->color = 1; //Vermelho
                insereReparando(getGrandParent(no));
            } else {
                No<int>* p = getParent(no);
                No<int>* g = getGrandParent(no);

                if(no == p->rightChild && p == g->leftChild)
                {
                    leftRotate(p);
                    no = no->leftChild;
                } else if (no == p->leftChild && p == g->rightChild)
                {
                    leftRotate(p);
                    no = no->rightChild;
                }

                insereCaso(no);
            }
        };

        void insereCaso(No<int>* n)
        {
            No<int>* p = getParent(n);
            No<int>* g = getGrandParent(n);

            if(n == p->leftChild)
            {
                rightRotate(g);
            } else {
                rightRotate(g);
            }

            p->color = 0; //Preto
            g->color = 1; //Vermelho
        }

        void remove(No<int>* no)
        {

        };


       //Função que retorna o irmão do Nó
       No<T>* getIrmao(No<T>* n)
       {
           No<T>* pai = n->parent;

           //Verifica a existencia do pai, caso contrário retorna null
           if(pai != nullptr)
           {
               if(pai->rightChild == n)
               {
                   return pai->leftChild;
               } else {
                   return pai->rightChild;
               }
           } else {
               return nullptr;
           }
       };

        //Função que retorna o "Tio" do Nó
        No<T>* getTio(No<T>* n)
        {
           No<T>* avo = n->parent->parent; //Obtém o "Nó avô"

           //Verifica se o Nó avô existe
           if(avo != nullptr)
           {
               if(avo->rightChild == n->parent)
               {
                   return avo->leftChild;
               } else {
                   return avo->rightChild;
               }
           } else {
               return nullptr;
           }
        }



};

#endif //SRC_TRABALHO2_ARVORERUBRONEGRA_H