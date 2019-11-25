/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar o NoB usando Objetos como chave

    @author: Luan Reis Ciribelli
    @version 1.0 27/10/2019



*/

#ifndef SRC_TRABALHO2_NoBObjeto_H
#define SRC_TRABALHO2_NoBObjeto_H

#include "../UserReview.h"

template <class T>
class NoBObjeto
{
private:
    UserReview *chave;
    int t;
    NoBObjeto **C;
    int n;
    bool folha;

public:
    NoBObjeto(int t1, bool folha1)
    {
        t = t1;
        folha = folha1;

        chave = new UserReview[2 * t - 1];
        C = new NoBObjeto *[2 * t];

        n = 0;
    }

    NoBObjeto *procura(UserReview k)
    {
        int i = 0;
        while (i < n && k.id > chave[i].id)
            i++;

        if (chave[i].id == k.id)
            return this;

        if (folha == true)
            return NULL;

        return C[i]->procura(k);
    }

    int achachave(UserReview k)
    {
        int idx = 0;
        while (idx < n && chave[idx].id < k.id)
            ++idx;
        return idx;
    }

    void inserenaocheio(UserReview k)
    {
        int i = n - 1;

        if (folha == true)
        {

            while (i >= 0 && chave[i].id > k.id)
            {
                chave[i + 1] = chave[i];
                i--;
            }

            chave[i + 1] = k;
            n = n + 1;
        }
        else
        {

            while (i >= 0 && chave[i].id > k.id)
                i--;

            if (C[i + 1]->n == 2 * t - 1)
            {
                dividefilho(i + 1, C[i + 1]);

                if (chave[i + 1].id < k.id)
                    i++;
            }
            C[i + 1]->inserenaocheio(k);
        }
    }

    void dividefilho(int i, NoBObjeto *y)
    {

        NoBObjeto *z = new NoBObjeto(y->t, y->folha);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->chave[j] = y->chave[j + t];

        if (y->folha == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            chave[j + 1] = chave[j];

        chave[i] = y->chave[t - 1];

        n = n + 1;
    }

    void remove(UserReview k)
    {

        int idx = achachave(k);

        if (idx < n && chave[idx].id == k.id)
        {

            if (folha)
                removefolha(idx);
            else
                removenaofolha(idx);
        }
        else
        {

            if (folha)
            {
                cout << "A chave " << k.id << " não existe na arvore\n";
                return;
            }

            bool flag = ((idx == n) ? true : false);

            if (C[idx]->n < t)
                preenche(idx);

            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
        return;
    }

    void removefolha(int idx)
    {

        for (int i = idx + 1; i < n; ++i)
            chave[i - 1] = chave[i];

        n--;

        return;
    }

    void removenaofolha(int idx)
    {

        UserReview k = chave[idx];

        if (C[idx]->n >= t)
        {
            UserReview pred = getPred(idx);
            chave[idx] = pred;
            C[idx]->remove(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            UserReview succ = getSucc(idx);
            chave[idx] = succ;
            C[idx + 1]->remove(succ);
        }

        else
        {
            juntar(idx);
            C[idx]->remove(k);
        }
        return;
    }

    UserReview getPred(int idx)
    {

        NoBObjeto *cur = C[idx];
        while (!cur->folha)
            cur = cur->C[cur->n];

        return cur->chave[cur->n - 1];
    }

    UserReview getSucc(int idx)
    {
        NoBObjeto *cur = C[idx + 1];
        while (!cur->folha)
            cur = cur->C[0];

        return cur->chave[0];
    }

    void preenche(int idx)
    {

        if (idx != 0 && C[idx - 1]->n >= t)
            emprestaant(idx);

        else if (idx != n && C[idx + 1]->n >= t)
            emprestaprox(idx);

        else
        {
            if (idx != n)
                juntar(idx);
            else
                juntar(idx - 1);
        }
        return;
    }

    void emprestaant(int idx)
    {

        NoBObjeto *filho = C[idx];
        NoBObjeto *irmao = C[idx - 1];

        for (int i = filho->n - 1; i >= 0; --i)
            filho->chave[i + 1] = filho->chave[i];

        if (!filho->folha)
        {
            for (int i = filho->n; i >= 0; --i)
                filho->C[i + 1] = filho->C[i];
        }

        filho->chave[0] = chave[idx - 1];

        if (!filho->folha)
            filho->C[0] = irmao->C[irmao->n];

        chave[idx - 1] = irmao->chave[irmao->n - 1];

        filho->n += 1;
        irmao->n -= 1;

        return;
    }

    void emprestaprox(int idx)
    {

        NoBObjeto *filho = C[idx];
        NoBObjeto *irmao = C[idx + 1];

        filho->chave[(filho->n)] = chave[idx];

        if (!(filho->folha))
            filho->C[(filho->n) + 1] = irmao->C[0];

        chave[idx] = irmao->chave[0];

        for (int i = 1; i < irmao->n; ++i)
            irmao->chave[i - 1] = irmao->chave[i];

        if (!irmao->folha)
        {
            for (int i = 1; i <= irmao->n; ++i)
                irmao->C[i - 1] = irmao->C[i];
        }

        filho->n += 1;
        irmao->n -= 1;

        return;
    }

    void juntar(int idx)
    {
        NoBObjeto *filho = C[idx];
        NoBObjeto *irmao = C[idx + 1];

        filho->chave[t - 1] = chave[idx];

        for (int i = 0; i < irmao->n; ++i)
            filho->chave[i + t] = irmao->chave[i];

        if (!filho->folha)
        {
            for (int i = 0; i <= irmao->n; ++i)
                filho->C[i + t] = irmao->C[i];
        }

        for (int i = idx + 1; i < n; ++i)
            chave[i - 1] = chave[i];

        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];

        filho->n += irmao->n + 1;
        n--;

        delete (irmao);
        return;
    }

    void percorre()
    {

        int i;
        for (i = 0; i < n; i++)
        {

            if (folha == false)
                C[i]->percorre();
            cout << " " << chave[i].id;
        }

        if (folha == false)
            C[i]->percorre();
    }

    friend class ArvoreBObjeto;
};

#endif //SRC_TRABALHO2_NoBObjetos_H
