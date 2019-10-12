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

        /**
         * Recebe dois parametros, diz de a.id > b.id e contabiliza a comparação
         * @param a item 1 da comparação
         * @param b item 2 da comparação
         * @return booleano indicando se a.id > b.id
         */
        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id < b.id;
        }

        /**
         * Recebe dois parametros, diz de a > b e contabiliza a comparação
         * @param a item 1 da comparação
         * @param b item 2 da comparação
         * @return booleano indicando se a > b
         */
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a < b;
        }

        /**
         * Inverte a posição de 2 itens no vetor
         * @param vetor vetor que está tendo seus itens invertidos
         * @param p1 posição do item 1 no vetor
         * @param p2 posição do item 2 no vetor
         */
        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
            num_trocas++;
        }

};

#endif // SELECTIONSORT_H
