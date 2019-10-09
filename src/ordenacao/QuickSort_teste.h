/**
    Universidade Federal de Juiz de Fora
    QuickSort.h
    Propósito: Implementação do algoritmo QuickSort.

    @author Thiago Almeida
    @version 3.0 06/10/19
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
        * @param tam Tamanho do vetor
        */
        void ordenar(T *vet, int tam){
            auxOrdenar(vet, 0, tam-1);
        }

        /**
        * Ordenação para os tipos de dados numericos
        * @param vet Vetor de inteiros
        * @param tam Tamanho do vetor
        */
        void ordenarInt(T *vet, int tam){
            auxOrdenarInt(vet, 0, tam-1);
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

        void auxOrdenar(T *vet, int inicio, int fim){
            //condições de parada
            if(fim-inicio==1){
                //o vetor tem duas posições - ordena de maneira trivial
                num_comparacoes++;
                if(vet[fim].id < vet[inicio].id){
                    //troca ordem
                    num_trocas++;
                    T aux = vet[fim];
                    vet[fim] = vet[inicio];
                    vet[inicio] = aux;
                }
                return;
            } else if(fim-inicio<1){
                //só tem um ou nenhum elemento e está ordenado
                return;
            }

            //particionamento
            int p = fim;
            int i=inicio;
            int m=0;
            for(int j=inicio; j<fim;j++){
                num_comparacoes++;
                if(vet[j].id < vet[p].id){
                    num_trocas++;
                    if(i>=50000 || i < 0){
                        cout << "saiu da faixa" << endl;
                        exit(1);
                    }
                    if(vet == nullptr){
                        cout << "vet nulo" << endl;
                        exit(1);
                    }
                    T aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = aux;
                    i++;
                }
            }
            num_comparacoes++;
            if(vet[p].id < vet[i].id){
                //reposiciona o pivo
                num_trocas++;
                T aux = vet[i];
                vet[i] = vet[p];
                vet[p] = aux;
                i++;
                m = i;
            } else {
                //mantem o pivo
                m = p;
            }

            //chama recursoes
            auxOrdenar(vet, inicio, m-1);
            auxOrdenar(vet, m, fim);
        }

        void auxOrdenarInt(T *vet, int inicio, int fim){
            //condições de parada
            if(fim-inicio==1){
                //o vetor tem duas posições - ordena de maneira trivial
                num_comparacoes++;
                if(vet[fim] < vet[inicio]){
                    //troca ordem
                    num_trocas++;
                    T aux = vet[fim];
                    vet[fim] = vet[inicio];
                    vet[inicio] = aux;
                }
                return;
            } else if(fim-inicio<1){
                //só tem um ou nenhum elemento e está ordenado
                return;
            }

            //particionamento
            int p = fim;
            int i=inicio;
            int m=0;
            for(int j=inicio; j<fim;j++){
                num_comparacoes++;
                if(vet[j] < vet[p]){
                    num_trocas++;
                    T aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = aux;
                    i++;
                }
            }
            num_comparacoes++;
            if(vet[p] < vet[i]){
                //reposiciona o pivo
                num_trocas++;
                T aux = vet[i];
                vet[i] = vet[p];
                vet[p] = aux;
                i++;
                m = i;
            } else {
                //mantem o pivo
                m = p;
            }

            //chama recursoes
            auxOrdenarInt(vet, inicio, m-1);
            auxOrdenarInt(vet, m, fim);
        }

};

#endif // QUICKSORT_H
