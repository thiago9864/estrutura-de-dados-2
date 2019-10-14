/**
    Universidade Federal de Juiz de Fora
    HashItemSeparado.h
    Propósito:

    @author Lucas Ribeiro, Thiago Almeida
    @version 1.5 14/10/19
*/

#ifndef SRC_HASHITEMSEPARADOGAMEINFO_H
#define SRC_HASHITEMSEPARADOGAMEINFO_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de um hash, esse é utilizado no Hash com Endereçamento Separado
 */
class HashItemSeparadoParte2 {
public:
    HashItemSeparadoParte2(){}
    HashItemSeparadoParte2(string conteudo){
        this->conteudo = conteudo;
        this->prox = nullptr;
        this->frequencia = 1;
    }

    string conteudo = "";
    long frequencia = 0;
    HashItemSeparadoParte2* prox;

};


#endif //SRC_HASHITEMSEPARADOGAMEINFO_H
