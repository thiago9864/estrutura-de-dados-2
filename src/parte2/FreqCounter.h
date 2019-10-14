/**
    Universidade Federal de Juiz de Fora
    HashItemSeparado.h
    Propósito:

    @author Thiago Almeida
    @version 1.0 08/10/19
*/

#ifndef SRC_FREQCOUNTER_H
#define SRC_FREQCOUNTER_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de um hash, esse é utilizado no Hash com Endereçamento Separado
 */
class FreqCounter {
public:
    FreqCounter(){}
    FreqCounter(int id, string categoria){
        this->id = id;
        this->prox = nullptr;
        this->frequencia = 1;
        this->categoria = categoria;
    }

    long id=0; // É o id do jogo
    long frequencia=0;
    string categoria="";
    FreqCounter* prox=nullptr;

};


#endif //SRC_FREQCOUNTER_H
