/**
    Universidade Federal de Juiz de Fora
    BubbleSort.h
    Propósito: Implementação do algoritmo BubbleSort.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <iostream>

using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de BubbleSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class BubbleSort
{
    public:
        BubbleSort(){};
        ~BubbleSort(){};

        /**
         * Ordenação para os tipos de dados do dataset
         * @param vetor Vetor de objetos
         * @param tam Tamanho do vetor
         */
        void ordenar(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                //Reseta o trocou para saber ao final se algo foi ordenado ou se a lista já está ordenada
                bool trocou=false;
                for(int j=0; j<tam-1-i; j++){
                    if(comparador(vetor[j], vetor[j+1])){
                        //Caso o segundo seja menor que o primeiro eles são invertidos de posição
                        troca(vetor, j, j+1);
                        trocou=true;
                    }
                }
                //Caso não tenha mais o que ordenar, a ordenação é finalizada
                if(!trocou){
                    break;
                }
            }
        }

        /**
         * Ordenação para inteiros
         * @param vetor Vetor de inteiros
         * @param tam Tamanho do vetor
         */
        void ordenarInt(T* vetor, int tam){
            for(int i=0; i<tam-1; i++){
                bool trocou=false;
                for(int j=0; j<tam-1-i; j++){
                    if(comparadorInt(vetor[j], vetor[j+1])){
                        troca(vetor, j, j+1);
                        trocou=true;
                    }
                }
                if(trocou==false){
                    break;
                }
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
         * Inverte a posição de 2 itens no vetor
         * @param vetor vetor que está tendo seus itens invertidos
         * @param p1 posição do item 1 no vetor
         * @param p2 posição do item 2 no vetor
         */
        void troca(T* vetor, int p1, int p2){
            T aux = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = aux;
        }

};

#endif // BUBBLESORT_H
