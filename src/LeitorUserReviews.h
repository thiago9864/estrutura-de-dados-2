/**
    Universidade Federal de Juiz de Fora
    LeitorUserReviews.h
    Propósito: Leitor do arquivo pre processado 'bgg-13m-reviews.csv'

    @version 1.0 18/08/19
*/
#ifndef LEITORUSERREVIEWS_H
#define LEITORUSERREVIEWS_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "UserReview.h"
#include "GameInfo.h"

using namespace std;

class LeitorUserReviews : protected LeitorBase
{
    public:

        LeitorUserReviews(int numRegistros){
            this->caminhoArquivo = this->getDiretorioPreprocessado()+"bgg-13m-reviews.csv";
            this->numRegistros = numRegistros;
            lerArquivo();
        };
        ~LeitorUserReviews(){};

        UserReview* getDataset(){
            return dataset;
        }

    private:
        UserReview *dataset;
        string caminhoArquivo;
        int numRegistros;
        string line;
        ifstream arqEntrada;
        bool headerProcessado;
        int ri, rf, rli, rlf;
        int idMin, idMax;

        void lerArquivo(){
            //abre o arquivo
            arqEntrada.open(caminhoArquivo.c_str());

            //verifica se o arquivo foi aberto
            if (!arqEntrada || !arqEntrada.is_open())
            {
                cout << "Impossivel abrir o arquivo 'bgg-13m-reviews.csv' para leitura";
                cout << "Verifique a pasta 'datasets' pela pasta 'preprocessado'. Nela deve estar o arquivo" << endl;
                exit(1); // sai do programa se nao conseguir abrir o arquivo
            }

            //gera a semente do processo randomico
            this->gerarSemente();

            headerProcessado=false;

            //calcula pulos de leitura maximos
            int numPulos = 0;
            int maxPulo = (5000000 - numRegistros) / numRegistros;
            //int ind=0;

            while (getline(arqEntrada, line))
            {
                vector<string> result = explode(line, ',');

                //obtem o numero de colunas e extrai o header
                if(headerProcessado==false){
                    headerProcessado=true;

                    //inicia o vetor de objetos do dataset
                    dataset = new UserReview[numRegistros];

                    //guarda o id minimo e máximo do dataset
                    idMin=999999999;
                    idMax=-999999999;
                    rli=numRegistros/2;//marca o tamanho maximo da partição inicial [0,meio-1]
                    rlf=numRegistros-rli;//marca o tamanho maximo da partição final [meio, fim)-1]
                    ri=0;//aponta pro inicio da partição inicial
                    rf=0;//aponta pro inicio da partição final
                } else {
                    if(numPulos == 0){
                        //calcula o pulo
                        numPulos = getRand(maxPulo);
                        //cout << "linha: " << ind << endl;

                        //cria o objeto
                        UserReview u;
                        u.id = stoi(result[0]);
                        u.user = result[1];
                        u.rating = stof(result[2]);
                        float rnd = getRand(10);
                        //cout << rnd << endl;
                        if(rnd > 5 && ri<rli){
                            //se o numero aleatorio for maior que 5
                            //coloca o numero na partição inicial
                            dataset[ri]=u;
                            ri++;//incrementa o indice da partição
                        } else if((rf+rli) < numRegistros) {
                            //se o numero aleatorio for menor ou igual a 5
                            //coloca o numero na partição final
                            dataset[rf+rli]=u;
                            rf++;//incrementa o indice da partição
                        }

                        //id minimo
                        if(u.id < idMin){
                            idMin = u.id;
                        }
                        //id maximo
                        if(u.id > idMax){
                            idMax = u.id;
                        }
                        //cout << (ri + rf) << endl;
                        if((ri + rf) >= numRegistros){
                            //quando os ponteiros de inicio e fim forem iguais
                            //o vetor foi totalmente preenchido
                            break;
                        }
                    } else {
                        //pula os numeros
                        numPulos--;
                    }
                }
                //ind++;
            }

            if(arqEntrada.is_open()){
                arqEntrada.close();
            }
        }
};

#endif // LEITORUSERREVIEWS_H
