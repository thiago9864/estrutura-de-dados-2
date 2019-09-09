/**
    Universidade Federal de Juiz de Fora
    QuickSort.h
    Propósito: Implementação do algoritmo QuickSort.

    @author Renan Nunes
    @version 2.0 27/08/19
*/

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>

using namespace std;

template <class T>
class QuickSort
{
    public:
        QuickSort(){};
        ~QuickSort(){};

        void ordenar(T* vet,int inicio, int fim){

            if (inicio < fim)
            {
                int p = particao(vet,inicio,fim);

                ordenar(vet, inicio, p-1);
                ordenar(vet, p + 1,fim);
            }

        };

    private:

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

#endif // QUICKSORT_H