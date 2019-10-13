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

/**
 * Classe que ordena uma lista usando o metodo de QuickSort Recursivo
 * @tparam T Tipo do item da lista
 */
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
        void ordenar(T* vet, int inicio, int fim){

            if (inicio < fim)
            {
                int p = particao(vet,inicio,fim);
                ordenar(vet, inicio, p-1);
                ordenar(vet, p + 1,fim);
            }
        };

        /**
         * Ordenação para inteiros
         * @param vet Vetor de inteiros
         * @param inicio Posição de inicio do vetor
         * @param fim Posição final do vetor
         */
        void ordenarInt(int* vet, int inicio, int fim){

            if (inicio < fim)
            {
                int p = particaoInt(vet, inicio, fim);

                ordenarInt(vet, inicio, p-1);
                ordenarInt(vet, p + 1,fim);
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
        long long int num_comparacoes; // Contador de comparações
        long long int num_trocas; // Contador de trocas


        /**
         * Escolhe um pivo entre o inicio e o fim especificado, depois coloca todos os maiores que ele de um lado e
         * todos os maiores do outro
         * @param vet vetor à ser particionado
         * @param inicio indice que começa a parte a ser particionada
         * @param fim  indice que termina a parte a ser particionada
         * @return a posição que o pivo ficou
         */
        int particao(T* vet, int inicio, int fim){

            int i = inicio - 1;
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

        /**
         * Escolhe um pivo entre o inicio e o fim especificado, depois coloca todos os maiores que ele de um lado e
         * todos os maiores do outro
         * @param vet vetor à ser particionado
         * @param inicio indice que começa a parte a ser particionada
         * @param fim  indice que termina a parte a ser particionada
         * @return a posição que o pivo ficou
         */
        int particaoInt(int* vet,int inicio, int fim){

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

        /**
         * Recebe dois parametros, diz se a.id <= b.id e atualiza o contador
         * @param a item 1 da comparação
         * @param b item 2 da comparação
         * @return booleano indicando se aid <= b.id
         */
        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id <= b.id;
        }

        /**
         * Recebe dois parametros, diz se a <= b e atualiza o contador
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
        void troca(T* vet, int i, int j){
            num_trocas++;
            T aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        };

};

#endif // QUICKSORT_H
