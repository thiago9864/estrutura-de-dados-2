/**
    Universidade Federal de Juiz de Fora
    Parte.h
    Propósito: Classe pra rodar a parte 2 do trabalho

    @author Luan Ciribelli
    @version 1.0 10/10/19
*/


#ifndef SRC_PARTE2_H
#define SRC_PARTE2_H
#include "HashAvaliacoes.h"
#include "HashCategorias.h"
#include "../LeitorBase.h"
#include "../UserReview.h"
#include "../GameInfo.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parte2 : protected LeitorBase
{

public:

    Parte2(string nomeArquivoSaida){
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);

        carregaDadosTeste();
    };
    /*
    Parte2(UserReview* vet[],int tam,int N ){
        this.tam=tam;
        this.numerodecategoriasaretornar=N;
        hash1=new HashEncSeparado;
        a=new LeitorBase;
        a.gerarSemente();
    }*/

    /**
    * Metodo que vai inicializar o controle da parte 2, que é essencialmente um
    * quinto cenário de teste
    */
    void realizaTeste(){
        string userInput;

        cout << "Digite o numero de categorias para pesquisar a frequencia:" << endl;
        cin >> userInput;
        nCategorias = stoi(userInput);

        cout << "Digite o numero de usuarios para pesquisar a frequencia:" << endl;
        cin >> userInput;
        nUsuarios = stoi(userInput);

        cout << "Realizando os testes..." << endl;

        //////////// Colocar a partir daqui o código dos testes //////////////////////


    }

private:

    int nCategorias;
    int nUsuarios;
    string nomeArquivoEntrada;
    long long int tamHashAvaliacoes = 13170000;
    int tamHashCategorias = 17060;
    HashAvaliacoes *hashAvaliacoes = NULL;//tabela hash de objetos do dataset de avaliacoes
    HashCategorias *hashCategorias = NULL;//tabela hash de objetos do dataset de categorias



    /**
    * Carrega o vetor do tamanho especificado no arquivo da configuração de teste
    * @param qtdDadosTeste Tamanho do vetor que vai ser obtido
    */
    void carregaDadosTeste(){

        cout << "Iniciando a leitura dos arquivos" << endl;

        LeitorGameInfo *gamesInfo = new LeitorGameInfo(tamHashCategorias);//tamanho total do dataset
        cout << "Conteudo do arquivo 'games_detailed_info.csv' lido" << endl;
        LeitorUserReviews *userReviews = new LeitorUserReviews(tamHashAvaliacoes);//tamanho total do dataset
        cout << "Conteudo do arquivo 'bgg-13m-reviews.csv' lido." << endl;
        UserReview* dts = userReviews->getDataset();

        if(hashAvaliacoes != NULL){
            //limpa memoria se tiver alguma coisa
            delete hashAvaliacoes;
        }
        if(hashCategorias != NULL){
            //limpa memoria se tiver alguma coisa
            delete hashCategorias;
        }



        hashAvaliacoes = new HashAvaliacoes(tamHashAvaliacoes);
        hashCategorias = new HashCategorias(tamHashCategorias);

        UserReview *dataset_users = userReviews->getDataset();
        GameInfo *dataset_categorias = gamesInfo->getDataset();

        //adiciona a tabela hash
        for(int i=0; i<tamHashAvaliacoes; i++){
            hashAvaliacoes->inserir(dataset_users[i]);
        }
        cout << "Insercao no hash de avaliacoes concluida" << endl;

        //adiciona a tabela hash
        for(int i=0; i<tamHashCategorias; i++){
            hashCategorias->inserir(dataset_categorias[i]);
        }

        cout << "Insercao no hash de categorias concluida" << endl;

        delete userReviews;//libera memória do leitor
        delete gamesInfo;//libera memória do leitor
    }

};




#endif //SRC_PARTE2_H
