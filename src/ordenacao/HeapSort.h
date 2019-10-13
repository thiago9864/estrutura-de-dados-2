/**
    Universidade Federal de Juiz de Fora
    HeapSort.h
    Propósito: Implementação do algoritmo HeapSort.

    @author Luan Reis, Renan Nunes
    @version 2.0 03/10/19
*/

#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <iostream>

using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de HeapSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class HeapSort
{
public:
    HeapSort(){};
    ~HeapSort(){};

    /**
     * Ordenação para os tipos de dados do dataset
     * @param v Vetor de objetos
     * @param t Tamanho do vetor
     */
    void ordenar(T *v, int n)
    {
        constroiHeap(n,v);
        for (int i = n-1; i > 1; i--)
        {
            constroiHeap(i,v);
            troca2(v,0,i);
        }
    };

    /**
     * Ordenação para inteiros
     * @param v Vetor de inteiros
     * @param t Tamanho do vetor
     */
    void ordenarInt(T *v, int n)
    {
        constroiHeapInt(n,v);
        for (int i = n-1; i > 1; i--)
        {
            constroiHeapInt(i,v);
            troca2(v,0,i);
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

    /**
     * Constroi uma heap com os itens do vetor de tipo T
     * @param m o indice o primeiro item que o constroiHeap não deve considerar na hora de "heapify" o vetor
     * @param vet vetor à ser ordenado em forma de heap
     */
    void constroiHeap(int m, T *vet)
    {
        // Inicializa as variaveis
        int tam = m;
        int p = (int) (tam/2) - 1;
        bool existe2 = true;

        while(p > -1)
        {
            // Conforme passam as iterações ele vai montando as subarvores
            T pai = vet[p];
            T filho1 = vet[2*p];
            T filho2 = vet[2*p+1];

            // Aqui ele testa se o item p da lista tem filhos na heap
            if(2*p+1 >= tam)
            {
                existe2 = false;
            }

            // Aqui está sendo testado se as subarvores cumprem os criterios para a arvore
            // montada ser considerada uma heap
            if(comparador(filho1, filho2) && existe2)
            {
                if(comparador(pai, filho2))
                {
                    troca2(vet,p,2*p+1);
                }
            } else
            {
                troca2(vet,p,2*p);
            }
            p--;
        }
    }

    /**
     * Constroi uma heap com os itens do vetor de inteiros
     * @param m o indice o primeiro item que o constroiHeap não deve considerar na hora de "heapify" o vetor
     * @param vet vetor à ser ordenado em forma de heap
     */
    void constroiHeapInt(int m, T *vet)
    {
        // Inicializa as variaveis
        int tam = m;
        int p = (int) (tam/2) - 1;
        bool existe2 = true;

        while(p > -1)
        {
            // Conforme passam as iterações ele vai montando as subarvores
            int pai = vet[p];
            int filho1 = vet[2*p];
            int filho2 = vet[2*p+1];

            // Aqui ele testa se o item p da lista tem filhos na heap
            if(2*p+1 >= tam)
            {
                existe2 = false;
            }

            // Aqui está sendo testado se as subarvores cumprem os criterios para a arvore
            // montada ser considerada uma heap
            if(comparadorInt(filho1, filho2) && existe2)
            {
                if(comparadorInt(pai, filho2))
                {
                    troca2(vet,p,2*p+1);
                }
            } else
            {
                troca2(vet,p,2*p);
            }
            p--;
        }
    }

    /**
     * Recebe dois parametros, diz se a.id < b.id e atualiza o contador
     * @param a item 1 da comparação
     * @param b item 2 da comparação
     * @return booleano indicando se a.id < b.id
     */
    bool comparador(T a, T b){
        num_comparacoes++;
        return a.id < b.id;
    }

    /**
     * Recebe dois parametros, diz se a > b e atualiza o contador
     * @param a item 1 da comparação
     * @param b item 2 da comparação
     * @return booleano indicando se a > b
     */
    bool comparadorInt(int a, int b){
        num_comparacoes++;
        return a < b;
    }

    /**
     * Inverte a posição de um item com o seu pai na heap e atualiza do contador de trocas
     * @param vet vetor que está tendo seus itens invertidos
     * @param f posição do item a ser trocado
     */
    void troca(T *vet, int f)
    {
        T aux;
        aux = vet[f / 2];
        vet[f / 2] = vet[f];
        vet[f] = aux;
        num_trocas++;
    }

    /**
     * Inverte a posição de 2 itens no vetor e atualiza do contador de trocas
     * @param vet vetor que está tendo seus itens invertidos
     * @param i posição do item 1 no vetor
     * @param j posição do item 2 no vetor
     */
    void troca2(T *vet, int i, int j){
        T aux;
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        num_trocas++;
    }

};

#endif // HEAPSORT_H
