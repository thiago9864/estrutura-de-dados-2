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


class HashEncSeparado {
public:
    HashEncSeparado(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemSeparado[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashEncSeparado(){
        for(int i = 0; i<this->tamanho; i++){
            if(hashMap[i].prox != nullptr){
                deleteRecursivo(hashMap[i].prox);
            }
        }
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(item);
        } else {
            HashItemSeparado* currentPointer = hashMap[hs].prox;
            if(currentPointer != nullptr){
                while(currentPointer->prox != nullptr){
                    currentPointer = currentPointer->prox;
                }
            }
            else {
                hashMap[hs].prox = new HashItemSeparado(item.user, item.id);
                return;
            }
            currentPointer->prox = new HashItemSeparado(item.user, item.id);
        }
    };

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

    int getTamanho() const {
        return tamanho;
    };

    HashItemSeparado *getHashMap() const {
        return hashMap;
    };

    int getNumColisoes() const {
        return numColisoes;
    };

    int getNumComparacoes() const {
        return numComparacoes;
    };

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
    int tamanho;
    HashItemSeparado* hashMap;
    int numColisoes;
    int numComparacoes;
    int primo;

    HashItemSeparado criaHashItem(UserReview ur){
        HashItemSeparado h;
        h.idRating = ur.id;
        h.name = ur.user;
        h.prox = nullptr;
        return h;
    };

    HashItemSeparado criaHashItemVazio(){
        HashItemSeparado h;
        h.name = "";
        h.idRating = -1;
        h.prox = nullptr;
        return h;
    }

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
