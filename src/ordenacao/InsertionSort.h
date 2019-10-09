/**
    Universidade Federal de Juiz de Fora
    InsertionSort.h
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

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vetor Vetor de objetos
         * @param tam Tamanho do vetor
         */
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

        /**
         * Ordenação para os tipos de dados do dataset otimizado para o QuickSortInsertion
         * @param vetor Vetor de objetos
         * @param start Posicao inicial do vetor
         * @param finish Posição final do vetor
         */
        void ordenarQuick(T* vetor, int start, int finish){
            for(int i=start; i<finish; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=start && comparador(vetor[j], pivo)){
                    vetor[j+1] = vetor[j];
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        /**
         * Ordenação para inteiros
         * @param vetor Vetor de inteiros
         * @param tam Tamanho do vetor
         */
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

        /**
         * Ordenação para os tipos de dados do dataset otimizado para o QuickSortInsertion
         * @param vetor Vetor de objetos
         * @param start Posicao inicial do vetor
         * @param finish Posição final do vetor
         */
        void ordenarIntQuick(T* vetor, int start, int finish){
            for(int i=start; i<finish; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=start && comparadorInt(vetor[j], pivo)){
                    vetor[j+1] = vetor[j];
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        void resetContadores(){
            num_trocas=0;
            num_comparacoes=0;
        }
        long long int getNumComparacoes(){
            return num_comparacoes;
        }
        long long int getNumTrocas(){
            return num_trocas;
        }
    private:
        long long int num_comparacoes;
        long long int num_trocas;
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
