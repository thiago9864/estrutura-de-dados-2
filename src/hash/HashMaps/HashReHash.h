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
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(item);
        } else {
            int hs2 = HashFunctions::multiplicacao(item.id, item.user, this->tamanho);
            this->numColisoes++;
            hs = (hs + hs2) % this->tamanho;

            while(!this->isPosicaoVazia(hs)){
                this->numColisoes++;
                hs = (hs + hs2) % this->tamanho;
            }
            hashMap[hs] = criaHashItem(item);

        }
    };

    bool buscar(UserReview item){
        int hs = HashFunctions:: divisao(item.id, item.user, this->tamanho, this->primo);
        int checkCounter = 0;
        if(hashMap[hs].idRating == item.id){
            return true;
        }
        checkCounter++;
        int hs2 = HashFunctions::multiplicacao(item.id, item.user, this->tamanho);
        hs = hs + hs2;
        while(checkCounter <= this->tamanho){
            if(hashMap[hs].idRating == item.id){
                return true;
            }
            else{
                hs = hs + hs2;
            }
            checkCounter++;
        }
    }

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
            cout << "user: " << hashMap[i].name << endl;
        }
    }

private:
    int tamanho;
    HashItemBasic* hashMap;
    int numColisoes;
    int numComparacoes;
    int primo;

    HashItemBasic criaHashItem(UserReview ur){
        HashItemBasic h;
        h.idRating = ur.id;
        h.name = ur.user;
        return h;
    };

    HashItemBasic criaHashItemVazio(){
        HashItemBasic h;
        h.name = "";
        h.idRating = -1;
        return h;
    }

    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].idRating == -1;
    };

};


#endif //SRC_HASHREHASH_H
