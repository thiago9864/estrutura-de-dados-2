//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHITEMCOALESCIDO_H
#define SRC_HASHITEMCOALESCIDO_H

#include <iostream>

using namespace std;

class HashItemCoalescido {
public:
    int hs;
    String name;
    long rating;
    int idNext; // Eh o id que o proximo item foi redirecionado em caso de colisao
};


#endif //SRC_HASHITEMCOALESCIDO_H
