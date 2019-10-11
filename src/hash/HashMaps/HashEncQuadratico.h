//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHENCQUADRATICO_H
#define SRC_HASHENCQUADRATICO_H

#include <iostream>
#include <cmath>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;

class HashEncQuadratico {
public:

    HashEncQuadratico(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

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
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        HashItemBasic newItem = this->criaHashItem(item);
        if(this->isPosicaoVazia(hs)){
            // não houve colisão - insere na tabela
            hashMap[hs] = criaHashItem(item);
        } else {
            // houve uma colisão - resolver
            // procura a próxima posição vazia na heap pelo metodo linear
            numColisoesQuad++;
            int j=1;// conta a iteração
            int hs_search = hs+1;//auxiliar para percorrer linearmente a tabela
            resolvendoComHashQuadratico=true;//inicia com hash quadratico

            while(j<tamanho){
                if(hs_search >= tamanho){
                    //fim do vetor, tenta pegar do inicio com a diferença restante
                    hs_search -= tamanho;

                    if(hs_search >= tamanho){
                        //se ainda for maior que o tamanho da tabela, muda de estratégia
                        resolvendoComHashQuadratico=false;
                        numMudancasEstrategia++;
                        hs_search=hs+1;//vai resetar a posição do hash pra tentar o linear
                    }
                }

                if(isPosicaoVazia(hs_search)){
                    //a colisão foi resolvida
                    hashMap[hs] = criaHashItem(item);
                    break;
                } else {
                    if(resolvendoComHashQuadratico){
                        numColisoesQuad++;//contabiliza a colisão quadratica
                    } else {
                        numColisoesLin++;
                    }
                }

                //calcula o proximo salto
                if(resolvendoComHashQuadratico){
                    //estrategia para sondagem quadrática
                    hs_search = hs + pow(2, j);
                } else {
                    //estrategia para sondagem linear
                    hs_search++;
                }

                j++;
                hs_search++;
            }
        }
    };

    int getTamanho() const {
        return tamanho;
    };

    HashItemBasic *getHashMap() const {
        return hashMap;
    };

    int getNumColisoesQuadraticas() const {
        return numColisoesQuad;
    };
    int getNumColisoesLineares() const {
        return numColisoesLin;
    };

    int getNumComparacoes() const {
        return numComparacoes;
    };

    //TODO: Fazer um metodo de reset

private:
    int tamanho;
    HashItemBasic* hashMap;
    int numColisoesQuad;
    int numColisoesLin;
    int numMudancasEstrategia;
    int numComparacoes;
    bool resolvendoComHashQuadratico;
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


#endif //SRC_HASHENCQUADRATICO_H
