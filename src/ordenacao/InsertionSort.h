/**
    Universidade Federal de Juiz de Fora
    SelectionSort.h
    Propósito: Implementação do algoritmo SelectionSort.

    @author Thiago Almeida
    @version 1.1 26/09/19
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

        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=0 && comparador(vetor[j], pivo)){
                    troca(vetor, j+1, j);
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        void ordenarInt(T* vetor, int tam){
            tamanho=tam;
            for(int i=0; i<tam; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=0 && comparadorInt(vetor[j], pivo)){
                    troca(vetor, j+1, j);
                    j-=1;
                }
                vetor[j+1] = pivo;
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
        int tamanho;

        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id > b.id;
        }
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a > b;
        }
        void troca(T* vetor, int a, int b){
            num_trocas++;
            vetor[a] = vetor[b];
        }
};

#endif // INSERTIONSORT_H
