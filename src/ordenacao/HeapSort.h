/**
    Universidade Federal de Juiz de Fora
    HeapSort.h
    Propósito: Implementação do algoritmo HeapSort.

    @author Luan Reis
    @version 1.0 21/08/19
*/

#include <iostream>

using namespace std;

template <class T>
class HeapSort
{
public:
    HeapSort(){};
    ~HeapSort(){};

    void ordenar(T *v, int n)
    {

        constroiHeap(n, v);
        for (int m = n; m >= 1; --m)
        {
            troca2(v, m);
            peneira(m - 1, v);
        }
    }

private:
    void constroiHeap(int m, T *vet)
    {

        for (int i = 0; i <= m; i++)
        {

            int f = i + 1;
            while (f > 0 && vet[f / 2].id < vet[f].id)
            {
                troca(vet, f);
                f /= 2;
            }
        }
        for (int z=0;z<=m;z++){
            cout<<"construindo a arvore"<<vet[z].id<<endl ;
        }
    }

    void peneira(int m, T *v)
    {
        int p = 0, f = 1;
        T x = v[0];
        while (f <= m)
        {
            if (f <= m && v[f].id < v[f + 1].id)
                ++f;
            if (x.id >= v[f].id)
                break;
            v[p] = v[f];
            p = f, f = 2 * p;
        }
        v[p] = x;
    }

    void troca(T *vet, int f)
    {
        T aux;
        aux = vet[f / 2];
        vet[f / 2] = vet[f];
        vet[f] = aux;
    }

    void troca2(T *vet, int m)
    {

        T aux;
        aux = vet[0];
        vet[0] = vet[m];
        vet[m] = aux;
    }

};
