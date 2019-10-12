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
    QuickSortMediana(){
        leitorBase=new LeitorBase();
        leitorBase->gerarSemente();
    };
    ~QuickSortMediana(){};

    void ordenar(T* vet, int k, int inicio, int fim)
    {
        this->k=k;
        if (inicio < fim)
        {
            calculaMedianak(vet, fim);
            int p = particao(vet, inicio, fim);

            ordenar(vet, k, inicio, p - 1);
            ordenar(vet, k, p + 1, fim);
        }
    };

    void ordenarInt(T *vet, int k, int inicio, int fim)
    {
        this->k=k;
        if (inicio < fim)
        {
            calculaMedianakInt(vet, fim);
            int p = particaoInt(vet, inicio, fim);
            ordenarInt(vet, k, inicio, p - 1);
            ordenarInt(vet, k, p + 1, fim);
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
    int mediana;
    int k;
    LeitorBase *leitorBase;

    void calculaMedianak(T *vet, int fim)
    {
        if(k==3) {
            int i1, i2, i3;
            i1 = leitorBase->getRand(fim+1);
            i2 = leitorBase->getRand(fim+1);
            i3 = leitorBase->getRand(fim+1);

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
            mediana = aux[1].id;
        }
        else {if(k==5){
            int i1, i2, i3, i4, i5;
            i1 = leitorBase->getRand(fim+1);
            i2 = leitorBase->getRand(fim+1);
            i3 = leitorBase->getRand(fim+1);
            i4 = leitorBase->getRand(fim+1);
            i5 = leitorBase->getRand(fim+1);



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
            mediana = aux[3].id;

        }}
    }

    void calculaMedianakInt(T *vet, int fim)
    {
        if(k==3) {
            int i1, i2, i3;
            i1 = leitorBase->getRand(fim+1);
            i2 = leitorBase->getRand(fim+1);
            i3 = leitorBase->getRand(fim+1);

            T aux[3] = {vet[i1], vet[i2], vet[i3]};
            T auxiliar;

            for (int k = 0; k < 2; k++) {
                if (aux[k] > aux[k + 1]) {
                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];
                }
                if (aux[k] > aux[k + 2]) {

                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];

                }
            }
            mediana = aux[1];
        }
        else {if(k==5){
            int i1, i2, i3, i4, i5;
            i1 = leitorBase->getRand(fim+1);
            i2 = leitorBase->getRand(fim+1);
            i3 = leitorBase->getRand(fim+1);
            i4= leitorBase->getRand(fim+1);
            i5= leitorBase->getRand(fim+1);



            T aux[5] = {vet[i1], vet[i2], vet[i3],vet[i4],vet[i5]};
            T auxiliar;

            for (int k = 0; k < 3; k++) {
                if (aux[k] > aux[k + 1]) {
                    auxiliar = aux[k];
                    aux[k] = aux[k + 1];
                    aux[k + 1] = aux[k];
                }
                if (aux[k] > aux[k + 2]) {

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

        int pivo = mediana;
        for (int j = inicio; j <= fim - 1; j++)
        {
            if (comparadorInt(vet[j].id, pivo))
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

        T pivo = mediana;
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

#endif // QUICKSORTMEDIANA_H
