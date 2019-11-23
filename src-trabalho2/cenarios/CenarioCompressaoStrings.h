/**
    Universidade Federal de Juiz de Fora
    CenarioCompressaoStrings.h
    Propósito: Implementação do cenario da arvore rubro-negra do trabalho 2.

    @author Thiago Almeida, Lucas Ribeiro
    @version 1.0 18/10/19
*/

#ifndef CENARIOCOMPRESSAOSTRINGS_H
#define CENARIOCOMPRESSAOSTRINGS_H
#include <iostream>
#include <string>
#include "../compressao/Huffman.h"

#include "../LeitorGameInfo.h"
#include "../Log.h"
#include "../LeitorBase.h"
#include "../compressao/LZW.h"

using namespace std;

class CenarioCompressaoStrings : protected LeitorBase
{
public:
    CenarioCompressaoStrings(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
    };

    ~CenarioCompressaoStrings(){
        testes=NULL;
        delete[] datasetObjetos;
        datasetObjetos=NULL;
    };

    /**
    * Metodo principal do teste
    */
    void realizaTeste(){

        uint64_t inicio;

        numAlgoritmos = 2;
        algoritmos = new string[numAlgoritmos];
        algoritmos[0] = "Huffman";
        algoritmos[1] = "LZW";

        //cria os vetores de teste
        temposDeExecucao = new double*[numAlgoritmos];
        taxaDeCompressao = new double*[numAlgoritmos];
        taxaDeCompressaoEmDisco = new double*[numAlgoritmos];
        armazenamentoEmDisco = new double*[numAlgoritmos];

        //inicia os vetores de teste com zero
        for(int a=0; a<numAlgoritmos; a++){
            temposDeExecucao[a] = new double[numTestes];
            taxaDeCompressao[a] = new double[numTestes];
            taxaDeCompressaoEmDisco[a] = new double[numTestes];
            armazenamentoEmDisco[a] = new double[numTestes];
            for(int t=0; t<numTestes; t++){
                temposDeExecucao[a][t] = 0;
                taxaDeCompressao[a][t] = 0;
                taxaDeCompressaoEmDisco[a][t] = 0;
                armazenamentoEmDisco[a][t] = 0;
            }
        }

        //preenche header do csv
        Log::getInstance().lineArquivo("Número de Testes,Algoritmo,Tempo de Execução,Taxa de Compressão,Taxa de Compressão Em Disco,Armazenamento Em Disco");

        //Loop entre os testes do arquivo de configuração
        for(int t=0; t<numTestes; t++){

            cout << endl << "Executando o teste com " << testes[t] << " registros" << endl;
            tamDataset = testes[t];//marca aqui o tamanho do vetor de ints do teste

            //obtem dados do teste com a semente atual
            carregaDadosTeste(tamDataset);

            //cópias de teste
            GameInfo* copiaLocalObjetos;
            int* copiaLocalInteiro;

            double tempo_teste;

            ////////// Algoritmo Huffman //////////

            //faz uma copia do dataset
            copiaLocalObjetos = copiaLocalVetor<GameInfo>(datasetObjetos, tamDataset);

            //monta string para compressão
            string textoParaComprimir;
            for(int i=0; i<tamDataset; i++){
                textoParaComprimir += copiaLocalObjetos[i].description + "\n";
            }

            //debug - nome do algoritmo
            cout << algoritmos[0] << endl;

            //inicialização do algoritmo
            auto huffman = new Huffman();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            huffman->compactar(textoParaComprimir);

            tempo_teste = timerEnd();//marca o tempo final

            //salva em disco para obter a taxa de compressão de armazenamento
            huffman->salvarEmDisco(getDiretorioTempCompressao() + "huffman_original" + to_string(tamDataset) + ".txt",
                                   getDiretorioTempCompressao() + "huffman_compactado" + to_string(tamDataset) + ".txt",
                                   getDiretorioTempCompressao() + "huffman_tabela_freq" + to_string(tamDataset) + ".txt"
                                   );

            huffman->calculaEstatisticas(getDiretorioTempCompressao() + "huffman_original" + to_string(tamDataset) + ".txt",
                                         getDiretorioTempCompressao() + "huffman_compactado" + to_string(tamDataset) + ".txt");


            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            taxaDeCompressao[0][t] = 0;huffman->geraTaxaCompressao();
            taxaDeCompressaoEmDisco[0][t] = 0; huffman->geraTaxaCompressaoEmDisco();
            armazenamentoEmDisco[0][t] = 0; huffman->geraTamanhoCompactadoEmDisco();
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete huffman;
            delete[] copiaLocalObjetos;
            //huffman = NULL;
            copiaLocalObjetos = NULL;

            ////////// Algoritmo LZW //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalObjetos = copiaLocalVetor<GameInfo>(datasetObjetos, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[1] << endl;

            //inicialização do algoritmo
            auto lzw = new LZW();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            lzw->compactar(textoParaComprimir);

            tempo_teste = timerEnd();//marca o tempo final

            //salva em disco para obter a taxa de compressão de armazenamento
            lzw->salvarEmDisco(getDiretorioTempCompressao() + "lzw_original" + to_string(tamDataset) + ".txt", getDiretorioTempCompressao() + "lzw_compactado" + to_string(tamDataset) + ".lzw");
            lzw->calculaEstatisticas();

            lzw->descompactar("lzw_compactado.lzw");

            //salva os resultados
            temposDeExecucao[1][t] = tempo_teste;
            taxaDeCompressao[1][t] = lzw->getTaxaCompressao();
            taxaDeCompressaoEmDisco[1][t] = lzw->getTaxaCompressaoEmDisco();
            armazenamentoEmDisco[1][t] = lzw->getTamanhoCompactadoEmDisco();
            salvaLinhaResultado(1, t);

            //libera memoria desse teste
            delete lzw;
            delete[] copiaLocalObjetos;
            lzw = NULL;
            copiaLocalObjetos = NULL;
            //exit(1);
        }
    }

private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    GameInfo *datasetObjetos = NULL;//vetor de objetos do dataset
    int tamDataset;
    double** temposDeExecucao;
    double** taxaDeCompressao;
    double** taxaDeCompressaoEmDisco;
    double** armazenamentoEmDisco;
    string *algoritmos;
    int numAlgoritmos;

    /**
    * Salva uma linha no arquivo de resultado
    * @param indice_algoritmo
    * @param indice_teste
    */
    void salvaLinhaResultado(int indice_algoritmo, int indice_teste){
        string linha = "";

        linha += to_string(testes[indice_teste]) + ",";
        linha += algoritmos[indice_algoritmo] + ",";
        linha += to_string(temposDeExecucao[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(taxaDeCompressao[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(taxaDeCompressaoEmDisco[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(armazenamentoEmDisco[indice_algoritmo][indice_teste]);

        Log::getInstance().lineArquivo(linha);
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
            cout << "Impossivel abrir o arquivo de configuração para leitura" << endl;
            cout << "Verifique a pasta 'entradas' e procure pelo arquivo '" << nomeArquivoEntrada << "'." << endl;
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

        LeitorGameInfo *gamesInfo = new LeitorGameInfo(qtdDadosTeste);
        GameInfo* dts = gamesInfo->getDataset();

        if(datasetObjetos != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] datasetObjetos;
        }

        this->datasetObjetos = new GameInfo[qtdDadosTeste];

        //monta vetor de inteiros
        for(int i=0; i<qtdDadosTeste; i++){
            datasetObjetos[i] = dts[i];
        }

        delete gamesInfo;//libera memória do leitor
    }

    /**
    * Faz uma cópia do vetor de inteiros.
    * Isso é usado porque os algoritmos modificam o vetor
    * @return *T
    */
    template <class T>
    T* copiaLocalVetor(T *vetor, int tam){
        T *ret = new T[tam];
        for(int i=0; i<tam; i++){
            ret[i] = vetor[i];
        }
        return ret;
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
};
#endif // CENARIOCOMPRESSAOSTRINGS_H
