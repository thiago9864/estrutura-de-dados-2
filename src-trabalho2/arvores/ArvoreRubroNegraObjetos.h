/**
    Universidade Federal de Juiz de Fora
    ArvoreRubroNegraObjetos.h
    Propósito: Classe para implementar a arvore rubro negra
    @author: Renan Nunes da Costa Gonçalves
    @version 1.0 27/10/2019
*/

#ifndef SRC_TRABALHO2_ARVORERUBRONEGRAOBJETOS_H
#define SRC_TRABALHO2_ARVORERUBRONEGRAObjetosOBJETOS_H

#include <iostream>
#include <math.h>
#include "BaseArvores.h"
#include "../UserReview.h"
#include "NoObjeto.h"

//template <class T>
class ArvoreRubroNegraObjetos : public BaseArvores
{
    private:
        NoRubroNegro *root;
        int N;

    public:

        ArvoreRubroNegraObjetos()
        {
            this->root = nullptr;
            
        };

        ~ArvoreRubroNegraObjetos()
        {
            this->auxDestrutor(this->root);
        };

        // Função Para auxiliar o destrutor da Árvore RB
        void auxDestrutor(NoRubroNegro* p)
        {
            if(p != nullptr)
            {
                this->auxDestrutor(p->leftChild);
                this->auxDestrutor(p->rightChild);
                delete p;
            }
        };

        //Função de inserção de Nós na arvore RB
        void inserir(UserReview valor)
        {
            this->root = inserirNo(valor,this->root);
        };

        //Função auxiliar que insere o Nó. Retorna a raiz, nova ou não - dependendo do caso de inserção
        NoRubroNegro* inserirNo(UserReview valor, NoRubroNegro* p)
        {
            NoRubroNegro* auxRoot; //Auxiliar para a raiz que será retornado caso o novo Nó seja inserido
            //Se p é null a arvore está vazia
            if(p == nullptr)
            {
                this->registraComparacao();
                this->registraCopia();
                p = new NoRubroNegro();
                p->value = valor;
                p->color = 0; //Preta para raiz
            } else {
                NoRubroNegro* pai;
                while(p != nullptr)
                {
                    pai = p;
                    this->registraComparacao();

                    if(valor.id < p->value.id)
                    {
                        p = p->leftChild;
                    } else {
                        p = p->rightChild;
                    }
                }

                p = new NoRubroNegro();
                p->parent = pai;
                p->value= valor;
                this->registraComparacao();
                this->registraCopia();

                if(valor.id > pai->value.id)
                {
                    pai->rightChild = p;
                } else {
                    pai->leftChild= p;
                }

                //NoRubroNegro* auxRoot;
                while(p != nullptr)
                {
                    this->registraComparacao();
                    p = verficaArvore(p);
                    auxRoot = p;
                    p = p->parent;
                }
            }

            //return auxRoot;
        };

        //Função que verifica se há necessidade de correção na arvore vermelho preta
        NoRubroNegro* verficaArvore(NoRubroNegro* p)
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
                    NoRubroNegro* pai = p->parent;
                    NoRubroNegro* avo = p->parent->parent;
                    NoRubroNegro* tio = this->getTio(p);

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

        NoRubroNegro* verificarRotacao(NoRubroNegro* p)
        {
            NoRubroNegro* pai = p->parent;
            NoRubroNegro* avo = p->parent->parent;

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
        int alturaNegra(NoRubroNegro* p)
        {
            if(p == nullptr)
            {
                return 0; //Caso seja null, a altura da árvore é zero
            } else {
                //Caso contrário, verifica recursivamente a quantidade de elementos negros do lado esquerdo e direito
                //O menor entre eles é a altura negra da árvore

                int alturaEsquerda = 0, alturaDireita = 0;
                NoRubroNegro* filhoEsquerda = p->leftChild;
                NoRubroNegro* filhoDireita = p->rightChild;

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
       void imprimirPorNivel(NoRubroNegro* p, int nivel)
       {
           if(p != nullptr)
           {
               cout << "( " << nivel << " )";
               for(int i = 1; i <= nivel; i++)
               {
                   cout << "--";
               }

               cout << p->value.id; //O que o Nó tá guardando é para ser impresso aqui
               if(p->color)
               {
                   cout << "(V)" << endl;
               } else {
                   cout << "(P)" << endl;
               }
               imprimirPorNivel(p->leftChild,nivel+1);
               imprimirPorNivel(p->rightChild,nivel+1);
           }
       };


       //Função que retorna o irmão do Nó
       NoRubroNegro* getIrmao(NoRubroNegro* n)
       {
           NoRubroNegro* pai = n->parent;

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
        NoRubroNegro* getTio(NoRubroNegro* n)
        {
           NoRubroNegro* avo = n->parent->parent; //Obtém o "Nó avô"

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

        //Função que retorna o "Neto" do Nó
        NoRubroNegro* getNeto(NoRubroNegro* n)
        {
            NoRubroNegro* pai = n->parent;
            NoRubroNegro* aux;

            if(pai->leftChild == n)
            {
                if(aux->leftChild != nullptr && aux->leftChild->color)
                    return aux->leftChild;
                else
                {
                    return aux->rightChild;
                }
                
            } else {
                aux = pai->rightChild;

                if(aux->rightChild != nullptr && aux->rightChild->color)
                    return aux->rightChild;
                else
                {
                    return aux->leftChild;
                }
                
            }

        };

        /*CASOS DE ROTAÇÃO DA AVORE RUBRO NEGRA*/
        NoRubroNegro* rotacaoSimplesEsq(NoRubroNegro* p)
        {
            NoRubroNegro* pai = p->rightChild;
            NoRubroNegro* a = p->leftChild;
            NoRubroNegro* b = p->leftChild;
            NoRubroNegro* c = p->parent;

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
        void remover(UserReview valor)
        {
            this->root= removerNo(valor,this->root);
        };

        NoRubroNegro* removerNo(UserReview valor, NoRubroNegro* p)
        {
            this->registraComparacao();
            if(p == nullptr)
            {
                return nullptr;
            } else if(valor.id < p->value.id)
            {
                this->registraComparacao();
                removerNo(valor,p->leftChild);
            } else if(valor.id > p->value.id)
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
                    p = casoDoisFilhos(valor,p);
                }
            }
            return p;
        };

        NoRubroNegro* casoNoUmFilho(NoRubroNegro* p)
        {
            NoRubroNegro* aux;
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

        NoRubroNegro* casoDoisFilhos(UserReview valor,NoRubroNegro* p)
        {
            NoRubroNegro* aux;

            aux = p->rightChild;
            while(aux->leftChild != nullptr)
            {
                this->registraComparacao();
                aux = aux->leftChild;
            }

            p->value = aux->value;
            aux->value = valor;
            removerNo(valor,p->rightChild);
            return p;
        };

        NoRubroNegro* casoNoFolha(NoRubroNegro* p)
        {
            this->registraComparacao();
            if(p->parent == nullptr)
            {
                delete p;
            } else if(p->color)
            {
                this->registraComparacao();
                NoRubroNegro* pai = p->parent;
                this->registraComparacao();
                if(pai->rightChild == p)
                    p->rightChild = nullptr;
                else
                    pai->leftChild = nullptr;

                delete p;
            } else {
                if(this->getIrmao(p)->color)
                {
                    this->registraComparacao();

                    NoRubroNegro* pai = p->parent;
                    this->registraComparacao();
                    if(pai->rightChild == p)
                    {
                        pai->rightChild = nullptr;
                        delete p;
                        pai = rotacaoDuplaEsqDir(pai);
                    } else {
                        pai->leftChild = nullptr;
                        delete p;
                        pai = rotacaoDuplaDirEsq(pai);
                    }
                } else {
                    NoRubroNegro* irmao = getIrmao(p);
                    NoRubroNegro* pai = p->parent;
                    this->getNumComparacoes();
                    this->getNumComparacoes();
                    if(!(irmao->rightChild->color) && !(irmao->leftChild->color))
                    {
                        this->getNumComparacoes();
                        if(pai->rightChild == p)
                        {
                            pai->rightChild = nullptr;
                            delete p;
                        } else {
                            pai->leftChild = nullptr;
                            delete p;
                        }
                        trocarCor(pai);
                        trocarCor(irmao);
                    } else {
                        NoRubroNegro* neto = this->getNeto(p);
                        this->registraComparacao();
                        if(pai->rightChild == p)
                        {
                            pai->rightChild = nullptr;
                            delete p;
                        } else {
                            pai = verificarRotacao(neto);
                            trocarCor(neto);
                            trocarCor(getIrmao(neto));
                        }
                    }
                }
            }
            return nullptr;
        };

        void trocarCor(NoRubroNegro* p)
        {
            if(p->color)
                p->color = false;
            else
                p->color = true;

        };

        NoRubroNegro* rotacaoSimplesDir(NoRubroNegro* p)
        {
            NoRubroNegro* pai = p->leftChild;
            NoRubroNegro* a = p->rightChild;
            NoRubroNegro* b = p->rightChild;
            NoRubroNegro* c = p->parent;

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

        NoRubroNegro* rotacaoDuplaEsqDir(NoRubroNegro* p)
        {
            NoRubroNegro* pai = p->leftChild;

            p->leftChild = this->rotacaoSimplesEsq(pai);
            p->leftChild->parent = p;
            return rotacaoSimplesDir(p);
        };

        NoRubroNegro* rotacaoDuplaDirEsq(NoRubroNegro* p)
        {
            NoRubroNegro* pai = p->leftChild;

            p->leftChild = this->rotacaoSimplesDir(pai);
            p->leftChild->parent = p;
            return rotacaoSimplesEsq(p);
        }



};

#endif //SRC_TRABALHO2_ARVORERUBRONEGRAOBJETOS_H