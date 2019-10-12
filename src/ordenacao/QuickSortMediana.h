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
#include "../LeitorBase.h"

using namespace std;

template <class T>
class QuickSortMediana
{
public:
    QuickSortMediana(){};
    ~QuickSortMediana(){};

    void ordenar(T* vet, int k, int inicio, int fim)
    {
        this.k=k;
        LeitorBase a=new LeitorBase;
        a.gerarSemente();
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
    int k;
    LeitorBase a;

    void calculaMedianak(T *vet, int fim)
    {
        if(k==3) {
            int i1, i2, i3;
            i1 = a.getRand(fim+1);
            i2 = a.getRand(fim+1);
            i3 = a.getRand(fim+1);

            T aux[3] = {vet[i1], vet[i2], vet[i3]};
            T auxiliar;

            for (int k = 0; k < 2; k++) {
                if (aux[k].id > aux[k + 1].id) {
                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];
                }
                if (aux[k].id > aux[k + 2].id) {

                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];

                }
            }
            mediana = aux[1];
        }
        else {if(k==5){
            int i1, i2, i3;
            i1 = a.getRand(fim+1);
            i2 = a.getRand(fim+1);
            i3 = a.getRand(fim+1);
            i4= a.getRand(fim+1);
            i5= a.getRand(fim+1);



            T aux[5] = {vet[i1], vet[i2], vet[i3],vet[i4],vet[i5]};
            T auxiliar;

            for (int k = 0; k < 3; k++) {
                if (aux[k].id > aux[k + 1].id) {
                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];
                }
                if (aux[k].id > aux[k + 2].id) {

                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];

                }
            }
            mediana = aux[3];

        }}
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
