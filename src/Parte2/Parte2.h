//
// Created by luand on 13/10/2019.
//

#ifndef SRC_PARTE2_H
#define SRC_PARTE2_H
#include "../hash/HashMaps/HashEncSeparado.h"
#include "LeitorBase.h"
#include "UserReview.h"
#include <iostream>

using namespace std;

class Parte2{

public:

    Parte2(T* vet,int tam,int N ){
        this.tam=tam;
        this.npalavrasrepetidas=N;
        hash1=new HashEncSeparado;
        a=new LeitorBase;
        a.gerarSemente();


    }
private:

int tam;
HashEncSeparado* Hash1;
HashEncSeparado* Hashavaliações;
HashEncSeparado* Hashcategorias;
int npalavrasrepetidas;
LeitorBase a;
int id=0;
String boardgamecategory=0;
string user=0;





    void hash1InsereN(T* vet)
    {
        int j;
        for(int i=0;i<=tam,i++){
            j=a.getRand(tam-1);
            Hash1->inserir(vet[j]);
        }
    }





};




#endif //SRC_PARTE2_H
