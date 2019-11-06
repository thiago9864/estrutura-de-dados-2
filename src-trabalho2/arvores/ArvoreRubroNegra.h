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
            this->numComparacoes = 0;
            this->numCopias = 0;
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

        //Função de inserção de Nós na arvore RB
        void inserir(No<T>* v)
        {
            this->root = inserirNo(v,this->root);
        };
        
        //Função auxiliar que insere o Nó. Retorna a raiz, nova ou não - dependendo do caso de inserção
        void inserirNo(No<T>* v, No<T>* p)
        {
            //Se p é null a arvore está vazia
            if(p == nullptr)
            {
                this->numComparacoes++;
                p = new No<T>();
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

        //Função de impressão da arvore RB
       void imprimir()
       {
           this->imprimirPorNivel(this->root,0);
       };

        //Função auxiliar da impressão da arvore RB
       void imprimirPorNivel(No<T>* p, int nivel)
       {
           if(p != nullptr)
           {
               cout << "( " << nivel << " )";
               for(int i = 1; i <= nivel; i++)
               {
                   cout "--";
               }

               cout << p->value; //O que o Nó tá guardando é para ser impresso aqui
               if(p->color)
               {
                   cout << "(V)" << endl;
               } else {
                   cout << "(P)" << endl;
               }
               imprimirPorNivel(p->leftChild,nivel+1);
               imprimirPorNivel(p->rightChild,nivel+1)
           }
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