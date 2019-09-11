/**
    Universidade Federal de Juiz de Fora
    EndSondagemQuadratica.h
    Propósito: Implementação do algoritmo de Hash de endereçamento por sondagem quadrática.

    @author Thiago Almeida
    @version 1.0 11/09/19
*/

#ifndef ENDSONDAGEMQUADRATICA_H
#define ENDSONDAGEMQUADRATICA_H

#include <iostream>
#include <cmath>
#include "../UserReview.h"

using namespace std;


class EndSondagemQuadratica
{
    public:
        EndSondagemQuadratica(UserReview* vetor, int tam){
            this->vetor = vetor;
            this->tamanho = tam;

            //inicializa hashMap
            hashMap = new HashMapItem[tam];
            for(int i=0; i<tam; i++){
                hashMap[i] = criaHashMapItem(-1, criaUserReview(-1,"",0));
            }
        };
        ~EndSondagemQuadratica(){
            delete[] hashMap;
        };

        //metodos da classe
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
                    //procura a próxima posição vazia na heap pelo metodo quadrático
                    int j=0;//conta a iteração
                    int hs_search = hs;//posição no hash
                    while(j<tamanho){
                        if(hashMap[hs_search].userReview.id == -1){
                            //a colisão foi resolvida
                            hashMap[hs_search] = criaHashMapItem(hs_search, vetor[i]);
                            break;
                        }

                        hs_search = hs + pow(2, j);
                        j++;
                        if(hs_search >= tamanho){
                            //chegou no fim do vetor sem resolver, busca do inicio agora
                            hs_search = hs_search - tamanho;//pega o quanto passou e volta pra origem
                            if(hs_search >= tamanho){
                                cout << "Nao foi possivel encontrar uma posicao vazia para corrigir a colisao" << endl;
                                cout << "A colisao ocorreu no hash: " << hs << endl;
                                imprime();
                                exit(1);
                            }
                        }
                    }

                }
            }
        }

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

#endif // ENDSONDAGEMQUADRATICA_H