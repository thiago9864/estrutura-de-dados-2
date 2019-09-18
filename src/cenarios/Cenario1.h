/**
    Universidade Federal de Juiz de Fora
    Cenario1.h
    Propósito: Implementação do primeiro cenário da parte 1 do trabalho.

    @author Thiago Almeida
    @version 1.0 18/09/19
*/

#ifndef CENARIO_1_H
#define CENARIO_1_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"

using namespace std;

class Cenario1 : protected LeitorBase
{
public:
    Cenario1(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
        Log::getInstance().line("---- Iniciando Cenario 1 ----");
        Log::getInstance().line("Com N="+to_string(this->numTestes));
        Log::getInstance().semEndl("Sendo: [");
        for(int i=0; i<this->numTestes; i++){
            if(i>0){
                Log::getInstance().semEndl(", ");
            }
            Log::getInstance().semEndl(to_string(testes[i]));
        }
        Log::getInstance().semEndl("]");
        Log::getInstance().breakLine();
    };
    ~Cenario1(){
        testes=NULL;
        delete[] dataset;
        dataset=NULL;
    };

    
private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    UserReview *dataset;

    void carregaConfiguracao(){
        string line;
        ifstream arqEntrada;

        //abre o arquivo
        arqEntrada.open(this->getDiretorioArquivoDeEntrada()+nomeArquivoEntrada.c_str());

        //verifica se o arquivo foi aberto
        if (!arqEntrada || !arqEntrada.is_open())
        {
            cout << "Impossivel abrir o arquivo de configuração para leitura" << endl;
            exit(1); // sai do programa se nao conseguir abrir o arquivo
        }

        int linecount=0;
        while (getline(arqEntrada, line))
        {
            if(linecount==0){
                //a primeira linha é o total de testes
                numTestes = stoi(line);
                testes = new int[numTestes];
            } else {
                //as proximas linhas são o numero de elementos de cada teste
                testes[linecount-1] = stoi(line);
            }
            linecount++;
        }
    }

    void gerarTeste(int n){
        LeitorUserReviews *userReviews = new LeitorUserReviews(testes[n]);
        UserReview *dataset2 = userReviews->getDataset();
        delete userReviews;
    }
};
#endif // CENARIO_1_H