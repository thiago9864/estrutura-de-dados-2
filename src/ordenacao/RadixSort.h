//
// Created by lrpes on 18/09/2019.
//

#ifndef BASE_TRABALHO_RADIXSORT_H
#define BASE_TRABALHO_RADIXSORT_H

#include <iostream>
using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de RadixSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class RadixSort {
public:
    RadixSort(){};
    ~RadixSort(){};

    /**
     * Ordenacao para os tipos de dados do dataset
     * @param vet Vetor de objetos
     * @param n Tamanho do vetor
     */
    void ordenar(T* vet, int n){
        T m = getMax(vet, n);
        for(long long int exp = 1; m.id/exp > 0; exp *= 10){
            countSort(vet, n, exp);
        }
    };

    /**
     * Ordenacao para inteiros
     * @param vet Vetor de inteiros
     * @param n Tamanho do vetor
     */
    void ordenarInt(int* vet, int n){
        int m = getMaxInt(vet, n);
        for(int exp = 1; m/exp > 0; exp *= 10){
            countSortInt(vet, n, exp);
        }
    };

private:

    /**
     * Obtem o maior valor em um vetor
     * @param vet vetor
     * @param n tamanho do vetor
     * @return maior valor
     */
    T getMax(T* vet, int n){
        T mx = vet[0];
        for(int i = 1; i < n; i++){
            if(vet[i].id > mx.id){
                mx = vet[i];
            }
        }
        return mx;
    };

    /**
     * Função que realiza o countsort para o digito atual no exp
     * @param vet vetor a ser ordenado
     * @param n tamanho do vetor
     * @param exp digito atual sendo ordenado
     */
    void countSort(T* vet, int n, int exp){
        T* output = new T[n];
        int *count = new int[10];
        int i=0;
        for(int i=0; i<10; i++){
            count[i] = 0;
        }
        //int i, count[10] = {0};

        for(i = 0; i < n; i++){
            count[(vet[i].id/exp)%10]++;
        }

        for(i = 1; i <10; i++){
            count[i] += count[i - 1];
        }

        for(i = n - 1; i >= 0; i--){
            output[count[(vet[i].id/exp)%10] - 1] = vet[i];
            count[(vet[i].id/exp)%10]--;
        }

        for(i = 0; i < n; i++){
            vet[i] = output[i];
        }

        delete[] output;
    }

    /**
     * Obtem o maior valor em um vetor
     * @param vet vetor
     * @param n tamanho do vetor
     * @return maior valor
     */
    int getMaxInt(int* vet, int n){
        int mx = vet[0];
        for(int i = 1; i < n; i++){
            if(vet[i] > mx){
                mx = vet[i];
            }
        }
        return mx;
    };

    /**
     * Função que realiza o countsort para o digito atual no exp
     * @param vet vetor a ser ordenado
     * @param n tamanho do vetor
     * @param exp digito atual sendo ordenado
     */
    void countSortInt(int* vet, int n, int exp){
        T output[n];
        int i, count[10] = {0};

        for(i = 0; i < n; i++){
            count[(vet[i]/exp)%10]++;
        }

        for(i = 1; i <10; i++){
            count[i] += count[i - 1];
        }

        for(i = n - 1; i >= 0; i--){
            output[count[(vet[i]/exp)%10] - 1] = vet[i];
            count[(vet[i]/exp)%10]--;
        }

        for(i = 0; i < n; i++){
            vet[i] = output[i];
        }
    }
};


#endif //BASE_TRABALHO_RADIXSORT_H
