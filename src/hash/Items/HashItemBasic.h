//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHITEMBASIC_H
#define SRC_HASHITEMBASIC_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de alguns hashes, esse é utilizado no Hash com Encadeamento Linear,
 * no Hash com Encadeamento Quadratico e no Hash com Rehashing
 */
class HashItemBasic {
public:
    string name;
    long idRating;
};


#endif //SRC_HASHITEMBASIC_H
