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
        EndSondagemLinear(int tam){
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
         * Inserção do registro na tabela
         */
        void inserir(UserReview item){
            //constroi o k com o valor de id e o nome do usuario
            int k = item.id + somaAsciiFromString(item.user);
            int hs = funcaoHash(k, tamanho);

            //coloca no hashmap
            if(posicaoVazia(hs)){
                //o espaço está vazio
                //inclui na posição gerada pela função hash uma referencia para o item do vetor
                hashMap[hs] = criaHashMapItem(hs, item);
            } else {
                //houve uma colisão
                //procura a próxima posição vazia na heap pelo metodo linear
                numColisoes++;//contabiliza a colisão
                int j=0;//conta a iteração
                int hs_search = hs;//posição do hash
                while(j<tamanho){
                    if(posicaoVazia(hs_search)){
                        //a colisão foi resolvida
                        hashMap[hs_search] = criaHashMapItem(hs_search, item);
                        break;
                    } else {
                        numColisoes++;//contabiliza a colisão
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

        /**
         * Verifica se o item está na tabela
         * @return boolean
         */
        bool buscar(UserReview item){
            //constroi o k com o valor de id e o nome do usuario
            int k = item.id + somaAsciiFromString(item.user);
            int hs = funcaoHash(k, tamanho);

            //verifica a tabela pra ver se o item está lá
            if(hashMap[hs].userReview.id == item.id){
                return true;
            }

            int j=0;//conta a iteração
            int hs_search = hs;//posição do hash
            while(j<tamanho){
                if(hashMap[hs_search].userReview.id == item.id){
                    return true;
                }
                j++;
                hs_search++;
                if(hs_search >= tamanho){
                    //chegou no fim do vetor sem resolver, busca do inicio agora
                    hs_search = 0;
                }
            }

            return false;
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
            return numColisoes;
        }

        /**
         * Obtem o numero de comparações de chaves
         * @return int
         */
        int getNumComparacoes(){
            return numComparacoes;
        }

        /**
         * Zera os contadores de comparação e colisão
         * @return int
         */
        void resetContadores(){
            numColisoes=0;
            numComparacoes=0;
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
        int numColisoes;
        int numComparacoes;

        /**
         * Função de hash usada
         */
        int funcaoHash(int k, int m){
            return k % m;
        }

        /**
         * Verifica se a posição do hash está vazia
         * @param hs Indice do vetor que representa o hash
         * @return bool
         */
        bool posicaoVazia(int hs){
            numComparacoes++;
            return hashMap[hs].userReview.id == -1;
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
