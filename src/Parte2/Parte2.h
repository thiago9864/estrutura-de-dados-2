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
#include "FreqCounter.h"
#include "../LeitorBase.h"
#include "../UserReview.h"
#include "../GameInfo.h"
#include "../ordenacao/RadixSort.h"
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

        /*
                //concatena todas as categorias em uma só string pra gerar o hash


        */

        FreqCounter *vfreq;

        //////////// Categorias mais frequentes //////////

        Log::getInstance().line("\nIniciando teste de categorias mais frequentes\n");
        timerStart();//marca o tempo inicial

        //obtem a tabela hash
        HashItemSeparadoParte2 *gamesInfo = hashCategorias->getHashMap();

        cout << "Passa pra um vetor..." << endl;

        int nCatMax = hashCategorias->getTamanho();
        vfreq = new FreqCounter[nCatMax];

        //faz uma cópia do vetor da hashtable pra ser ordenado sem influenciar a tabela
        for(int i=0; i<nCatMax; i++){
            FreqCounter fc;
            fc.id = gamesInfo[i].frequencia;
            fc.frequencia = gamesInfo[i].frequencia;
            fc.conteudo = gamesInfo[i].conteudo;
            vfreq[i] = fc;
        }

        cout << "Ordena lista..." << endl;

        //ordena esse vetor usando o melhor do cenário 3
        RadixSort<FreqCounter> *radixSort = new RadixSort<FreqCounter>();
        radixSort->ordenar(vfreq, nCatMax);

        //mostra as nCategorias mais frequentes
        Log::getInstance().line("\nMostrando as "+to_string(nCategorias)+" categorias mais frequentes:");
        for(int i=0; i<nCategorias; i++){
            int pos = nCatMax-i-1;
            Log::getInstance().line(to_string(vfreq[pos].frequencia) + " - " + vfreq[pos].conteudo);
        }

        double tempo_teste = timerEnd();//marca o tempo final
        cout << endl;
        Log::getInstance().line("Concluido em "+to_string(tempo_teste)+" segundos.\n");
        cout << endl;

        //limpa memória usada
        delete[] vfreq;
        delete radixSort;
        radixSort=nullptr;
        vfreq = nullptr;

        ////////////////////// Usuarios mais frequentes ////////////////////////

        Log::getInstance().line("\nIniciando teste de usuarios mais ativos\n");
        timerStart();//marca o tempo inicial

        //obtem a tabela hash
        HashItemSeparadoParte2 *userReviews = hashAvaliacoes->getHashMap();


        cout << "Passa pra um vetor..." << endl;

        int nUsrMax = hashAvaliacoes->getTamanho();
        vfreq = new FreqCounter[nUsrMax];

        //faz uma cópia do vetor da hashtable pra ser ordenado sem influenciar a tabela
        for(int i=0; i<nUsrMax; i++){
            FreqCounter fc;
            fc.id = userReviews[i].frequencia;
            fc.frequencia = userReviews[i].frequencia;
            fc.conteudo = userReviews[i].conteudo;
            vfreq[i] = fc;
        }

        cout << "Ordena lista..." << endl;

        //ordena esse vetor usando o melhor do cenário 3
        radixSort = new RadixSort<FreqCounter>();
        radixSort->ordenar(vfreq, nUsrMax);

        //mostra as nCategorias mais frequentes
        Log::getInstance().line("\nMostrando os "+to_string(nUsuarios)+" usuarios mais ativos (com mais avaliacoes):");
        for(int i=0; i<nUsuarios; i++){
            int pos = nUsrMax-i-1;
            Log::getInstance().line(to_string(vfreq[pos].frequencia) + " - " + vfreq[pos].conteudo);
        }

        tempo_teste = timerEnd();//marca o tempo final
        cout << endl;
        Log::getInstance().line("Concluido em "+to_string(tempo_teste)+" segundos.\n");
        cout << endl;
    }

private:

    int nCategorias;
    int nUsuarios;
    string nomeArquivoEntrada;
    //long long int tamHashAvaliacoes = 13170000; //não usado por restrições de memória do pc de teste
    long long int tamHashAvaliacoes = 10000000;
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
            hashAvaliacoes->inserir(dataset_users[i].user);
            if(i%1000000==0){
                cout << "Inserindo avaliacoes: " << (i*100/(float)tamHashAvaliacoes) << " %" << endl;
            }
        }
        cout << "Insercao no hash de avaliacoes concluida" << endl;

        //adiciona a tabela hash
        for(int i=0; i<tamHashCategorias; i++){
            vector<string> categorias = dataset_categorias[i].boardgamecategory;
            for(int i=0; i<categorias.size();i++){
                hashCategorias->inserir(categorias[i]);
            }
        }

        cout << "Insercao no hash de categorias concluida" << endl;

        delete userReviews;//libera memória do leitor
        delete gamesInfo;//libera memória do leitor
    }

};




#endif //SRC_PARTE2_H
