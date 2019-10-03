//
// Created by lrpes on 18/09/2019.
//

#ifndef BASE_TRABALHO_RADIXSORT_H
#define BASE_TRABALHO_RADIXSORT_H

#include <iostream>
using namespace std;

template <class T>
class RadixSort {
public:
    RadixSort(){};
    ~RadixSort(){};

    void ordenar(T* vet, int n){
        T m = getMax(vet, n);
        for(int exp = 1; m.id/exp > 0; exp *= 10){
            countSort(vet, n, exp);
        }
    };

    void print(T* vet, int n){
        for(int i = 0; i < n; i++){
            cout << vet[i].id << " ";
        }
    }
private:

    T getMax(T* vet, int n){
        T mx = vet[0];
        for(int i = 1; i < n; i++){
            if(vet[i].id > mx.id){
                mx = vet[i];
            }
        }
        return mx;
    };

    void countSort(T* vet, int n, int exp){
        T output[n];
        int i, count[10] = {0};

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
    }

};


#endif //BASE_TRABALHO_RADIXSORT_H
