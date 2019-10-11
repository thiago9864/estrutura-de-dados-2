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
    HashEndCoalescido(int tam){
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
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(item);
        } else {
            numColisoes++;
            for(int i = this->tamanho - 1; i >= 0; i--){
                if(this->isPosicaoVazia(i)) {
                    int pointerID = hs;
                    while(pointerID!=-1){
                        pointerID = hashMap[pointerID].idNext;
                    }
                    hashMap[pointerID].idNext = i;
                    hashMap[i] = this->criaHashItem(item);
                } else {
                    numColisoes++;
                }
            }
        }
    };

    bool buscar(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        while(hashMap[hs].idRating!=item.id || hashMap[hs].idNext == -1){
            hs = hashMap[hs].idNext;
        }
        return hashMap[hs].idRating == item.id;
    }

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

    HashItemCoalescido criaHashItem(UserReview ur){
        HashItemCoalescido h;
        h.idRating = ur.id;
        h.name = ur.user;
        h.idNext = -1;
        return h;
    };

    HashItemCoalescido criaHashItemVazio(){
        HashItemCoalescido h;
        h.name = "";
        h.idRating = -1;
        h.idNext = -2;
        return h;
    }

    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].idRating == -1;
    };

    void resetContadores(){
        numColisoes = 0;
        numComparacoes = 0;
    };

};


#endif //SRC_HASHENDCOALESCIDO_H
