//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHITEMCOALESCIDO_H
#define SRC_HASHITEMCOALESCIDO_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de um hash, esse é utilizado no Hash com Endereçamento Coalescido
 */
class HashItemCoalescido {
public:
    string name;
    long idRating; // É o id do rating
    long idNext; // Eh o id que o proximo item foi redirecionado em caso de colisao
};


#endif //SRC_HASHITEMCOALESCIDO_H
