/**
    Universidade Federal de Juiz de Fora
    InsertionSort.h
    Propósito: Implementação do algoritmo SelectionSort.

    @author Thiago Almeida
    @version 1.1 26/09/19
*/

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <iostream>

using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de InsertionSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class InsertionSort
{
    public:
        InsertionSort(){};
        ~InsertionSort(){};

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vetor Vetor de objetos
         * @param tam Tamanho do vetor
         */
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=0 && comparador(vetor[j], pivo)){
                    troca(vetor, j+1, j);
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        /**
         * Ordenação para os tipos de dados do dataset otimizado para o QuickSortInsertion
         * @param vetor Vetor de objetos
         * @param start Posicao inicial do vetor
         * @param finish Posição final do vetor
         */
        void ordenarQuick(T* vetor, int start, int finish){
            for(int i=start; i<finish; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=start && comparador(vetor[j], pivo)){
                    vetor[j+1] = vetor[j];
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        /**
         * Ordenação para inteiros
         * @param vetor Vetor de inteiros
         * @param tam Tamanho do vetor
         */
        void ordenarInt(T* vetor, int tam){
            tamanho=tam;
            for(int i=0; i<tam; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=0 && comparadorInt(vetor[j], pivo)){
                    troca(vetor, j+1, j);
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

        /**
         * Ordenação para os tipos de dados do dataset otimizado para o QuickSortInsertion
         * @param vetor Vetor de objetos
         * @param start Posicao inicial do vetor
         * @param finish Posição final do vetor
         */
        void ordenarIntQuick(T* vetor, int start, int finish){
            for(int i=start; i<finish; i++){
                T pivo=vetor[i];
                int j=i-1;
                while(j>=start && comparadorInt(vetor[j], pivo)){
                    vetor[j+1] = vetor[j];
                    j-=1;
                }
                vetor[j+1] = pivo;
            }
        }

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
        long long int getNumComparacoes(){
            return num_comparacoes;
        }

        /**
         * Retorna o numero de trocas contabilizado pelo contador
         * @return numero de trocas feitas desde a ultima inicialização dos contadores
         */
        long long int getNumTrocas(){
            return num_trocas;
        }
    private:
        long long int num_comparacoes; // Contador de comparações
        long long int num_trocas; // Contador de trocas
        int tamanho; // Tamanho da lista à ser ordenada

        /**
         * Recebe dois parametros, diz se a.id > b.id e atualiza o contador
         * @param a item 1 da comparação
         * @param b item 2 da comparação
         * @return booleano indicando se a.id > b.id
         */
        bool comparador(T a, T b){
            num_comparacoes++;
            return a.id > b.id;
            }

        /**
         * Recebe dois parametros, diz se a > b e atualiza o contador
         * @param a item 1 da comparação
         * @param b item 2 da comparação
         * @return booleano indicando se a > b
         */
        bool comparadorInt(int a, int b){
            num_comparacoes++;
            return a > b;
        }

        /**
         * Função que coloca o item da posição b do vetor no lugar do da posição a e invremmenta o numero de trocas
         * @param vetor vetor que está tendo seus itens invertidos
         * @param a posição do item 1 no vetor
         * @param b posição do item 2 no vetor
         */
        void troca(T* vetor, int a, int b){
            num_trocas++;
            vetor[a] = vetor[b];
        }
};

#endif // INSERTIONSORT_H
