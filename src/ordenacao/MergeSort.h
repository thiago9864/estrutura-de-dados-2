/**
    Universidade Federal de Juiz de Fora
    MergeSort.h
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

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vet Vetor de objetos
         * @param inicio Posição de inicio do vetor
         * @param fim Posição final do vetor
         */
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

        /**
         * Ordenação para inteiros
         * @param vet Vetor de objetos
         * @param inicio Posição de inicio do vetor
         * @param fim Posição final do vetor
         */
        void ordenarInt(int *vet, int inicio, int fim)
        {
            int meio;
            if (inicio < fim)
            {
                meio = (inicio + fim) / 2;
                ordenarInt(vet, inicio, meio);
                ordenarInt(vet, meio + 1, fim);
                intercalaInt(vet, inicio, meio, fim);
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

        void intercala(T* vet,int inicio, int meio,int fim)
        {

            T auxiliar[fim+1];
            int inicioVetor2, inicioVetor1, posicaoLivre;
            inicioVetor1 = inicio;
            inicioVetor2 = meio + 1;
            posicaoLivre = inicio;

            while (inicioVetor1 <= meio && inicioVetor2 <= fim)
            {
                if (comparador(vet[inicioVetor1], vet[inicioVetor2]))
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor1];
                    num_trocas++;
                    inicioVetor1++;
                }
                else
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor2];
                    num_trocas++;
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

        void intercalaInt(int* vet,int inicio, int meio,int fim)
        {

            T auxiliar[fim+1];
            int inicioVetor2, inicioVetor1, posicaoLivre;
            inicioVetor1 = inicio;
            inicioVetor2 = meio + 1;
            posicaoLivre = inicio;

            while (inicioVetor1 <= meio && inicioVetor2 <= fim)
            {
                if (comparadorInt(vet[inicioVetor1], vet[inicioVetor2]))
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor1];
                    num_trocas++;
                    inicioVetor1++;
                }
                else
                {
                    auxiliar[posicaoLivre] = vet[inicioVetor2];
                    num_trocas++;
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

        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id <= b.id;
        }
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a <= b;
        }

};

#endif // MERGESORT_H
