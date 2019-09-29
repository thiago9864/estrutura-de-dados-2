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
        EndSondagemQuadratica(int tam){
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
        void inserir(UserReview item){
            mudarEstrategia=false;//começa com a estratégia de rodar com a sondagem quadrática

            //constroi o k com o valor de id e o nome do usuario
            int k = item.id + somaAsciiFromString(item.user);
            int hs = funcaoHash(k, tamanho);

            //coloca no hashmap
            if(hashMap[hs].userReview.id == -1){
                //o espaço está vazio
                //inclui na posição gerada pela função hash uma referencia para o item do vetor
                hashMap[hs] = criaHashMapItem(hs, item);
            } else {
                //houve uma colisão
                //procura a próxima posição vazia na heap pelo metodo quadrático
                numColisoes++;//contabiliza a colisao
                int j=0;//conta a iteração
                int ji = -1;//guarda a posição do j ao entrar no quadratico
                int hs_search = hs;//posição no hash
                while(j<tamanho){
                    if(hashMap[hs_search].userReview.id == -1){
                        //a colisão foi resolvida
                        hashMap[hs_search] = criaHashMapItem(hs_search, item);
                        ji = -1;
                        break;
                    } else {
                        numColisoes++;//contabiliza a colisao
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
        int numColisoes=0;

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
