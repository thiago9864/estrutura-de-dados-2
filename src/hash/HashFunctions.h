//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHFUNCTIONS_H
#define SRC_HASHFUNCTIONS_H

#include <iostream>

using namespace std;

class HashFunctions {
public:
    static int divisao(int id, string nome, int tamTable){
        int hashValue = geraNumeroHashable(id, nome);
        // TODO: Implementar Hash Divisão
        return 0;
    }

    static int multiplicacao(int id, string nome, int tamTable){
        int hashValue = geraNumeroHashable(id, nome);
        //TODO: Implementar Hash Multiplicação
        return 0;
    }

private:
    static int geraNumeroHashable(int id, string nome){
        // Conta as letras pelo asc code
        int totalLetras = 0;
        for(int i = 0; i<nome.length(); i++){
            totalLetras = totalLetras + int(nome.at(i));
        }
        return totalLetras + id;
    }
};


#endif //SRC_HASHFUNCTIONS_H
