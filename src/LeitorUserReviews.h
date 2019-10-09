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
            int linhas_inseridas=0;
            bool insuficiente=true;

            while (getline(arqEntrada, line))
            {
                vector<string> result = explode(line, ',');

                //obtem o numero de colunas e extrai o header
                if(headerProcessado==false){
                    headerProcessado=true;

                    //inicia o vetor de objetos do dataset com ids=-1
                    dataset = new UserReview[numRegistros];
                    for(int i=0; i<numRegistros; i++){
                        dataset[i].id=-1;
                    }

                } else {
                    //gera posicao aleatoria
                    unsigned int pos = 0;
                    while(dataset[pos].id!=-1){
                        pos=getRand(numRegistros);
                    }

                    //cria objeto na posicao
                    UserReview u;
                    u.id = stoi(result[0]);
                    u.user = result[1];
                    u.rating = stof(result[2]);
                    dataset[pos] = u;

                    //conta linhas inseridas
                    linhas_inseridas++;

                    //para inserção quando completo
                    if(linhas_inseridas>=numRegistros){
                        insuficiente=false;
                        break;
                    }
                }
            }

            if(insuficiente){
                cout << "O numero de registros solicitado e maior que o numero de registros do dataset" << endl;
                exit(1);
            }

            if(arqEntrada.is_open()){
                arqEntrada.close();
            }
        }
};

#endif // LEITORUSERREVIEWS_H
