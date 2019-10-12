/**
    Universidade Federal de Juiz de Fora
    Cenario4.h
    Propósito: Implementação do quarto cenário da parte 1 do trabalho.

    @author Thiago Almeida, Lucas Ribeiro
    @version 2.0 06/10/19
*/

#ifndef CENARIO_4_H
#define CENARIO_4_H
#include <iostream>
#include <string>

#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"
#include "../hash/HashMaps/HashEncLinear.h"
#include "../hash/HashMaps/HashEncQuadratico.h"
#include "../hash/HashMaps/HashEncSeparado.h"
#include "../hash/HashMaps/HashEndCoalescido.h"
#include "../hash/HashMaps/HashReHash.h"

using namespace std;

class Cenario4 : protected LeitorBase
{
public:
    Cenario4(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
    };

    ~Cenario4(){
        testes=NULL;
        delete[] dataset;
        dataset=NULL;
    };

    /**
    * Metodo principal do teste
    */
    void realizaTeste(){

        uint64_t inicio;

        numAlgoritmos = 5;
        algoritmos = new string[numAlgoritmos];
        algoritmos[0] = "Enderecamento por Sondagem Linear";
        algoritmos[1] = "Enderecamento por Sondagem Quadratica";
        algoritmos[2] = "Enderecamento por Duplo Hash";
        algoritmos[3] = "Encadeamento Separado";
        algoritmos[4] = "Encadeamento Coalescido";

        //cria os vetores de teste
        numeroDeComparacores = new uint64_t*[numAlgoritmos];
        gastoDeMemoria = new uint64_t*[numAlgoritmos];

        //inicia os vetores de teste com zero
        for(int a=0; a<numAlgoritmos; a++){
            temposDeExecucao[a] = new double[numTestes];
            numeroDeComparacores[a] = new uint64_t[numTestes];
            gastoDeMemoria[a] = new uint64_t[numTestes];
            for(int t=0; t<numTestes; t++){
                temposDeExecucao[a][t] = 0;
                numeroDeComparacores[a][t] = 0;
                gastoDeMemoria[a][t] = 0;
            }
        }

        //preenche header do csv
        Log::getInstance().lineArquivo("Teste,Número de Testes,Algoritmo,Número de Comparações,Gasto de Memoria");

        //Loop entre os testes do arquivo de configuração
        for(int t=0; t<numTestes; t++){

            cout << endl << "Executando o teste com " << testes[t] << " registros" << endl;
            sizeDataset = testes[t];//marca aqui o tamanho do vetor de ints do teste

            //obtem dados do teste com a semente atual
            carregaDadosTeste(sizeDataset);

            int* copiaLocal;//copia do vetor de testes usada no algoritmo
            double tempo_teste;

            ////////// Enderecamento por Sondagem Linear //////////
]

            //debug - nome do algoritmo
            cout << "- Enderecamento por Sondagem Linear" << endl;

            //inicialização do algoritmo
            auto* encLinear = new HashEncLinear(sizeDataset);


            // Iniciando as inserções
            for(int i = 0; i<sizeDataset; i++){
                encLinear->inserir(dataset[i]);
            }

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;//pegar do algoritmo
            gastoDeMemoria[0][t] = 0;//pegar do algoritmo
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete algoritmo; // colocar variavel do algoritmo aqui
            delete[] copiaLocal;
            //algoritmo = NULL; // colocar variavel do algoritmo aqui
            copiaLocal = NULL;

            ////////// Enderecamento por Sondagem Quadratica //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocal = copiaLocalVetorInt();

            //debug - Salvar o vetor fonte
            //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //debug - nome do algoritmo
            cout << "- Enderecamento por Sondagem Quadratica" << endl;

            //inicialização do algoritmo

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;//pegar do algoritmo
            numeroDeTrocas[0][t] = 0;//pegar do algoritmo
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete algoritmo; // colocar variavel do algoritmo aqui
            delete[] copiaLocal;
            //algoritmo = NULL; // colocar variavel do algoritmo aqui
            copiaLocal = NULL;

            ////////// Enderecamento por Duplo Hash //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocal = copiaLocalVetorInt();

            //debug - Salvar o vetor fonte
            //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //debug - nome do algoritmo
            cout << "- Enderecamento por Duplo Hash" << endl;

            //inicialização do algoritmo

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;//pegar do algoritmo
            numeroDeTrocas[0][t] = 0;//pegar do algoritmo
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete algoritmo; // colocar variavel do algoritmo aqui
            delete[] copiaLocal;
            //algoritmo = NULL; // colocar variavel do algoritmo aqui
            copiaLocal = NULL;

            ////////// Encadeamento Separado //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocal = copiaLocalVetorInt();

            //debug - Salvar o vetor fonte
            //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //debug - nome do algoritmo
            cout << "- Encadeamento Separado" << endl;

            //inicialização do algoritmo

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;//pegar do algoritmo
            numeroDeTrocas[0][t] = 0;//pegar do algoritmo
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete algoritmo; // colocar variavel do algoritmo aqui
            delete[] copiaLocal;
            //algoritmo = NULL; // colocar variavel do algoritmo aqui
            copiaLocal = NULL;

            ////////// Encadeamento Coalescido //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocal = copiaLocalVetorInt();

            //debug - Salvar o vetor fonte
            //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //debug - nome do algoritmo
            cout << "- Encadeamento Coalescido" << endl;

            //inicialização do algoritmo

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;//pegar do algoritmo
            numeroDeTrocas[0][t] = 0;//pegar do algoritmo
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete algoritmo; // colocar variavel do algoritmo aqui
            delete[] copiaLocal;
            //algoritmo = NULL; // colocar variavel do algoritmo aqui
            copiaLocal = NULL;

        }
    }

private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    UserReview *dataset = NULL;//vetor de objetos do dataset
    int sizeDataset = NULL;
    double** temposDeExecucao;
    uint64_t** numeroDeComparacores;
    uint64_t** gastoDeMemoria;
    string *algoritmos;
    int numAlgoritmos;

    void salvaLinhaResultado(int indice_algoritmo, int indice_teste){
        string linha = "";

        linha += to_string(indice_teste) + ",";
        linha += to_string(testes[indice_teste]) + ",";
        linha += algoritmos[indice_algoritmo] + ",";
        linha += to_string(temposDeExecucao[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(numeroDeComparacores[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(gastoDeMemoria[indice_algoritmo][indice_teste]);

        Log::getInstance().lineArquivo(linha);
    }

    void carregaDadosTeste(int qtdDadosTeste){

        LeitorUserReviews *userReviews = new LeitorUserReviews(qtdDadosTeste);
        UserReview* dts = userReviews->getDataset();

        if(dataset != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] dataset;
        }
        if(vetorInt != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] vetorInt;
        }

        this->dataset = new UserReview[qtdDadosTeste];
        this->vetorInt = new int[qtdDadosTeste];

        //monta vetor de inteiros
        for(int i=0; i<qtdDadosTeste; i++){
            dataset[i] = dts[i];
            vetorInt[i] = dts[i].id;
        }

        //debug - Salvar o vetor fonte
        //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);


        delete userReviews;//libera memória do leitor
    }



    /**
    * Carrega o arquivo de configuração do teste, que está na pasta 'entradas'
    */
    void carregaConfiguracao(){
        string line;
        ifstream arqEntrada;

        //abre o arquivo
        arqEntrada.open(this->getDiretorioArquivoDeEntrada()+nomeArquivoEntrada.c_str());

        //verifica se o arquivo foi aberto
        if (!arqEntrada || !arqEntrada.is_open())
        {
            cout << "Impossivel abrir o arquivo de configuração para leitura";
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

    /**
    * Carrega o vetor do tamanho especificado no arquivo da configuração de teste
    * @param qtdDadosTeste Tamanho do vetor que vai ser obtido
    */
    void carregaDadosTeste(int qtdDadosTeste){

        LeitorUserReviews *userReviews = new LeitorUserReviews(qtdDadosTeste);
        UserReview* dts = userReviews->getDataset();

        if(dataset != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] dataset;
        }
        this->dataset = new int[qtdDadosTeste];

        //monta vetor de inteiros
        for(int i=0; i<qtdDadosTeste; i++){
            dataset[i] = dts[i].id;
        }
        delete userReviews;//libera memória do leitor
    }

    /**
    * Faz uma cópia do vetor de inteiros.
    * Isso é usado porque os algoritmos modificam o vetor
    * @return *int
    */
    int* copiaLocalVetorInt(){
        int* copia = new int[sizeDataset];
        for(int i=0; i<sizeDataset; i++){
            //copia[i] = dataset[i].id;
            copia[i] = dataset[i];
        }
        return copia;
    }


    /**
    * Debug: Imprime o vetor de inteiros
    * @param vetor Vetor de inteiros
    * @param tam Tamanho do vetor
    */
    void imprimeVetor(int *vetor, int tam){
        cout << "[";
        for(int i=0; i<tam; i++){
            if(i>0){
                cout << ", ";
            }
            cout << vetor[i];
        }
        cout << "]" << endl;
    }

    /**
    * Debug: Salva o vetor de inteiros em um arquivo
    * @param filename Nome do arquivo
    * @param vetor Vetor de inteiros
    * @param tam Tamanho do vetor
    */
    void salvaVetor(string filename, int* vetor, int tam){
        ofstream arqSaida;
        //cout << caminhoArqSaida << endl;
        //abre arquivo para saida
        arqSaida.open("saidas"+getDirSep()+filename.c_str(), fstream::in | fstream::out | fstream::trunc);

        //verifica se o arquivo foi aberto
        if (!arqSaida || !arqSaida.is_open())
        {
            cout << "Impossivel abrir o arquivo de saida para escrita" << endl;
            cout << "Com o arquivo: " << filename << endl;
            cout << "O diretorio 'saidas' foi criado no diretorio raiz (o que esta a main.cpp) ?" << endl;
            exit(1); // sai do programa se nao conseguir abrir o arquivo
        }

        for(int i=0; i<tam; i++){
            arqSaida << vetor[i] << endl;
        }

        if(arqSaida.is_open()){
            arqSaida.close();
        }
    }
};
#endif // CENARIO_4_H
