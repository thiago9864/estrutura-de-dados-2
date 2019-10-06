/**
    Universidade Federal de Juiz de Fora
    QuickSortMediana.h
    Propósito: Implementação do algoritmo Quick sort com a mediana sendo o pivo.

    @author Luan Reis
    @version 1.0 30/08/19
*/

#ifndef QUICKSORTMEDIANA_H
#define QUICKSORTMEDIANA_H

#include <iostream>

using namespace std;

template <class T>
class QuickSortMediana
{
public:
    QuickSortMediana(){};
    ~QuickSortMediana(){};

    void ordenar(T *vet, int inicio, int fim)
    {

        if (inicio < fim)
        {
            int p = particao(vet, inicio, fim);

            ordenar(vet, inicio, p - 1);
            ordenar(vet, p + 1, fim);
        }
    };

    void ordenarInt(T *vet, int inicio, int fim)
    {

        if (inicio < fim)
        {
            calculaMediana3k(vet, fim);
            int p = particaoInt(vet, inicio, fim);

            ordenarInt(vet, inicio, p - 1);
            ordenarInt(vet, p + 1, fim);
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
    int mediana;

    void calculaMediana3k(T *vet, int fim)
    {

        int i1, i2, i3;
        i1 = rand() % (fim + 1);
        i2 = rand() % (fim + 1);
        i3 = rand() % (fim + 1);
        while (i1 < 0 || i1 > fim || i2 < 0 || 12 > fim || i3 < 0 || i3 > fim)
        {
            if (i1 < 0 || i1 > fim)
                i1 = rand();
            if (i2 < 0 || 12 > fim)
                i2 = rand();
            if (i3 < 0 || i3 > fim)
            {
                i3 = rand();
            }
        }

        int aux[3] = {i1, i2, i3};
        int auxiliar;

        for (int k = 0; k < 2; k++)
        {
            if (aux[k] > aux[k + 1])
            {
                auxiliar = aux[k];
                aux[k]=aux[k+1];
                aux[k+1]=aux[k];
            }
            if(aux[k] > aux[k + 2]){

                auxiliar = aux[k];
                aux[k]=aux[k+1];
                aux[k+1]=aux[k];

            }
        }
        mediana=aux[1];
    }

    int particao(T *vet, int inicio, int fim)
    {

        int i = inicio - 1;

        T pivo = vet[mediana];
        for (int j = inicio; j <= fim - 1; j++)
        {
            if (comparador(vet[j], pivo))
            {
                i++;
                troca(vet, i, j);
            }
        }
        troca(vet, i + 1, fim);
        return (i + 1);
    };

    int particaoInt(T *vet, int inicio, int fim)
    {

        int i = inicio - 1;

        T pivo = vet[mediana];
        for (int j = inicio; j <= fim - 1; j++)
        {
            if (comparadorInt(vet[j], pivo))
            {
                i++;
                troca(vet, i, j);
            }
        }
        troca(vet, i + 1, fim);
        return (i + 1);
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
        T aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        num_trocas++;
    };
};

#endif // QUICKSORTMEDIANA_H
