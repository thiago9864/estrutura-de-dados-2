/**
    Universidade Federal de Juiz de Fora
    BubbleSort.h
    Propósito: Implementação do algoritmo BubbleSort.

    @author Lucas Ribeiro Pessamilio
    @version 1.0 04/09/19
*/

#ifndef BASE_TRABALHO_HASHMAP_H
#define BASE_TRABALHO_HASHMAP_H

#include <iostream>
#include <UserReview.h>

using namespace std;

class HashingDuplo {

public:
    //TODO: Clean debug couts
    HashingDuplo(UserReview* vetor, int tam) {
        this->tamanho = tam;
        this->hasherModule = 13;
        newHashMap = new UserReview[tam];
        for(int i = 0; i<tam; i++){
            newHashMap[i] = UserReview();
            newHashMap[i].id = -1;
        }
        for(int i = 0; i<tam; i++){
            int nomeValue = this->contaLetras(vetor[i].user);
            int hashNumero = this->hasher(vetor[i].id, nomeValue);
            //cout << "ID: "<<vetor[i].id << endl;
            //cout << "Resultado Hash: " << hashNumero << endl;
            if(newHashMap[hashNumero].id == -1){
                newHashMap[hashNumero] = vetor[i];
                //cout << "Posicao Colocada: " <<hashNumero << endl;
            } else {
                int j = 1;
                int newHashNumero = hashNumero;
                while(newHashMap[newHashNumero].id != -1){
                    //cout << "Posicao Antiga: " <<newHashNumero << endl;

                    j++;
                    newHashNumero = this->rehasher(vetor[i].id,nomeValue,j,hashNumero);
                }
                //cout << "Posicao Colocada: " <<newHashNumero << endl;

                newHashMap[newHashNumero] = vetor[i];
            }
        }
    };

    ~HashingDuplo() {};

    void printHashMap(){
        for(int i = 0; i < tamanho;i++){
            cout << "Position: " << i << ", Key: (" << newHashMap[i].user << ", " << newHashMap[i].id << "), Value: " << newHashMap[i].rating << endl;
        }
    };

    float getRating(string name, int id){
        int nameValue = this->contaLetras(name);
        int hashID = hasher(id, nameValue);
        int oldHashID = hashID;
        int tryCounter = 1;
        while(newHashMap[hashID].id!=id && newHashMap[hashID].user!=name){
            hashID = rehasher(id,nameValue,tryCounter,oldHashID);
            if(tryCounter>this->tamanho){
                cout << "O item nao esta na lista, rating sera retornado -1" << endl;
                return -1;
            }
            tryCounter++;
        }
        return newHashMap[hashID].rating;

    };

private:
    UserReview* newHashMap;
    int tamanho;
    int hasherModule;

    int contaLetras(string nome){
        int total = 0;
        for(int i = 0; i<nome.length(); i++){
            total = total + int(nome.at(i));
        }
        return total;
    };

    int hasher(int id, int nomeValue){
        return (nomeValue*id)%this->tamanho;
    };

    int rehasher(int id, int nameValue, int tryNumber, int hasherValue){
        return (hasherValue + tryNumber*(1 + (nameValue*id)%this->hasherModule))%this->tamanho;
    };
};


#endif //BASE_TRABALHO_HASHMAP_H
