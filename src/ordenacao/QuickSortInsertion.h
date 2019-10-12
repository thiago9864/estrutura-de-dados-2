//
// Created by lrpes on 18/09/2019.
//

#ifndef BASE_TRABALHO_QUICKSORTINSERTION_H
#define BASE_TRABALHO_QUICKSORTINSERTION_H

#include <iostream>
#include "InsertionSort.h"


template <class T>
class QuickSortInsertion {

public:
    QuickSortInsertion(){
        this->inSorter = new InsertionSort<T>();
    };
    ~QuickSortInsertion(){
        delete this->inSorter;
    }

    void ordenar(T* vet,int inicio, int fim, int m){

        if(fim - inicio <= m){
            inSorter->ordenarQuick(vet, inicio, fim);
        }
        if (inicio < fim)
        {
            int p = particao(vet,inicio,fim);

            this->ordenar(vet, inicio, p-1, m);
            this->ordenar(vet, p + 1,fim, m);
        }

    };

    void ordenarInt(T* vet,int inicio, int fim, int m){

        if(fim - inicio <= m){
            inSorter->ordenarIntQuick(vet, inicio, fim);
        }
        if (inicio < fim)
        {
            int p = particaoInt(vet,inicio,fim);

            this->ordenarInt(vet, inicio, p-1, m);
            this->ordenarInt(vet, p + 1,fim, m);
        }

    };

    /**
     * Reseta os contadores para os estado que estavam no momento de criação do objeto
     */
    void resetContadores(){
        num_trocas=0;
        num_comparacoes=0;
    }

    /**
     * Retorna o numero de comparações contabilizado pelo contador
     * @return numero de comparações feitas desde a ultima inicialização dos contadores
     */
    long getNumComparacoes(){
        return num_comparacoes;
    }

    /**
     * Retorna o numero de trocas contabilizado pelo contador
     * @return numero de trocas feitas desde a ultima inicialização dos contadores
     */
    long getNumTrocas(){
        return num_trocas;
    }

private:
    long num_comparacoes; // Contador de comparações
    long num_trocas; // Contador de trocas

    InsertionSort<T> *inSorter;

    int particao(T* vet,int inicio, int fim){

        int i = inicio - 1;

        T pivo = vet[fim];
        for(int j = inicio; j <= fim - 1; j++){
            if(comparador(vet[j],pivo))
            {
                i++;
                troca(vet,i,j);
            }
        }
        troca(vet,i+1,fim);
        return (i+1);
    };

    int particaoInt(T* vet,int inicio, int fim){

        int i = inicio - 1;

        int pivo = vet[fim];
        for(int j = inicio; j <= fim - 1; j++){
            if(comparadorInt(vet[j],pivo))
            {
                i++;
                troca(vet,i,j);
            }
        }
        troca(vet,i+1,fim);
        return (i+1);
    };

    /**
     * Recebe dois parametros, diz de a.id <= b.id e atualiza o contador
     * @param a item 1 da comparação
     * @param b item 2 da comparação
     * @return booleano indicando se a.id <= b.id
     */
    bool comparador(T a, T b){
        num_comparacoes++;
        return a.id <= b.id;
    }

    /**
     * Recebe dois parametros, diz de a <= b e atualiza o contador
     * @param a item 1 da comparação
     * @param b item 2 da comparação
     * @return booleano indicando se a <= b
     */
    bool comparadorInt(int a, int b){
        num_comparacoes++;
        return a <= b;
    }

    /**
     * Inverte a posição de 2 itens no vetor
     * @param vet vetor que está tendo seus itens invertidos
     * @param i posição do item 1 no vetor
     * @param j posição do item 2 no vetor
     */
    void troca(T* vet,int i,int j){
        T aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        num_trocas++;
    };

};


#endif //BASE_TRABALHO_QUICKSORTINSERTION_H
