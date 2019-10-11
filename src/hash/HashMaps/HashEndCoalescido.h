//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHENDCOALESCIDO_H
#define SRC_HASHENDCOALESCIDO_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemCoalescido.h"
#include "../HashFunctions.h"

using namespace std;

class HashEndCoalescido {
public:

    HashItemCoalescido(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemCoalescido[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashEndCoalescido(){
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        HashItemCoalescido newItem = this->criaHashItem(hs, item);
        if(this->isPosicaoVazia(hs)){
            // TODO: Realizar inserção
        }
    };

    int getTamanho() const {
        return tamanho;
    };

    HashItemCoalescido *getHashMap() const {
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
    HashItemCoalescido* hashMap;
    int numColisoes;
    int numComparacoes;
    int primo;

    HashItemCoalescido criaHashItem(int hs, UserReview ur){
        HashItemCoalescido h;
        h.hs = hs;
        h.rating = ur.rating;
        h.name = ur.user;
        h.idNext = -1;

        return h;
    };

    HashItemCoalescido criaHashItemVazio(){
        HashItemCoalescido h;
        h.hs = -1;
        h.name = "";
        h.rating = 0;
        h.idNext = -2;

        return h;
    };

    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].hs == -1;
    };

};


#endif //SRC_HASHENDCOALESCIDO_H
