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
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        HashItemSeparado newItem = this->criaHashItem(item);
        if(this->isPosicaoVazia(hs)){
            // TODO: Realizar inserção
        }
    };

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

    void resetContadores(){
        numColisoes=0;
        numComparacoes=0;
    };
};


#endif //SRC_HASHENCSEPARADO_H
