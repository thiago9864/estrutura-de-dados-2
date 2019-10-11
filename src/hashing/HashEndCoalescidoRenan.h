/**
    Universidade Federal de Juiz de Fora
    HashEndCoalescido.h
    Propósito: Implementação do algoritmo de Hash por endereçamento coalescido.
    @author Thiago de Almeida,Renan Nunes da Costa Gonçalves
    @version 1.0 18/09/19
*/

#ifndef HASHENDCOALESCIDO_H
#define HASHENDCOALESCIDO_H

#include <iostream>
#include "../UserReview.h"

using namespace std;


class HashMapItem {
    public:
        int hs;
        UserReview userReview;
};

class HashEndCoalescidoRenan {

    private:
        int tamanho; //Tamanho Original dos dados
        int m; //Tamanho da Tabela Hash
        int numeroComparacoes; //Número de Comparações feitas
        int numeroPosicoesPreenchidas; //Número de Posições Preenchidas a tabela
        UserReview* vetor; // vetor de valores desejados
        HashMapItem *hashMap;

    public:
        HashEndCoalescidoRenan(UserReview* vetor, int tam)
        {
            this->vetor = vetor;
            this->tamanho = tam;
            this->numeroComparacoes = 0;
            this->numeroPosicoesPreenchidas = 0;
            
            this->m = encontraPrimo(this->tamanho);

         
            vetor = new UserReview[this->tamanho];
            

            for(int i = 0; i < this->m; i++)
            {
                hashMap[i] = criaHashMapItem(-2, criaUserReview(-1,"",0));
            }
        };

        void inserir(UserReview item)
        {
            int k = item.id + somaAsciiFromString(item.user);
            int hs = funcaoHash(k,m);

            if(posicaoVazia(hs))
            {
                hashMap[hs] = criaHashMapItem(hs, item);
                hashMap[hs].userReview.id == -1;
            } else {
                int novaPos;
                int posAnterior = hs;
                
                if(hashMap[hs].userReview.id != -1)
                {
                    novaPos = m-1;
                    this->numeroComparacoes++;
                } else {
                    int posAtual = hs;
                    int posProx;

                    while(hashMap[posAtual].userReview.id != -1)
                    {
                        posAnterior = posAtual;
                        posProx = hashMap[posAtual].userReview.id;
                        posAtual = posProx;
                        this->numeroComparacoes++;
                    }
                    novaPos = posAtual - 1;
                }

                do {
                    if(novaPos <= 0)
                        novaPos = m - 1;
                    novaPos--;
                    this->numeroComparacoes++;
                } while (hashMap[hs].userReview.id != -2);
                
                hashMap[posAnterior].userReview.id == -novaPos;
                hashMap[posAnterior].userReview.id == -1;
                hashMap[novaPos] = criaHashMapItem(novaPos, item);

                numeroPosicoesPreenchidas++;

            }

            
        };


        void inserirAux(UserReview item, int k)
        {
            if(this->numeroPosicoesPreenchidas >= m)
                cout << "Tabela Cheia!";
            else 
            {
                if(k == NULL)
                {
                    return;
                }
            }

            int pos = funcaoHash(k,m);
        };

         bool posicaoVazia(int hs){
            numeroComparacoes++;
            return hashMap[hs].userReview.id == -2;
        }

        ~HashEndCoalescidoRenan()
        {
            delete [] vetor;
            delete [] hashMap;
            
        };


        int encontraPrimo(int x)
        {
            int nNew = ((x * 2 + 3) - 2) / 2;
            
            bool* colore = new bool [nNew+1];

            for(int k = 0; k < nNew+1;k++)
            {
                colore[k] = false;
            }

            int primo = x;

            for(int i = 1; i <= nNew; i++)
            {
                for(int j = i;(i + j + 2 * i * j) <= nNew; j++)
                {
                    try{
                        colore[i + j + 2 * i * j] = true;
                    } catch(exception e)
                    {
                        break;
                    }
                }

                for (int k=x/2; k < nNew+1; k++) 
                {
                    if (colore[k] == false && k * 2 + 1 > m) 
                    {
                        primo = k * 2 + 1;
                        break;
                    }

                }
            }

            return primo;    
        };

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

        
        

       

};



#endif // HASHENDCOALESCIDO_H
