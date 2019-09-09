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

using namespace std;

class LeitorGameInfo : protected LeitorBase
{
    public:

        LeitorGameInfo(int numRegistros){
            this->caminhoArquivo = "datasets"+getDirSep()+"preprocessado"+getDirSep()+"bgg-13m-reviews.csv";
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
        int ri, rf;
        int idMin, idMax;

        void lerArquivo(){
            //abre o arquivo
            arqEntrada.open(caminhoArquivo.c_str());

            //verifica se o arquivo foi aberto
            if (!arqEntrada || !arqEntrada.is_open())
            {
                cout << "Impossivel abrir o arquivo para leitura";
                exit(1); // sai do programa se nao conseguir abrir o arquivo
            }
            
            headerProcessado=false;

            while (getline(arqEntrada, line))
            {
                vector<string> result = explode(line, ',');

                //obtem o numero de colunas e extrai o header
                if(headerProcessado==false){
                    headerProcessado=true;

                    //inicia o vetor de objetos do dataset
                    dataset = new GameInfo[numRegistros];

                    //guarda o id minimo e máximo do dataset
                    idMin=99999999;
                    idMax=-99999999;
                    ri=0;//aponta pro inicio do dataset
                    rf=numRegistros-1;//aponta pro fim do dataset
                } else {

                    //cria o objeto
                    GameInfo g;
                    g.id = stoi(result[0]);
                    g.boardgamecategory = explode(result[1], '|');

                    if(getRand(10) > 5){
                        //se o numero aleatorio for maior que 5
                        //coloca o numero do final pro inicio
                        dataset[rf]=g;
                        rf--;//decrementa o ponteiro do fim
                    } else {
                        //se o numero aleatorio for menor ou igual a 5
                        //coloca o numero do inicio pro fim
                        dataset[ri]=g;
                        ri++;//incrementa o ponteiro do inicio
                    }

                    //id minimo
                    if(g.id < idMin){
                        idMin = g.id;
                    }
                    //id maximo
                    if(g.id > idMax){
                        idMax = g.id;
                    }

                    if(ri > rf){
                        //quando os ponteiros de inicio e fim forem iguais
                        //o vetor foi totalmente preenchido
                        break;
                    }     
                }
            }

            if(arqEntrada.is_open()){
                arqEntrada.close();
            }
        }
};

#endif // LEITORGAMEINFO_H