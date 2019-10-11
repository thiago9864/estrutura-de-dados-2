/**
    Universidade Federal de Juiz de Fora
    HashListaEncadeada.h
    Propósito: Resolver conflitos de hash usando listas encadeadas

    @author Luan Reis Ciribelli
    @version 1.0 10/10/2019
*/

#include <iostream>
#include "../UsersRated.h"
#include "ListaEncadeada.h"
#include "../UserReview.h"
#include "HashmapItemAux.h"

using namespace std;





class HashListaEncadeada
{

private:
    int tamanho; //Tamanho Original dos dados
    int m; //Tamanho da Tabela Hash
    int numeroComparacoes; //Número de Comparações feitas
    UserReview* vetor; // vetor de valores desejados
    HashMapItemAux *hashMap;

public:
    HashListaEncadeada(UserReview* vetor, int tam)
    {
        this->vetor = vetor;
        this->tamanho = tam;
        vetor = new UserReview[this->tamanho];



        for(int i = 0; i < this->m; i++)
        {
            hashMap[i] = criaHashMapItem(NULL, criaUserReview(-1,"",0));
        }
    };

    void inserir(UserReview item)
    {
        int k = item.id + somaAsciiFromString(item.user);
        int hs = funcaoHash(k,m);
        hashMap[hs].a->inserir_inicio(hs);

    };







    ~HashListaEncadeada()
    {
        delete [] vetor;
        delete [] hashMap;

    };




    UserReview criaUserReview(int id, string user, float rating)
    {
        UserReview u;
        u.id = id;
        u.user = user;
        u.rating = rating;
        return u;
    }

    HashMapItemAux criaHashMapItem(int hash_ind, UserReview userReview)
    {
        HashMapItemAux h;
        h.a->inserir_inicio(hash_ind);
        h.user= UserReview.user;
        h.rating=UserReview.rating;
        return h;
    }

    int funcaoHash(int k, int m)
    {
        return k % m;
    }


    int somaAsciiFromString(string str)
    {
        int ret = 0;
        for(int i=0; i<str.length(); i++)
        {
            ret += int(str.at(i));
        }
        return ret;
    }






};
