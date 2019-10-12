/**
    Universidade Federal de Juiz de Fora
    HeapSort.h
    Propósito: Implementação do algoritmo HeapSort.

    @author Luan Reis, Renan Nunes
    @version 2.0 03/10/19
*/

#ifndef HEAPSORT_H
#define HEAPSORT_H

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
        constroiHeap(n,v);
        for (int i = n-1; i > 1; i--)
        {
            constroiHeap(i,v);
            troca2(v,0,i);
        }
    };

    /**
     * Ordenação para inteiros
     * @param v Vetor de inteiros
     * @param t Tamanho do vetor
     */
    void ordenarInt(T *v, int n)
    {
        constroiHeapInt(n,v);
        for (int i = n-1; i > 1; i--)
        {
            constroiHeapInt(i,v);
            troca2(v,0,i);
        }
    };

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

        int tam = m;
        int p = (int) (tam/2) - 1;
        bool existe2 = true;

        while(p > -1)
        {
            T pai = vet[p];
            T filho1 = vet[2*p];
            T filho2 = vet[2*p+1];

            if(2*p+1 >= tam)
            {
                existe2 = false;
            }

            if(comparador(filho1, filho2) && existe2)
            {
                if(comparador(pai, filho2))
                {
                    troca2(vet,p,2*p+1);
                }
            } else
            {
                troca2(vet,p,2*p);
            }
            p--;
        }
        /*
        for (int z=0;z<=m;z++){
            cout<<"construindo a arvore"<<vet[z].id<<endl ;
        }
        */
    }

    void constroiHeapInt(int m, T *vet)
    {

        int tam = m;
        int p = (int) (tam/2) - 1;
        bool existe2 = true;

        while(p > -1)
        {
            int pai = vet[p];
            int filho1 = vet[2*p];
            int filho2 = vet[2*p+1];

            if(2*p+1 >= tam)
            {
                existe2 = false;
            }

            if(comparadorInt(filho1, filho2) && existe2)
            {
                if(comparadorInt(pai, filho2))
                {
                    troca2(vet,p,2*p+1);
                }
            } else
            {
                troca2(vet,p,2*p);
            }
            p--;
        }
        /*
        for (int z=0;z<=m;z++){
            cout<<"construindo a arvore"<<vet[z]<<endl ;
        }
        */
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

    /**
     * Inverte a posição de 2 itens no vetor e atualiza do contador de trocas
     * @param vet vetor que está tendo seus itens invertidos
     * @param i posição do item 1 no vetor
     * @param j posição do item 2 no vetor
     */
    void troca2(T *vet, int i, int j){
        T aux;
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        num_trocas++;
    }

};

#endif // HEAPSORT_H
