//
// Created by lrpes on 11/10/2019.
//

#ifndef SRC_HASHFUNCTIONS_H
#define SRC_HASHFUNCTIONS_H

#include <iostream>

using namespace std;

class HashFunctions {
public:
    static int divisao(int id, string nome, int tamTable, int primo){
        return (geraNumeroHashable(id, nome) % primo) % tamTable;
    };

    static int multiplicacao(int id, string nome, int tamTable){
        int hashValue = geraNumeroHashable(id, nome);
        return 1 + (int)(10*(hashValue*0.61803399-(int)(hashValue*0.61803399)));
    };

    static int encontraPrimo(int x){
        int nNew = ((x * 2 + 3) - 2)/ 2;
        bool* colore = new bool[nNew + 1];
        for(int k = 0; k < nNew + 1; k++){
            colore[k] = false;
        }
        int primo = x;

        for(int i = 1; i <= nNew; i++){
            for(int j = i;(i + j + 2* i * j) <= nNew; j++){
                try{
                    colore[i + j + 2 * i * j] = true;
                } catch(exception e){
                    break;
                }
            }

            for(int k = x/2; k < nNew + 1; k++){
                if(!colore[k] && (k * 2 + 1) > x){
                    primo = k * 2 + 1;
                    break;
                }
            }
        }

        return primo;
    };

private:
    static int geraNumeroHashable(int id, string nome){
        // Conta as letras pelo asc code
        int totalLetras = 0;
        for(int i = 0; i<nome.length(); i++){
            totalLetras = totalLetras + int(nome.at(i));
        }
        return totalLetras + id;
    };
};


#endif //SRC_HASHFUNCTIONS_H
