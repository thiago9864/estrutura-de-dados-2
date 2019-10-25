/**
    Universidade Federal de Juiz de Fora
    HashEndCoalescido.h
    Propósito:

    @author Lucas Ribeiro e Renan Nunes
    @version 1.0 08/10/19
*/
#ifndef SRC_HASHENDCOALESCIDO_H
#define SRC_HASHENDCOALESCIDO_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemCoalescido.h"
#include "../HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do endereçamento coealescido
 */
class HashEndCoalescido {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashEndCoalescido(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemCoalescido[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    /**
     * Destrutor do hash
     */
    ~HashEndCoalescido(){
        delete[] hashMap;
    };

    /**
     * Insere o item no hash, usando seu metodo respectivo de lidar com as colisões
     * @param item item a ser inserido no hash
     */
    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(item);
        } else {
            numColisoes++;
            for(int i = this->tamanho - 1; i >= 0; i--){
                if(this->isPosicaoVazia(i)) {
                    int pointerID = hs;
                    while(this->hashMap[pointerID].idNext != -1){
                        //cout << pointerID << endl;
                        pointerID = hashMap[pointerID].idNext;
                    }
                    hashMap[pointerID].idNext = i;
                    hashMap[i] = this->criaHashItem(item);
                    break;
                } else {
                    numColisoes++;
                }
                if(i==0){
                    cout << "ERRO, HASHTABLE CHEIA" << endl;
                }
            }
        }
    };

    /**
     * Verifica se um item está inserido no hash
     * @param item item à ser verificado
     * @return booleano indicando se o item existe no hash
     */
    bool buscar(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        while(hashMap[hs].idRating!=item.id || hashMap[hs].idNext == -1){
            hs = hashMap[hs].idNext;
        }
        return hashMap[hs].idRating == item.id;
    }

    /**
     * Retorna o tamanho da lista por trás do hash
     * @return tamanho do hash (ocupado + desocupado)
     */
    int getTamanho() const {
        return tamanho;
    };

    /**
     * Retorna a lista de items que tem por trás do hash
     * @return lista por trás do hash
     */
    HashItemCoalescido *getHashMap() const {
        return hashMap;
    };

    /**
     * Retorna o número de colisões que ocorreram na inserção desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de colisões que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumColisoes() const {
        return numColisoes;
    };

    /**
     * Retorna o número de comparações que ocorreram na inserção desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de comparações que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumComparacoes() const {
        return numComparacoes;
    };

    /**
     * Reseta os contadores de volta para seu valor inicial (0)
     */
    void resetContadores(){
        numColisoes = 0;
        numComparacoes = 0;
    };

    /**
     * Imprime o hashmap para debug
     */
    void imprime(){
        cout << endl << "------- Imprime a tabela Hash -------" << endl << endl;
        for(int i=0; i<tamanho; i++){
            cout << "#" << i << ": ";
            cout << "id: " << hashMap[i].idRating << ", ";
            cout << "user: " << hashMap[i].name << ", ";
            cout << "proximo: " << hashMap[i].idNext << endl;
        }
    }

private:
    int tamanho; // Tamanho do da lista que está sendo utilizado para guardar os items do hash
    HashItemCoalescido* hashMap; // Lista de hashItems sendo usado para guardar os itens inseridos
    int numColisoes; // Contador de colisões
    int numComparacoes; // Contador de comparações
    int primo; // Numero primo sendo utilizado no hash de divisão

    /**
     * Cria um novo item para o hash
     * @param ur Review à ser transformado em um item do hash
     * @return item para ser inserido no hash
     */
    HashItemCoalescido criaHashItem(UserReview ur){
        HashItemCoalescido h;
        h.idRating = ur.id;
        h.name = ur.user;
        h.idNext = -1;
        return h;
    };
    /**
     *
     * Cria um item vazio para inicializar o hash
     * @return item vazio para o hash
     */
    HashItemCoalescido criaHashItemVazio(){
        HashItemCoalescido h;
        h.name = "";
        h.idRating = -1;
        h.idNext = -2;
        return h;
    }

    /**
     * Testa se a posição inserida está vazia
     * @param pos posição à ser testada
     * @return booleano indicando se a posição da lista está ocupada ou não
     */
    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].idRating == -1;
    };


};


#endif //SRC_HASHENDCOALESCIDO_H
