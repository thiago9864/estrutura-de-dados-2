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
#include "../Contador.h"

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
        //numCopias = 0;
        //numComparacoes = 0;
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
                Contador::getInstance().registraComparacao();
                chave[i + 1] = chave[i];
                Contador::getInstance().registraCopia();
                i--;
            }

            chave[i + 1] = k;
            Contador::getInstance().registraCopia();
            n = n + 1;
        }
        else
        {

            while (i >= 0 && chave[i].id > k.id)
            {
                i--;
                Contador::getInstance().registraComparacao();
            }

            if (C[i + 1]->n == 2 * t - 1)
            {
                Contador::getInstance().registraComparacao();
                dividefilho(i + 1, C[i + 1]);

                if (chave[i + 1].id < k.id)
                {
                    i++;
                    Contador::getInstance().registraComparacao();
                }
            }
            C[i + 1]->inserenaocheio(k);
        }
    }

    void dividefilho(int i, NoBObjeto *y)
    {

        NoBObjeto *z = new NoBObjeto(y->t, y->folha);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
        {
            z->chave[j] = y->chave[j + t];
            Contador::getInstance().registraCopia();
        }

        if (y->folha == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
        {
            Contador::getInstance().registraComparacao();
            C[j + 1] = C[j];
            Contador::getInstance().registraCopia();
        }

        C[i + 1] = z;
        Contador::getInstance().registraCopia();

        for (int j = n - 1; j >= i; j--)
            for (int j = n - 1; j >= i; j--)
            {
                Contador::getInstance().registraComparacao();
                chave[j + 1] = chave[j];
                Contador::getInstance().registraCopia();
            }

        chave[i] = y->chave[t - 1];
        Contador::getInstance().registraCopia();


        n = n + 1;
    }

    void remove(UserReview k)
    {

        int idx = achachave(k);

        if (idx < n && chave[idx].id == k.id)
        {
            Contador::getInstance().registraComparacao();
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
             {
            chave[i - 1] = chave[i];
            Contador::getInstance().registraComparacao();
        }

        n--;

        return;
    }

    void removenaofolha(int idx)
    {

        UserReview k = chave[idx];

        if (C[idx]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            UserReview pred = getPred(idx);
            chave[idx] = pred;
            C[idx]->remove(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            Contador::getInstance().registraComparacao();
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
        Contador::getInstance().registraCopia();
        while (!cur->folha)
            cur = cur->C[cur->n];

        return cur->chave[cur->n - 1];
    }

    UserReview getSucc(int idx)
    {
        NoBObjeto *cur = C[idx + 1];
        Contador::getInstance().registraCopia();
        while (!cur->folha)
            cur = cur->C[0];

        return cur->chave[0];
    }

    void preenche(int idx)
    {

        if (idx != 0 && C[idx - 1]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            emprestaant(idx);
        }
        else if (idx != n && C[idx + 1]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            emprestaprox(idx);
        }

        else
        {
            Contador::getInstance().registraComparacao();
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
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        for (int i = filho->n - 1; i >= 0; --i){
            filho->chave[i + 1] = filho->chave[i];
            Contador::getInstance().registraCopia();
            Contador::getInstance().registraComparacao();
            }

        if (!filho->folha)
        {
            for (int i = filho->n; i >= 0; --i)
                filho->C[i + 1] = filho->C[i];
        }

        filho->chave[0] = chave[idx - 1];
        Contador::getInstance().registraCopia();

        if (!filho->folha)
            filho->C[0] = irmao->C[irmao->n];

        chave[idx - 1] = irmao->chave[irmao->n - 1];
        Contador::getInstance().registraCopia();

        filho->n += 1;
        irmao->n -= 1;

        return;
    }

    void emprestaprox(int idx)
    {

        NoBObjeto *filho = C[idx];
        NoBObjeto *irmao = C[idx + 1];
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        filho->chave[(filho->n)] = chave[idx];
        Contador::getInstance().registraCopia();

        if (!(filho->folha))
            filho->C[(filho->n) + 1] = irmao->C[0];

        chave[idx] = irmao->chave[0];
        Contador::getInstance().registraCopia();

        for (int i = 1; i < irmao->n; ++i)
           {
            irmao->chave[i - 1] = irmao->chave[i];
            Contador::getInstance().registraCopia();
            Contador::getInstance().registraComparacao();
        }

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
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        filho->chave[t - 1] = chave[idx];
        Contador::getInstance().registraCopia();
        
        for (int i = 0; i < irmao->n; ++i)
            {
            filho->chave[i + t] = irmao->chave[i];
            Contador::getInstance().registraCopia();
        }

        if (!filho->folha)
        {
            for (int i = 0; i <= irmao->n; ++i)
                filho->C[i + t] = irmao->C[i];
        }

        for (int i = idx + 1; i < n; ++i)
            {
            chave[i - 1] = chave[i];
            Contador::getInstance().registraCopia();
        }

        for (int i = idx + 2; i <= n; ++i)
           {
            C[i - 1] = C[i];
            Contador::getInstance().registraCopia();
        }

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

#endif //SRC_TRABALHO2_NoBObjeto_H
