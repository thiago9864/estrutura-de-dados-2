/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar o NoB usando inteiros como chave

    @author: Luan Reis Ciribelli
    @version 1.0 27/10/2019



*/

#ifndef SRC_TRABALHO2_NoB_H
#define SRC_TRABALHO2_No_H

class NoB
{
private:
    int *chave;
    int t;
    NoB **C;
    int n;
    bool folha;

public:
    NoB(int t1, bool folha1)
    {
        t = t1;
        folha = folha1;

        chave = new int[2 * t - 1];
        C = new NoB *[2 * t];

        n = 0;
    }

    NoB *procura(int k)
    {
        int i = 0;
        while (i < n && k > chave[i])
            i++;

        if (chave[i] == k)
            return this;

        if (folha == true)
            return NULL;

        return C[i]->procura(k);
    }

    int achachave(int k)
    {
        int idx = 0;
        while (idx < n && chave[idx] < k)
            ++idx;
        return idx;
    }

    void inserenaocheio(int k)
    {
        int i = n - 1;

        if (folha == true)
        {

            while (i >= 0 && chave[i] > k)
            {
                chave[i + 1] = chave[i];
                i--;
            }

            chave[i + 1] = k;
            n = n + 1;
        }
        else
        {

            while (i >= 0 && chave[i] > k)
                i--;

            if (C[i + 1]->n == 2 * t - 1)
            {
                dividefilho(i + 1, C[i + 1]);

                if (chave[i + 1] < k)
                    i++;
            }
            C[i + 1]->inserenaocheio(k);
        }
    }

    void dividefilho(int i, NoB *y)
    {

        NoB *z = new NoB(y->t, y->folha);
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

    void remove(int k)
    {

        int idx = achachave(k);

        if (idx < n && chave[idx] == k)
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
                cout << "A chave " << k << " não existe na arvore\n";
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

        int k = chave[idx];

        if (C[idx]->n >= t)
        {
            int pred = getPred(idx);
            chave[idx] = pred;
            C[idx]->remove(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            int succ = getSucc(idx);
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

    int getPred(int idx)
    {

        NoB *cur = C[idx];
        while (!cur->folha)
            cur = cur->C[cur->n];

        return cur->chave[cur->n - 1];
    }

    int getSucc(int idx)
    {
        NoB *cur = C[idx + 1];
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

        NoB *filho = C[idx];
        NoB *irmao = C[idx - 1];

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

        NoB *filho = C[idx];
        NoB *irmao = C[idx + 1];

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
        NoB *filho = C[idx];
        NoB *irmao = C[idx + 1];

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
            cout << " " << chave[i];
        }

        if (folha == false)
            C[i]->percorre();
    }

    friend class ArvoreB;
};

#endif //SRC_TRABALHO2_NoB_H