//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHREHASH_H
#define SRC_HASHREHASH_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;


class HashReHash {
public:
    HashReHash(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemBasic[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashReHash(){
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        int initialHS = hs;
        HashItemBasic newItem = this->criaHashItem(hs, item);
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(hs, item);
        } else {
            int hs2 = HashFunctions::multiplicacao(item.id, item.user, this->tamanho);
            this->numColisoes++;
            hs = (hs + hs2) % this->tamanho;

            while(!this->isPosicaoVazia(hs)){
                this->numColisoes++;
                hs = (hs + hs2) % this->tamanho;
            }
            hashMap[hs] = criaHashItem(initialHS, item);

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
    int primo;

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


#endif //SRC_HASHREHASH_H
