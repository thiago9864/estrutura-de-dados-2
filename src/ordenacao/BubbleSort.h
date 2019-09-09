/**
    Universidade Federal de Juiz de Fora
    BubbleSort.h
    Propósito: Implementação do algoritmo BubbleSort.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <iostream>

using namespace std;

template <class T>
class BubbleSort
{
    public:
        BubbleSort(){};
        ~BubbleSort(){};

        //metodos da classe
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                for(int j=0; j<tam-1; j++){
                    if(vetor[j].id > vetor[j+1].id){
                        troca(vetor, j, j+1);
                    }
                }
            }
        }
        void ordenar_melhorado(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                bool trocou=false;
                for(int j=0; j<tam-1-i; j++){
                    if(vetor[j].id > vetor[j+1].id){
                        troca(vetor, j, j+1);
                        trocou=true;
                    }
                }
                if(trocou==false){
                    break;
                }
            }
        }
    private:

        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
        }

};

#endif // BUBBLESORT_H
