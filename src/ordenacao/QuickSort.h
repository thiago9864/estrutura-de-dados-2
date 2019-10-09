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

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vet Vetor de objetos
         * @param inicio Posição de inicio do vetor
         * @param fim Posição final do vetor
         */
        void ordenar(T* vet,long long int inicio, long long int fim){

            /*profundidade++;
            if(profundidade%100==0 || profundidade%100==1){
                cout << "profundidade -> " << profundidade << endl;
            }*/
            if (inicio < fim)
            {
                int p = particao(vet,inicio,fim);

                /*if(profundidade%100==0 || profundidade%100==1){
                    cout << " inicio: " << inicio << ", fim: " << fim << " p: " << p << endl;
                }*/

                ordenar(vet, inicio, p-1);
                ordenar(vet, p + 1,fim);
            }/*
            profundidade--;
            if(profundidade%100==0){
                cout << "profundidade <- " << profundidade << endl;
            }*/

        };

        /**
         * Ordenação para inteiros
         * @param vet Vetor de inteiros
         * @param inicio Posição de inicio do vetor
         * @param fim Posição final do vetor
         */
        void ordenarInt(int* vet, long long int inicio, long long int fim){

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
        long long int num_comparacoes;
        long long int num_trocas;
        //long long int profundidade=0;

        int particao(T* vet, long long int inicio, long long int fim){

            int i = inicio - 1;

            /*if(vet==0x0){
                cout << "profundidade: " << profundidade << endl;
                cout << "inicio: " << inicio << endl;
                cout << "fim: " << fim << endl;
                exit(1);
            }*/

            T pivo = vet[fim];
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

        int particaoInt(int* vet,long long int inicio, long long int fim){

            long long int i = inicio - 1;

            long long int pivo = vet[fim];
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
        bool comparadorInt(long long int a, long long int b){
            num_comparacoes++;
            return a <= b;
        }
        void troca(T* vet,long long int i,long long int j){
            num_trocas++;
            T aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        };

};

#endif // QUICKSORT_H
