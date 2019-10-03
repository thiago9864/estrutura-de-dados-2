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

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vetor Vetor de objetos
         * @param tam Tamanho do vetor
         */
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                bool trocou=false;
                for(int j=0; j<tam-1-i; j++){
                    if(comparador(vetor[j], vetor[j+1])){
                        troca(vetor, j, j+1);
                        trocou=true;
                    }
                }
                if(trocou==false){
                    break;
                }
            }
        }

        /**
         * Ordenação para inteiros
         * @param vetor Vetor de inteiros
         * @param tam Tamanho do vetor
         */
        void ordenarInt(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                bool trocou=false;
                for(int j=0; j<tam-1-i; j++){
                    if(comparadorInt(vetor[j], vetor[j+1])){
                        troca(vetor, j, j+1);
                        trocou=true;
                    }
                }
                if(trocou==false){
                    break;
                }
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

        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
        }

};

#endif // BUBBLESORT_H
