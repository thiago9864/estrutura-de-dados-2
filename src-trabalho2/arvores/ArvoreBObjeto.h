/**
    Universidade Federal de Juiz de Fora
    ArvoreBObjeto.h
    Propósito: Classe para implementar a arvore B usando o No objetos

    @author: Luan Reis Ciribelli
    @version 1.0 27/10/2019



*/

#ifndef SRC_TRABALHO2_ARVOREBObjeto_H
#define SRC_TRABALHO2_ARVOREBObjeto_H

#include <iostream>
#include "BaseArvores.h"
#include "NoBObjeto.h"

template <class T>
class ArvoreBObjeto : public BaseArvores
{
    NoBObjeto<UserReview> *raiz;
    int t;

public:
    ArvoreBObjeto(int _t)
    {
        raiz = NULL;
        t = _t;
    }

    void percorre()
    {
        if (raiz != NULL)
            raiz->percorre();
    }

    NoBObjeto<UserReview> *procura(int k)
    {
        return (raiz == NULL) ? NULL : raiz->procura(k);
    }

    void insert(int k);

    void remove(int k);
};

void ArvoreBObjetos::insert(int k)
{

    if (raiz == NULL)
    {

        raiz = new NoBObjeto<UserReview>(t, true);
        raiz->chave[0] = k;
        raiz->n = 1;
    }
    else
    {
        if (raiz->n == 2 * t - 1)
        {
            NoBObjeto<UserReview> *s = new NoBObjeto<UserReview>(t, false);

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

void ArvoreBObjetos::remove(int k)
{
    if (!raiz)
    {
        cout << "A arvore está vazia\n";
        return;
    }

    raiz->remove(k);

    if (raiz->n == 0)
    {
        NoBObjeto<UserReview> *tmp = raiz;
        if (raiz->folha)
            raiz = NULL;
        else
            raiz = raiz->C[0];

        delete tmp;
    }
    return;
}

#endif //SRC_TRABALHO2_ARVOREBObjetos_H
