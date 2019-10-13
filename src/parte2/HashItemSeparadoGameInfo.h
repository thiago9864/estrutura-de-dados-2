/**
    Universidade Federal de Juiz de Fora
    HashItemSeparado.h
    Propósito:

    @author Lucas Ribeiro
    @version 1.0 08/10/19
*/

#ifndef SRC_HASHITEMSEPARADOGAMEINFO_H
#define SRC_HASHITEMSEPARADOGAMEINFO_H

#include <iostream>

using namespace std;

/**
 * Item para a lista de um hash, esse é utilizado no Hash com Endereçamento Separado
 */
class HashItemSeparadoGameInfo {
public:
    HashItemSeparadoGameInfo(){}
    HashItemSeparadoGameInfo(int idGame, vector<string> boardgamecategory){
        this->boardgamecategory = boardgamecategory;
        this->idGame = idGame;
        this->prox = nullptr;
    }

    vector<string> boardgamecategory;
    long idGame; // É o id do jogo
    HashItemSeparadoGameInfo* prox;

};


#endif //SRC_HASHITEMSEPARADOGAMEINFO_H
