/**
    Universidade Federal de Juiz de Fora
    SelectionSort.h
    Propósito: Implementação do algoritmo SelectionSort.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <iostream>

using namespace std;

template <class T>
class SelectionSort
{
    public:
        SelectionSort(){};
        ~SelectionSort(){};

        //metodos da classe
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                int menor=i;
                for(int j=i+1; j<tam; j++){
                    if(vetor[j].id < vetor[menor].id){
                        menor = j;
                    }
                }
                troca(vetor, i, menor);
            }
        }
    private:

        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
        }

};

#endif // SELECTIONSORT_H
