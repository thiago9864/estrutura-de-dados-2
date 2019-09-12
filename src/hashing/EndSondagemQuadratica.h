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
#include "HashMapItem.h"

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

        /**
         * Constroi o hashmap para o dataset indicado
         */
        void construir(){
            mudarEstrategia=false;//começa com a estratégia de rodar com a sondagem quadrática

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
                    int ji = -1;//guarda a posição do j ao entrar no quadratico
                    int hs_search = hs;//posição no hash
                    while(j<tamanho){
                        if(hashMap[hs_search].userReview.id == -1){
                            //a colisão foi resolvida
                            hashMap[hs_search] = criaHashMapItem(hs_search, vetor[i]);

                            //contabiliza as colisões resolvidas e o metodo usado
                            if(mudarEstrategia){
                                numColisoesResolvidasLin++;
                            } else {
                                numColisoesResolvidasQuad++;
                            }
                            ji = -1;
                            break;
                        }

                        if(ji == -1){
                            ji = j;//salva indice da iteracao
                        }

                        if(mudarEstrategia){
                            //estrategia para sondagem linear
                            hs_search++;
                        } else {
                            //estrategia para sondagem quadrática
                            hs_search = hs + pow(2, j);
                        }

                        j++;
                        if(hs_search >= tamanho){
                            if(mudarEstrategia){
                                //está na estratégia de sondagem linear
                                hs_search=0;//volta pro inicio do vetor
                            } else {
                                //está na estrategia de sondagem quadrática
                                hs_search = hs_search - tamanho;//pega o quanto passou e volta pra origem
                                if(hs_search >= tamanho){
                                    //não há mais como cair na lista, mudar de estratégia para endereçamento linear
                                    mudarEstrategia=true;
                                    hs_search=hs;//reseta o indice do vetor
                                    j=ji;//restaura indice da iteração
                                }
                            }
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
         * Obtem o numero de colisões pelo metodo quadratico
         * @return int
         */
        int getNumColisoesQuadraticas(){
            return numColisoesResolvidasQuad;
        }

        /**
         * Obtem o numero de colisões pelo metodo linear
         * @return int
         */
        int getNumColisoesLineares(){
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
        bool mudarEstrategia=false;
        int numColisoesResolvidasQuad=0;
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

#endif // ENDSONDAGEMQUADRATICA_H
