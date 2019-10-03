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

    /**
     * Ordenação para os tipos de dados do dataset
     * @param v Vetor de objetos
     * @param t Tamanho do vetor
     */
    void ordenar(T *v, int n)
    {
        constroiHeap(n, v);
        for (int m = n; m >= 1; --m)
        {
            troca2(v, m);
            peneira(m - 1, v);
        }
    }

    /**
     * Ordenação para inteiros
     * @param v Vetor de inteiros
     * @param t Tamanho do vetor
     */
    void ordenarInt(int *v, int n)
    {
        constroiHeapInt(n, v);
        for (int m = n; m >= 1; --m)
        {
            troca2(v, m);
            peneiraInt(m - 1, v);
        }
    }

    void resetContadores(){
        num_trocas=0;
        num_comparacoes=0;
    }
    long getNumComparacoes(){
        return num_comparacoes;
    }
    long getNumTrocas(){
        return num_trocas;
    }
private:
    long num_comparacoes;
    long num_trocas;

    void constroiHeap(int m, T *vet)
    {

        for (int i = 0; i <= m; i++)
        {
            int f = i + 1;
            while (f > 0 && comparador(vet[f / 2], vet[f]))
            {
                //num_comparacoes++;
                troca(vet, f);
                f /= 2;
            }
        }
        //for (int z=0;z<=m;z++){
        //    cout<<"construindo a arvore"<<vet[z].id<<endl ;
        //}
    }

    void peneira(int m, T *v)
    {
        int p = 0, f = 1;
        T x = v[0];
        while (f <= m)
        {
            if (f <= m && comparador(v[f], v[f + 1]))
                ++f;
            if (x.id >= v[f].id)
                break;
            v[p] = v[f];
            p = f, f = 2 * p;
            num_comparacoes++;
        }
        v[p] = x;
    }

    void constroiHeapInt(int m, int *vet)
    {

        for (int i = 0; i <= m; i++)
        {
            int f = i + 1;
            while (f > 0 && comparadorInt(vet[f / 2], vet[f]))
            {
                //num_comparacoes++;
                troca(vet, f);
                f /= 2;
            }
        }
        //for (int z=0;z<=m;z++){
        //    cout<<"construindo a arvore"<<vet[z].id<<endl ;
        //}
    }

    void peneiraInt(int m, int *v)
    {
        int p = 0, f = 1;
        T x = v[0];
        while (f <= m)
        {
            if (f <= m && comparadorInt(v[f], v[f + 1]))
                ++f;
            if (x >= v[f])
                break;
            v[p] = v[f];
            p = f, f = 2 * p;
            num_comparacoes++;
        }
        v[p] = x;
    }

    bool comparador(T a, T b){
        num_comparacoes++;
        return a.id < b.id;
    }
    bool comparadorInt(int a, int b){
        num_comparacoes++;
        return a < b;
    }

    void troca(T *vet, int f)
    {
        T aux;
        aux = vet[f / 2];
        vet[f / 2] = vet[f];
        vet[f] = aux;
        num_trocas++;
    }

    void troca2(T *vet, int m)
    {
        T aux;
        aux = vet[0];
        vet[0] = vet[m];
        vet[m] = aux;
        num_trocas++;
    }

};
