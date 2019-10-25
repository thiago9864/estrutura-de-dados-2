/**
    Universidade Federal de Juiz de Fora
    HashItemBasic.h
    Propósito:

    @author Lucas Ribeiro
    @version 1.0 08/10/19
*/

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
