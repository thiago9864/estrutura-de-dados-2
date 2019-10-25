/**
    Universidade Federal de Juiz de Fora
    HashItemSeparado.h
    Propósito:

    @author Lucas Ribeiro
    @version 1.0 08/10/19
*/

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
