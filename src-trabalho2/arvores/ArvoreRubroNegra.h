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
#include "UserReview.h"
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
        void inserir(T valor)
        {
            this->root = inserirNo(valor,this->root);
        };

        //Função auxiliar que insere o Nó. Retorna a raiz, nova ou não - dependendo do caso de inserção
        void inserirNo(T valor, No<T>* p)
        {
            //Se p é null a arvore está vazia
            if(p == nullptr)
            {
                this->registraComparacao();
                p = new No<T>();
                p->value = valor;
                p->color = 0; //Preta para raiz
            } else {
                No<T>* pai;
                while(p != nullptr)
                {
                    pai = p;
                    this->registraComparacao();

                    if(valor < p->value)
                    {
                        p = p->leftChild;
                    } else {
                        p = p->rightChild;
                    }
                }

                p = new No<T>();
                p->parent = pai;
                p->value= valor;
                this->registraComparacao();

                if(valor > pai->value)
                {
                    pai->rightChild = p;
                } else {
                    pai->leftChild= p;
                }

                No<T>* auxRoot;
                while(p != nullptr)
                {
                    this->registraComparacao();
                    p = verificaArvore(p);
                    auxRoot = p;
                    p = p->parent;
                }
            }

            return auxRoot;
        };

        //Função que verifica se há necessidade de correção na arvore vermelho preta
        No<T>* verficaArvore(No<T>* p)
        {
            this->registraComparacao();
            if(p->parent == nullptr)
            {
                p->color = false;
                return p;
            } else {
                this->registraComparacao();
                if(!(p->parent->color)) //Verifica se o pai é preto
                {
                    return p;
                } else {
                    No<T>* pai = p->parent;
                    No<T>* avo = p->parent->parent;
                    No<T>* tio = this->getTio(p);

                    this->registraComparacao();
                    if(p->color && pai->color)
                    {
                        this->registraComparacao();
                        if(tio != nullptr)
                        {
                            if(tio->color)
                            {
                                avo->color = true;
                                tio->color = false;
                                pai->color = false;
                            } else {
                                p = verificarRotacao(p);
                            }
                        }
                    }
                    return p;
                }
            }
        };

        No<T>* verificarRotacao(No<T>* p)
        {
            No<T>* pai = p->parent;
            No<T>* avo = p->parent->parent;

            this->registraComparacao();
            if(avo->leftChild == pai)
            {
                this->registraComparacao();
                if(pai->rightChild == p)
                {
                    avo = rotacaoDuplaEsqDir(avo);
                } else
                {
                    avo = rotacaoSimplesDir(avo);
                }
            } else {
                this->registraComparacao(); 
                if(pai->rightChild == p)
                {
                    avo = rotacaoSimplesEsq(avo);
                } else {
                    avo = rotacaoDuplaDirEsq(avo);
                }
            }

            avo->color = false;
            avo->leftChild->color = true;
            avo->rightChild->color = true;
            return avo;
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
        };

        /*CASOS DE ROTAÇÃO DA AVORE RUBRO NEGRA*/
        No<T>* rotacaoSimplesEsq(No<T>* p)
        {
            No<T>* pai = p->rightChild;
            No<T>* a = p->leftChild;
            No<T>* b = p->leftChild;
            No<T>* c = p->parent;

            pai->leftChild = p;
            p->leftChild = a;
            p->rightChild = b;

            if(a)
            {
                a->parent = p;
            } 
            if(b)
            {
                b->parent = p;
            }

            p->parent = pai;
            pai->parent = c;

            if(c)
            {
                c->leftChild = pai;
            }
            
            return pai;
        };

        //Remoção de um Nó
        void remover(T valor)
        {
            this->root= removerNo(valor,this->root);
        };

        No<T>* removerNo(T valor, No<T>* p)
        {
            this->registraComparacao();
            if(p == nullptr)
            {
                return nullptr;
            } else if(valor < p->value)
            {
                this->registraComparacao();
                removerNo(valor,p->leftChild);
            } else if(valor > p->value)
            {
                removerNo(valor,p->rightChild);
            } else {

                if(p->rightChild == nullptr && p->leftChild == nullptr)
                {
                    this->registraComparacao();
                    this->registraComparacao();

                    p = casoNoFolha(p);
                } else if((p->rightChild == nullptr) ||(p->leftChild == nullptr))
                {
                    this->registraComparacao();
                    this->registraComparacao();

                    p = casoNoUmFilho(p);
                } else {
                    p = casoNoDoisFilhos(valor,p);
                }
            }
            return p;
        };

        No<T>* casoNoUmFilho(No<T>* p)
        {
            No<T>* aux;
            this->registraComparacao();
            if(p->leftChild == nullptr)
            {
                aux = p->rightChild;
                p->value = aux->value;
                p->rightChild = aux->rightChild;
                p->leftChild = aux->leftChild;
                
                delete aux;
            } else {
                aux = p->leftChild;
                p->value = aux->value;
                p->rightChild = aux->rightChild;
                p->leftChild = aux->leftChild;

                delete aux;
            }
            return p;
        };

        No<T>* casoDoisFilhos(T valor,No<T>* p)
        {

        };

        No<T>* casoNoFolha(No<T>* p)
        {

        };

        No<T>* rotacaoSimplesDir(No<T>* p)
        {
            No<T>* pai = p->leftChild;
            No<T>* a = p->rightChild;
            No<T>* b = p->rightChild;
            No<T>* c = p->parent;

            pai->rightChild= p;
            p->rightChild= a;
            p->leftChild = b;

            if(a)
            {
                a->parent = p;
            } 
            if(b)
            {
                b->parent = p;
            }

            p->parent = pai;
            pai->parent = c;

            if(c)
            {
                c->rightChild = pai;
            }

            return pai;
        };

        No<T>* rotacaoDuplaEsqDir(No<T>* p)
        {
            No<T>* pai = p->leftChild;

            p->leftChild = this->rotacaoSimplesEsq(pai);
            p->leftChild->parent = p;
            return rotacaoSimplesDir(p);
        };

        No<T>* rotacaoDuplaDirEsq(No<T>* p)
        {
            No<T>* pai = p->leftChild;

            p->leftChild = this->rotacaoSimplesDir(pai);
            p->leftChild->parent = p;
            return rotacaoSimplesEsq(p);
        }

        
        
};

#endif //SRC_TRABALHO2_ARVORERUBRONEGRA_H