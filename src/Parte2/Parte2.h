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

        //////////// Categorias mais frequentes //////////

        Log::getInstance().line("\nIniciando teste de categorias mais frequentes\n");
        timerStart();//marca o tempo inicial

        //obtem a tabela hash
        HashItemSeparadoGameInfo *gamesInfo = hashCategorias->getHashMap();
        FreqCounter *fc = nullptr;
        FreqCounter *p = nullptr;
        int numCategorias=0;

        cout << "Constroi a lista encadeada de frequencia..." << endl;

        //circula toda a tabela em busca de jogos
        for(int i=0; i<hashCategorias->getTamanho();i++){
            HashItemSeparadoGameInfo g = gamesInfo[i];

            //abre o vetor de categorias
            vector<string> categorias = g.boardgamecategory;
            for(int i=0; i<categorias.size();i++){
                string categoria = categorias[i];
                if(fc == nullptr){
                    //se a lista de frequencia estiver vazia, coloca um item
                    fc = new FreqCounter(0, categoria);
                    numCategorias++;
                } else {
                    p = fc;
                    FreqCounter *fant = fc;
                    bool encontrado=false;
                    while(p!=nullptr){
                        //percorre a lista a procura do item
                        if(p->categoria == categoria){
                            //se encontrar, incrementa a frequencia
                            p->frequencia++;
                            encontrado=true;
                            break;
                        }
                        fant = p;
                        p = p->prox;
                    }
                    if(encontrado==false){
                        //se não encontrar, adiciona no fim da lista
                        fant->prox = new FreqCounter(0, categoria);
                        numCategorias++;
                    }
                }
            }
        }

        cout << "Passa pra um vetor..." << endl;

        //lista encadeada de frequencias pronta
        //transforma em um vetor pra ordenar
        FreqCounter *vfreq = new FreqCounter[numCategorias];
        p = fc;
        int i=0;
        while(p!=nullptr){
            FreqCounter fcn;
            fcn.id = p->frequencia;
            fcn.categoria = p->categoria;
            fcn.frequencia = p->frequencia;
            vfreq[i]=fcn;
            i++;
            p = p->prox;
        }

        int nCatMax = i;


        cout << "Ordena lista..." << endl;

        //ordena esse vetor usando o melhor do cenário 3
        RadixSort<FreqCounter> *radixSort = new RadixSort<FreqCounter>();
        radixSort->ordenar(vfreq, nCatMax);

        //mostra as nCategorias mais frequentes
        Log::getInstance().line("\nMostrando as "+to_string(nCategorias)+" categorias mais frequentes:");
        for(i=0; i<nCategorias; i++){
            int pos = nCatMax-i-1;
            Log::getInstance().line(to_string(vfreq[pos].frequencia) + " - " + vfreq[pos].categoria);
        }

        double tempo_teste = timerEnd();//marca o tempo final
        cout << endl;
        Log::getInstance().line("Concluido em "+to_string(tempo_teste)+" segundos.\n");
        cout << endl;

        //limpa a lista
        while(fc!=nullptr){
            p=fc->prox;
            delete fc;
            fc=p;
        }

        p = nullptr;
        fc = nullptr;
        delete radixSort;
        radixSort=nullptr;

        ////////////////////// Usuarios mais frequentes ////////////////////////

        Log::getInstance().line("\nIniciando teste de usuarios mais ativos\n");
        timerStart();//marca o tempo inicial

        //obtem a tabela hash
        HashItemSeparado *usersReview = hashAvaliacoes->getHashMap();
        fc = nullptr;
        p = nullptr;
        int numUsuarios=0;

        cout << "Constroi a lista encadeada de frequencia..." << endl;

        //circula toda a tabela em busca de avaliacoes
        for(int i=0; i<hashAvaliacoes->getTamanho();i++){
            HashItemSeparado h = usersReview[i];

            if(i%10000==0){
                cout << ((i / (float)hashAvaliacoes->getTamanho())*100.0) << "%" << endl;
            }
            //abre o encadeamento de itens
            HashItemSeparado *encad = h.prox;
            bool proprio_item=true;

            while(encad!=nullptr){
                string user = h.name;
                if(proprio_item==true){
                    user = h.name;
                } else {
                    user = encad->name;
                }

                if(fc == nullptr){
                    //se a lista de frequencia estiver vazia, coloca um item
                    fc = new FreqCounter(0, user);
                    numUsuarios++;
                } else {
                    p = fc;
                    FreqCounter *fant = fc;
                    bool encontrado=false;
                    while(p!=nullptr){
                        //percorre a lista a procura do item
                        if(p->categoria == user){
                            //se encontrar, incrementa a frequencia
                            p->frequencia++;
                            encontrado=true;
                            break;
                        }
                        fant = p;
                        p = p->prox;
                    }
                    if(encontrado==false){
                        //se não encontrar, adiciona no fim da lista
                        fant->prox = new FreqCounter(0, user);
                        numUsuarios++;
                    }
                }
                if(proprio_item==false){
                    encad = encad->prox;
                }
                proprio_item=false;
            }
        }

        cout << "Passa pra um vetor..." << endl;

        //lista encadeada de frequencias pronta
        //transforma em um vetor pra ordenar
        vfreq = new FreqCounter[numUsuarios];
        p = fc;
        i=0;
        while(p!=nullptr){
            FreqCounter fcn;
            fcn.id = p->frequencia;
            fcn.categoria = p->categoria;
            fcn.frequencia = p->frequencia;
            //cout << p->categoria << endl;
            vfreq[i]=fcn;
            i++;
            p = p->prox;
        }

        int nUsrMax = i;


        //cout << numUsuarios << endl;
        //cout << nUsrMax << endl;

        for(int j=0; j<nUsrMax; j++){
            //cout << vfreq[j].id << " - " << vfreq[j].categoria << endl;
        }

        cout << "Ordena lista..." << endl;

        //ordena esse vetor usando o melhor do cenário 3
        radixSort = new RadixSort<FreqCounter>();
        radixSort->ordenar(vfreq, nUsrMax);

        //mostra as nCategorias mais frequentes
        Log::getInstance().line("\nMostrando os "+to_string(nUsuarios)+" usuarios mais ativos (com mais avaliacoes):");
        for(i=0; i<nUsuarios; i++){
            int pos = nUsrMax-i-1;
            Log::getInstance().line(to_string(vfreq[pos].frequencia) + " - " + vfreq[pos].categoria);
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
    long long int tamHashAvaliacoes = 13170000;
    //long long int tamHashAvaliacoes = 200000;
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
