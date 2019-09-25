//
// Created by lrpes on 18/09/2019.
//

#ifndef BASE_TRABALHO_QUICKSORTINSERTION_H
#define BASE_TRABALHO_QUICKSORTINSERTION_H

#include <iostream>
#include "InsertionSort.h"


template <class T>
class QuickSortInsertion {

public:
    QuickSortInsertion(){
        this->inSorter = new InsertionSort<T>();
    };
    ~QuickSortInsertion();

    void ordenar(T* vet,int inicio, int fim, int m){

        if(inicio - fim <= m){
        inSorter.ordenar(vet, inicio, fim);
        }
        if (inicio < fim)
        {
            int p = particao(vet,inicio,fim);

            ordenar(vet, inicio, p-1);
            ordenar(vet, p + 1,fim);
        }

    };

private:

    InsertionSort<T> inSorter;
    int particao(T* vet,int inicio, int fim){

        int i = inicio - 1;

        int pivo = vet[fim].id;
        for(int j = inicio; j <= fim - 1; j++){
            if(vet[j].id <= pivo)
            {
                i++;
                troca(vet,i,j);
            }
        }
        troca(vet,i+1,fim);
        return (i+1);
    };

    void troca(T* vet,int i,int j){
        T aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
    };

};


#endif //BASE_TRABALHO_QUICKSORTINSERTION_H
