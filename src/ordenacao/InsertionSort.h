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
        void ordenar(T* vetor, int tam){
            num_comparacoes=0;
            num_trocas=0;
            for(int i=0; i<tam; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=0 && vetor[j].id > pivo.id){
                    num_comparacoes++;
                    vetor[j+1] = vetor[j];
                    num_trocas++;
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        int getNumComparacoes(){
            return num_comparacoes;
        }
        int getNumTrocas(){
            return num_trocas;
        }
    private:
        int num_comparacoes;
        int num_trocas;
};

#endif // INSERTIONSORT_H
