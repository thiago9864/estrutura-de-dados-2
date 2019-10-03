/**
    Universidade Federal de Juiz de Fora
    SelectionSort.h
    Propósito: Implementação do algoritmo SelectionSort.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <iostream>

using namespace std;

template <class T>
class InsertionSort
{
    public:
        InsertionSort(){};
        ~InsertionSort(){};

        //metodos da classe
        void ordenar(T* vetor, int start, int finish){
            for(int i=start; i<finish; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=start && vetor[j].id > pivo.id){
                    vetor[j+1] = vetor[j];
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }
    private:
        //
};

#endif // INSERTIONSORT_H
