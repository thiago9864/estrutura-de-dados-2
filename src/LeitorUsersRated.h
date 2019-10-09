/**
    Universidade Federal de Juiz de Fora
    LeitorUsersRated.h
    Propósito: Leitor do arquivo pre processado '2019-05-02.csv'

    @version 1.0 21/08/19
*/
#ifndef LEITORUSERSRATED_H
#define LEITORUSERSRATED_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "UsersRated.h"

using namespace std;

class LeitorUsersRated : protected LeitorBase
{
    public:

        LeitorUsersRated(int numRegistros){
            this->caminhoArquivo = this->getDiretorioPreprocessado()+"2019-05-02.csv";
            this->numRegistros = numRegistros;
            lerArquivo();
        };
        ~LeitorUsersRated(){};

        UsersRated* getDataset(){
            return dataset;
        }

    private:
        UsersRated *dataset;
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
                cout << "Impossivel abrir o arquivo '2019-05-02.csv' para leitura";
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
                    dataset = new UsersRated[numRegistros];
                    for(int i=0; i<numRegistros; i++){
                        dataset[i].id=-1;
                    }

                } else {

                    //gera posicao aleatoria
                    unsigned int pos = 0;
                    while(dataset[pos].id!=-1){
                        pos=getRand(numRegistros);
                    }

                    //cria o objeto
                    UsersRated u;
                    u.id = stoi(result[0]);
                    u.usersRated = stoi(result[1]);
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

#endif // LEITORUSERSRATED_H
