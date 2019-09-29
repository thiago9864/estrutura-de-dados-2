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

        void ordenarInt(int* vet,int inicio, int fim){
            
            if (inicio < fim)
            {
                int p = particaoInt(vet, inicio, fim);

                ordenarInt(vet, inicio, p-1);
                ordenarInt(vet, p + 1,fim);
            }

        };

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

        int particao(T* vet,int inicio, int fim){

            int i = inicio - 1;
            
            int pivo = vet[fim];
            for(int j = inicio; j <= fim - 1; j++){
                if(comparador(vet[j], pivo))
                {
                    i++;
                    troca(vet,i,j);
                }
            }
            troca(vet,i+1,fim);
            return (i+1);
        };

        int particaoInt(int* vet,int inicio, int fim){

            int i = inicio - 1;
            
            int pivo = vet[fim];
            for(int j = inicio; j <= fim - 1; j++){
                if(comparadorInt(vet[j], pivo))
                {
                    i++;
                    troca(vet,i,j);
                }
            }
            troca(vet,i+1,fim);
            return (i+1);
        };

        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id <= b.id;
        }
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a <= b;
        }
        void troca(T* vet,int i,int j){
            num_trocas++;
            T aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        };

};

#endif // QUICKSORT_H