/**
    Universidade Federal de Juiz de Fora
    HashEndAberto.h
    Propósito: Implementação do algoritmo de Hash por endereçamento aberto.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef HASHENDABERTO_H
#define HASHENDABERTO_H

#include <iostream>
#include "../UserReview.h"

using namespace std;

class HashMapItem {
    public:
        int hs;
        UserReview userReview;
};
class HashEndAberto
{
    public:
        HashEndAberto(UserReview* vetor, int tam){
            this->vetor = vetor;
            this->tamanho = tam;

            //inicializa hashMap
            hashMap = new HashMapItem[tam];
            for(int i=0; i<tam; i++){
                hashMap[i] = criaHashMapItem(-1, criaUserReview(-1,"",0));
            }
        };
        ~HashEndAberto(){

        };

        //metodos da classe
        void construir(){
            for(int i=0; i<tamanho; i++){
                //cout << "id: " << vetor[i].id << ", ";
                //cout << "user: " << vetor[i].user << ", ";
                //cout << "soma ascii: " << somaAsciiFromString(vetor[i].user) << endl;
                int k = vetor[i].id + somaAsciiFromString(vetor[i].user);
                int hs = funcaoHash(k, tamanho);

                //coloca no hashmap
                if(hashMap[hs].userReview.id == -1){
                    //o espaço está vazio
                    hashMap[hs] = criaHashMapItem(hs, vetor[i]);
                    cout << "hash: " << hs << endl;
                } else {
                    //houve uma colisão
                    cout << "colisao com o hash: " << hs << endl;
                    //procura a próxima posição vazia na heap
                    int j=0;
                    int hs_search = hs;
                    while(j<tamanho){
                        if(hashMap[hs_search].userReview.id == -1){
                            hashMap[hs_search] = criaHashMapItem(hs_search, vetor[i]);
                            cout << "colisao resolvida com o hash: " << hs_search << endl;
                            break;
                        }
                        j++;
                        hs_search++;
                        if(hs_search >= tamanho){
                            hs_search = 0;
                        }
                    }

                }
            }
        }

        void imprime(){
            cout << endl << "------- Imprime a tabela Hash -------" << endl << endl;
            for(int i=0; i<tamanho; i++){
                cout << "hash: " << hashMap[i].hs << ", ";
                cout << "id: " << hashMap[i].userReview.id << ", ";
                cout << "user: " << hashMap[i].userReview.user << endl;
            }
        }
    private:
        int tamanho;
        UserReview* vetor;
        HashMapItem *hashMap;

        int funcaoHash(int k, int m){
            return k % m;
        }

        int somaAsciiFromString(string str){
            int ret = 0;
            for(int i=0; i<str.length(); i++){
                ret += int(str.at(i));
            }
            return ret;
        }

        UserReview criaUserReview(int id, string user, float rating){
            UserReview u;
            u.id = id;
            u.user = user;
            u.rating = rating;
            return u;
        }

        HashMapItem criaHashMapItem(int hash_ind, UserReview userReview){
            HashMapItem h;
            h.hs = hash_ind;
            h.userReview = userReview;
            return h;
        }
};

#endif // HASHENDABERTO_H
