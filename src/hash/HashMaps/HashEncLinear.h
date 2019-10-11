//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHENCLINEAR_H
#define SRC_HASHENCLINEAR_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;

class HashEncLinear {
public:

    HashEncLinear(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemBasic[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    ~HashEncLinear(){
        delete[] hashMap;
    };

    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        HashItemBasic newItem = this->criaHashItem(item);
        if(this->isPosicaoVazia(hs)){
            // não houve colisão - insere na tabela
            hashMap[hs] = criaHashItem(item);
        } else {
            // houve uma colisão - resolver
            // procura a próxima posição vazia na heap pelo metodo linear
            numColisoes++;
            int j=0;// conta a iteração
            int hs_search = hs+1;//auxiliar para percorrer linearmente a tabela
            while(j<tamanho){
                if(hs_search >= tamanho){
                    //chegou no fim do vetor sem resolver, busca do inicio agora
                    hs_search = 0;
                }
                if(isPosicaoVazia(hs_search)){
                    //a colisão foi resolvida
                    hashMap[hs] = criaHashItem(item);
                    break;
                } else {
                    numColisoes++;//contabiliza a colisão
                }
                j++;
                hs_search++;
            }
        }
    };

    /**
     * Verifica se o item está na tabela
     * @return boolean
     */
    bool buscar(UserReview item){
        //constroi o k com o valor de id e o nome do usuario
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);

        //verifica a tabela pra ver se o item está lá
        if(hashMap[hs].idRating == item.id){
            return true;
        }

        int j=0;//conta a iteração
        int hs_search = hs;//posição do hash
        while(j<tamanho){
            if(hashMap[hs_search].idRating == item.id){
                return true;
            }
            j++;
            hs_search++;
            if(hs_search >= tamanho){
                //chegou no fim do vetor sem resolver, busca do inicio agora
                hs_search = 0;
            }
        }

        return false;
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

    void resetContadores(){
        numColisoes=0;
        numComparacoes=0;
    };

};


#endif //SRC_HASHENCLINEAR_H
