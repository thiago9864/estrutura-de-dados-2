/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar a arvore B

    @author: Luan Reis Ciribelli
    @version 1.0 27/10/2019



*/

#ifndef SRC_TRABALHO2_ARVOREB_H
#define SRC_TRABALHO2_ARVOREB_H

#include <iostream>
#include "BaseArvores.h"
#include "NoB.h"

class ArvoreB : public BaseArvores
{
    NoB *raiz;
    int t;

public:
    ArvoreB(int _t)
    {
        raiz = NULL;
        t = _t;
    }

    void percorre()
    {
        if (raiz != NULL)
            raiz->percorre();
    }

    NoB *procura(int k)
    {
        return (raiz == NULL) ? NULL : raiz->procura(k);
    }

    void insert(int k);

    void remove(int k);
};

void ArvoreB::insert(int k)
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

            s->dividefilho(0, raiz);

            int i = 0;
            if (s->chave[0] < k)
                i++;
            s->C[i]->inserenaocheio(k);

            raiz = s;
        }
        else
            raiz->inserenaocheio(k);
    }
}

void ArvoreB::remove(int k)
{
    if (!raiz)
    {
        cout << "A arvore está vazia\n";
        return;
    }

    raiz->remove(k);

    if (raiz->n == 0)
    {
        NoB *tmp = raiz;
        if (raiz->folha)
            raiz = NULL;
        else
            raiz = raiz->C[0];

        delete tmp;
    }
    return;
}

#endif //SRC_TRABALHO2_ARVOREB_H
