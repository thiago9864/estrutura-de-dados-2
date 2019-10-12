//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHITEMSEPARADO_H
#define SRC_HASHITEMSEPARADO_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de um hash, esse é utilizado no Hash com Endereçamento Separado
 */
class HashItemSeparado {
public:
    HashItemSeparado(){}
    HashItemSeparado(string name, long idRating){
        this->name = name;
        this->idRating = idRating;
        this->prox = nullptr;
    }

    string name;
    long idRating; // É o id do rating
    HashItemSeparado* prox;

};


#endif //SRC_HASHITEMSEPARADO_H
