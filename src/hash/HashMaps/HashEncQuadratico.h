//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHENCQUADRATICO_H
#define SRC_HASHENCQUADRATICO_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;

class HashEncQuadratico {
public:

    HashEncQuadratico(int tam){
        this->tamanho = tam;

        // Inicializa hashMap
        this->hashMap = new HashItemBasic[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashEncQuadratico(){
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho);
        HashItemBasic newItem = this->criaHashItem(hs, item);
        if(this->isPosicaoVazia(hs)){
            // TODO: Realizar inserção
        }
    };

    int getTamanho() const {
        return tamanho;
    };

    HashItemBasic *getHashMap() const {
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
    HashItemBasic* hashMap;
    int numColisoes;
    int numComparacoes;

    HashItemBasic criaHashItem(int hs, UserReview ur){
        HashItemBasic h;
        h.hs = hs;
        h.rating = ur.rating;
        h.name = ur.user;
        return h;
    };

    HashItemBasic criaHashItemVazio(){
        HashItemBasic h;
        h.hs = -1;
        h.name = "";
        h.rating = 0;
        return h;
    }

    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].hs == -1;
    };

};


#endif //SRC_HASHENCQUADRATICO_H
