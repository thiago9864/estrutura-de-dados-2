/**
    Universidade Federal de Juiz de Fora
    EndSondagemLinear.h
    Propósito: Implementação do algoritmo de Hash de endereçamento por sondagem linear.

    @author Thiago Almeida
    @version 1.0 14/08/19
*/

#ifndef ENDSONDAGEMLINEAR_H
#define ENDSONDAGEMLINEAR_H

#include <iostream>
#include "../UserReview.h"
#include "HashMapItem.h"

using namespace std;

class EndSondagemLinear
{
    public:
        EndSondagemLinear(UserReview* vetor, int tam){
            this->vetor = vetor;
            this->tamanho = tam;

            //inicializa hashMap
            hashMap = new HashMapItem[tam];
            for(int i=0; i<tam; i++){
                hashMap[i] = criaHashMapItem(-1, criaUserReview(-1,"",0));
            }
        };
        ~EndSondagemLinear(){
            delete[] hashMap;
        };

        /**
         * Constroi o hashmap para o dataset indicado
         */ 
        void construir(){
            for(int i=0; i<tamanho; i++){

                //constroi o k com o valor de id e o nome do usuario
                int k = vetor[i].id + somaAsciiFromString(vetor[i].user);
                int hs = funcaoHash(k, tamanho);

                //coloca no hashmap
                if(hashMap[hs].userReview.id == -1){
                    //o espaço está vazio
                    //inclui na posição gerada pela função hash uma referencia para o item do vetor
                    hashMap[hs] = criaHashMapItem(hs, vetor[i]);
                } else {
                    //houve uma colisão
                    //procura a próxima posição vazia na heap pelo metodo linear
                    int j=0;//conta a iteração
                    int hs_search = hs;//posição do hash
                    while(j<tamanho){
                        if(hashMap[hs_search].userReview.id == -1){
                            //a colisão foi resolvida
                            hashMap[hs_search] = criaHashMapItem(hs_search, vetor[i]);
                            numColisoesResolvidasLin++;//contabiliza colisões resolvidas
                            break;
                        }
                        j++;
                        hs_search++;
                        if(hs_search >= tamanho){
                            //chegou no fim do vetor sem resolver, busca do inicio agora
                            hs_search = 0;
                        }
                    }

                }
            }
        }

        /**
         * Obtem o vetor do hashmap
         * @return HashMapItem*
         */
        HashMapItem* getHashMap(){
            return hashMap;
        }

        /**
         * Obtem o numero de colisões
         * @return int
         */
        int getNumColisoes(){
            return numColisoesResolvidasLin;
        }

        /**
         * Imprime o hashmap para debug
         */
        void imprime(){
            cout << endl << "------- Imprime a tabela Hash -------" << endl << endl;
            for(int i=0; i<tamanho; i++){
                cout << "#" << i << ": ";
                cout << "hash: " << hashMap[i].hs << ", ";
                cout << "id: " << hashMap[i].userReview.id << ", ";
                cout << "user: " << hashMap[i].userReview.user << endl;
            }
        }
    private:
        int tamanho;
        UserReview* vetor;
        HashMapItem *hashMap;
        int numColisoesResolvidasLin=0;

        /**
         * Função de hash usada
         */
        int funcaoHash(int k, int m){
            return k % m;
        }

        /**
         * Soma os valores da posição do caractere na tabela ascii, dada a string
         * @param str String pra somar
         * @return int
         */
        int somaAsciiFromString(string str){
            int ret = 0;
            for(int i=0; i<str.length(); i++){
                ret += int(str.at(i));
            }
            return ret;
        }

        /**
         * Cria objeto UserReview
         * @param id
         * @param user
         * @param rating
         * @return UserReview
         */
        UserReview criaUserReview(int id, string user, float rating){
            UserReview u;
            u.id = id;
            u.user = user;
            u.rating = rating;
            return u;
        }

        /**
         * Cria objeto HashMapItem
         * @param id
         * @param user
         * @param rating
         * @return UserReview
         */
        HashMapItem criaHashMapItem(int hash_ind, UserReview userReview){
            HashMapItem h;
            h.hs = hash_ind;
            h.userReview = userReview;
            return h;
        }
};

#endif // ENDSONDAGEMLINEAR_H
