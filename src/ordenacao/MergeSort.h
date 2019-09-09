/**
    Universidade Federal de Juiz de Fora
    BubbleSort.h
    Propósito: Implementação do algoritmo MergeSort.

    @author Luan Reis
    @version 1.0 21/08/19
*/

#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>

using namespace std;

template <class T>
class MergeSort
{
    public:
        MergeSort(){};
        ~MergeSort(){};

        void ordenar(T *vet, int inicio, int fim)
        {
            int meio;
            if (inicio < fim)
            {
                meio = (inicio + fim) / 2;
                ordenar(vet, inicio, meio);
                ordenar(vet, meio + 1, fim);
                intercala(vet, inicio, meio, fim);
            }
        }

    private:
        void intercala(T* vet,int inicio, int meio,int fim)
        {

            T auxiliar[fim+1];
            int inicioVetor2, inicioVetor1, posicaoLivre;
            inicioVetor1 = inicio;
            inicioVetor2 = meio + 1;
            posicaoLivre = inicio;

            while (inicioVetor1 <= meio && inicioVetor2 <= fim)
            {
                if (vet[inicioVetor1].id <= vet[inicioVetor2].id)
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor1];
                    inicioVetor1++;
                }
                else
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor2];
                    inicioVetor2++;
                }
                posicaoLivre++;
            }

            for (int i = inicioVetor1; i <= meio; i++)
            {
                auxiliar[posicaoLivre] = vet[i];
                posicaoLivre++;
            }
            for (int i = inicioVetor2; i <= fim; i++)
            {
                auxiliar[posicaoLivre] = vet[i];
                posicaoLivre++;
            }

            for (int i = inicio; i <= fim; ++i)
            {
                vet[i] = auxiliar[i];
            }
        }

        
};

#endif // MERGESORT_H
