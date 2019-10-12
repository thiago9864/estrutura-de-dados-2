//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHENCSEPARADO_H
#define SRC_HASHENCSEPARADO_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemSeparado.h"
#include "../HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do endereçamento separado
 */
class HashEncSeparado {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashEncSeparado(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemSeparado[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    /**
     * Destrutor do hash
     */
    ~HashEncSeparado(){
        for(int i = 0; i<this->tamanho; i++){
            if(hashMap[i].prox != nullptr){
                deleteRecursivo(hashMap[i].prox);
            }
        }
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
            HashItemSeparado* currentPointer = hashMap[hs].prox;
            if(currentPointer != nullptr){
                this->numComparacoes++;
                this->numColisoes++;
                while(currentPointer->prox != nullptr){
                    this->numComparacoes++;
                    this->numColisoes++;
                    currentPointer = currentPointer->prox;
                }
            }
            else {
                this->numComparacoes++;
                hashMap[hs].prox = new HashItemSeparado(item.user, item.id);
                return;
            }
            currentPointer->prox = new HashItemSeparado(item.user, item.id);
        }
    };

    /**
     * Verifica se um item está inserido no hash
     * @param item item à ser verificado
     * @return booleano indicando se o item existe no hash
     */
    bool buscar(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        if(hashMap[hs].idRating == item.id) return true;
        HashItemSeparado* currentPointer = hashMap[hs].prox;
        if(currentPointer == nullptr) return false;
        while(currentPointer->prox != nullptr){
            if(currentPointer->idRating == item.id) return true;
            currentPointer = currentPointer->prox;
        }
        return currentPointer->idRating == item.id;
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
    HashItemSeparado *getHashMap() const {
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
            cout << "encadeamento: ";
            HashItemSeparado *p = hashMap[i].prox;
            while(p != nullptr){
                cout << "{ " << p->idRating << ", " << p->name << "} ";
                p = p->prox;
            }
            cout << endl;
        }
    }

private:
    int tamanho; // Tamanho do da lista que está sendo utilizado para guardar os items do hash
    HashItemSeparado* hashMap; // Lista de hashItems sendo usado para guardar os itens inseridos
    int numColisoes; // Contador de colisões
    int numComparacoes; // Contador de comparações
    int primo; // Numero primo sendo utilizado no hash de divisão

    /**
     * Cria um novo item para o hash
     * @param ur Review à ser transformado em um item do hash
     * @return item para ser inserido no hash
     */
    HashItemSeparado criaHashItem(UserReview ur){
        HashItemSeparado h;
        h.idRating = ur.id;
        h.name = ur.user;
        h.prox = nullptr;
        return h;
    };

    /**
     * Cria um item vazio para inicializar o hash
     * @return item vazio para o hash
     */
    HashItemSeparado criaHashItemVazio(){
        HashItemSeparado h;
        h.name = "";
        h.idRating = -1;
        h.prox = nullptr;
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

    void deleteRecursivo(HashItemSeparado* deletado){
        if(deletado->prox != nullptr){
            this->deleteRecursivo(deletado->prox);
        }
        delete deletado;
    }
};


#endif //SRC_HASHENCSEPARADO_H
