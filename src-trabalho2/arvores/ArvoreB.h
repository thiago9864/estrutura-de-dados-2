/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar a arvore B

    @author: Luan Reis Ciribelli
    @version 1.0 27/11/2019



*/

#ifndef SRC_TRABALHO2_ARVOREB_H
#define SRC_TRABALHO2_ARVOREB_H

#include <iostream>
#include "BaseArvores.h"
#include "NoB.h"

class ArvoreB : public BaseArvores
{
private:
    NoB *raiz; //ponteiro pra raiz
    int t;     // grau minimo

public:
    ArvoreB(int _t) //construtor arvore
    {
        raiz = NULL;
        t = _t;
    }
    // função que percorre a arvore chamando a função equivalente no Nó, começando pela raiz

    void percorre()
    {
        if (raiz != NULL)
            raiz->percorre();
    }
    // função que procura um Nó arvore chamando a função equivalente no Nó

    NoB *procura(int k)
    {
        return (raiz == NULL) ? NULL : raiz->procura(k);
    }
    // Função que insere na arvore usando os metodos "inserenaocheio" e "dividefilho", implementadas no Nó

    void insert(int k)
    {

        if (raiz == NULL)
        {

            raiz = new NoB(t, true);
            raiz->chave[0] = k;
            raiz->n = 1;
        }
        else
        {
            if (raiz->n == 2 * t - 1)
            {
                NoB *s = new NoB(t, false);

                s->C[0] = raiz;
                registraCopia();

                s->dividefilho(0, raiz);

                int i = 0;
                if (s->chave[0] < k)
                {
                    registraComparacao();
                    i++;
                }
                s->C[i]->inserenaocheio(k);

                raiz = s;
            }
            else
            {
                raiz->inserenaocheio(k);
            }
        }
    }
    // Função que remove um Nó passado, utiliza a função "remove" implementada no Nó.

    void remove(int k)
    {
        if (!raiz)
        {
            cout << "A arvore está vazia\n";
            return;
        }

        raiz->remove(k);

        if (raiz->n == 0)
        {
            registraComparacao();
            NoB *tmp = raiz;
            if (raiz->folha)
                raiz = NULL;
            else
            {
                raiz = raiz->C[0];
                registraCopia();
            }
            delete tmp;
        }
        return;
    }
};
#endif //SRC_TRABALHO2_ARVOREB_H
