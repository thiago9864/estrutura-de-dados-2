//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHITEMSEPARADO_H
#define SRC_HASHITEMSEPARADO_H

#include <iostream>

using namespace std;

class HashItemSeparado {
public:
    int hs;
    string name;
    long rating; // É o id do rating
    HashItemSeparado* prox;

};


#endif //SRC_HASHITEMSEPARADO_H
