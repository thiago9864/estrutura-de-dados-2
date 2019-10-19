/**
    Universidade Federal de Juiz de Fora
    LeitorGameInfo.h
    Propósito: Leitor do arquivo pre processado'games_detailed_info.csv'

    @version 1.0 19/08/19
*/
#ifndef LEITORGAMEINFO_H
#define LEITORGAMEINFO_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "LeitorBase.h"
#include "GameInfo.h"
#include "LeitorBase.h"

using namespace std;

class LeitorGameInfo : protected LeitorBase
{
    public:

        LeitorGameInfo(int numRegistros){
            this->caminhoArquivo = this->getDiretorioPreprocessado()+"games_detailed_info.csv";
            this->numRegistros = numRegistros;
            lerArquivo();
        };
        ~LeitorGameInfo(){};

        GameInfo* getDataset(){
            return dataset;
        }

    private:

        GameInfo *dataset;
        string caminhoArquivo;
        int numRegistros;
        string line;
        ifstream arqEntrada;
        bool headerProcessado;
        int linePos;

        void lerArquivo(){
            //abre o arquivo
            arqEntrada.open(caminhoArquivo.c_str());

            //verifica se o arquivo foi aberto
            if (!arqEntrada || !arqEntrada.is_open())
            {
                cout << "Impossivel abrir o arquivo 'games_detailed_info.csv' para leitura";
                cout << "Verifique a pasta 'datasets' pela pasta 'preprocessado'. Nela deve estar o arquivo" << endl;
                cout << "Se o arquivo estiver na pasta, verifique a classe 'LeitorBase.h' para o caminho correto no"<<endl;
                cout << "metodo 'getDiretorioPreprocessado()'." << endl;
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
                    dataset = new GameInfo[numRegistros];
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
                    GameInfo g;
                    g.id = stoi(result[0]);

                    if(result.size()>1){
                        string cat = result[1];
                        //registro com categorias
                        g.boardgamecategory = explode(cat, '|');
                    }

                    dataset[pos] = g;
                    //cout << "--" << endl;
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

#endif // LEITORGAMEINFO_H
