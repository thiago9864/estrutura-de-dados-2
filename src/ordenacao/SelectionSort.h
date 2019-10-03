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

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vetor Vetor de objetos
         * @param tam Tamanho do vetor
         */
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                int menor=i;
                for(int j=i+1; j<tam; j++){
                    num_comparacoes++;
                    if(comparador(vetor[j], vetor[menor])){
                        menor = j;
                    }
                }
                troca(vetor, i, menor);
            }
        }

        /**
         * Ordenação para inteiros
         * @param vetor Vetor de inteiros
         * @param tam Tamanho do vetor
         */
        void ordenarInt(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                int menor=i;
                for(int j=i+1; j<tam; j++){
                    if(comparadorInt(vetor[j], vetor[menor])){
                        menor = j;
                    }
                }
                troca(vetor, i, menor);
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
            return a.id < b.id;
        }
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a < b;
        }

        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
            num_trocas++;
        }

};

#endif // SELECTIONSORT_H
