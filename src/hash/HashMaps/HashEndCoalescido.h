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

        // Inicializa hashMap
        this->hashMap = new HashItemCoalescido[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashEndCoalescido(){
        delete[] hashMap;
    };

    int getTamanho() const {
        return tamanho;
    }

    HashItemCoalescido *getHashMap() const {
        return hashMap;
    }

    int getNumColisoes() const {
        return numColisoes;
    }

    int getNumComparacoes() const {
        return numComparacoes;
    }

private:
    int tamanho;
    HashItemCoalescido* hashMap;
    int numColisoes;
    int numComparacoes;

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

};


#endif //SRC_HASHENDCOALESCIDO_H
