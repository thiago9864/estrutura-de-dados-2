/**
    Universidade Federal de Juiz de Fora
    Cenario3.h
    Propósito: Implementação do terceiro cenário da parte 1 do trabalho.

    @author Thiago Almeida
    @version 1.0 18/09/19
*/

#ifndef CENARIO_3_H
#define CENARIO_3_H
#include <iostream>
#include <time.h>
#include <chrono>
#include <string>

#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"
#include "../ordenacao/Quicksort.h"
#include "../ordenacao/InsertionSort.h"
#include "../ordenacao/MergeSort.h"
#include "../ordenacao/HeapSort.h"
#include "../ordenacao/RadixSort.h"

using namespace std;

class Cenario3 : protected LeitorBase
{
public:
    Cenario3(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
        Log::getInstance().line("---- Iniciando Cenario 3 ----");
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
    ~Cenario3(){
        testes=NULL;
        delete[] dataset;
        dataset=NULL;
    };

    /**
    * Metodo principal do teste
    */
    void realizaTeste(){

        uint64_t inicio;
        string algoritmos[] = {"InsertionSort", "Quicksort    ", "Mergesort    ", "Heapsort     ", "Meusort      "};
        int numAlgoritmos = 5;

        //cria os vetores de teste
        temposDeExecucao = new double*[numAlgoritmos];
        numeroDeComparacores = new uint64_t*[numAlgoritmos];
        numeroDeTrocas = new uint64_t*[numAlgoritmos];

        //inicia os vetores de teste com zero
        for(int a=0; a<numAlgoritmos; a++){
            temposDeExecucao[a] = new double[numTestes];
            numeroDeComparacores[a] = new uint64_t[numTestes];
            numeroDeTrocas[a] = new uint64_t[numTestes];
            for(int t=0; t<numTestes; t++){
                temposDeExecucao[a][t] = 0;
                numeroDeComparacores[a][t] = 0;
                numeroDeTrocas[a][t] = 0;
            }
        }

        //Loop entre os testes do arquivo de configuração
        for(int t=0; t<numTestes; t++){

            cout << endl << "Executando o teste com " << testes[t] << " registros" << endl;
            tamVetorInt = testes[t];//marca aqui o tamanho do vetor de ints do teste

            //obtem dados do teste com a semente atual
            carregaDadosTeste(tamVetorInt);

            int* copiaLocal;//copia do vetor de testes usada no algoritmo
            double tempo_teste;

            ////////// InsertionSort //////////

            copiaLocal = copiaLocalVetorInt();

            //debug - Salvar o vetor fonte
            //salvaVetor("vetor_fonte_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            cout << "- InsertionSort" << endl;

            //inicia o algoritmo de ordenacao
            InsertionSort<int> *insertionSort = new InsertionSort<int>();

            timerStart();//marca o tempo inicial
            insertionSort->resetContadores();
            insertionSort->ordenarInt(copiaLocal, tamVetorInt);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = insertionSort->getNumComparacoes();
            numeroDeTrocas[0][t] = insertionSort->getNumTrocas();

            //Debug - Salva o vetor ordenado pelo InsertionSort
            //salvaVetor("insertionsort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete insertionSort;
            delete[] copiaLocal;
            insertionSort = NULL;
            copiaLocal = NULL;

            ////////// QuickSort //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSort" << endl;

            //inicia o algoritmo de ordenacao
            QuickSort<int> *quickSort = new QuickSort<int>();

            timerStart();//marca o tempo inicial
            quickSort->resetContadores();
            quickSort->ordenarInt(copiaLocal, 0, tamVetorInt-1);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[1][t] = tempo_teste;
            numeroDeComparacores[1][t] = quickSort->getNumComparacoes();
            numeroDeTrocas[1][t] = quickSort->getNumTrocas();

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete quickSort;
            delete[] copiaLocal;
            quickSort = NULL;
            copiaLocal = NULL;

            ////////// MergeSort //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- MergeSort" << endl;

            //inicia o algoritmo de ordenacao
            MergeSort<int> *mergeSort = new MergeSort<int>();

            timerStart();//marca o tempo inicial
            mergeSort->resetContadores();
            mergeSort->ordenarInt(copiaLocal, 0, tamVetorInt-1);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[2][t] = tempo_teste;
            numeroDeComparacores[2][t] = mergeSort->getNumComparacoes();
            numeroDeTrocas[2][t] = mergeSort->getNumTrocas();

            //Debug - Salva o vetor ordenado pelo MergeSort
            //salvaVetor("mergesort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete mergeSort;
            delete[] copiaLocal;
            mergeSort = NULL;
            copiaLocal = NULL;

            ////////// HeapSort //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- HeapSort" << endl;

            //inicia o algoritmo de ordenacao
            HeapSort<int> *heapSort = new HeapSort<int>();

            timerStart();//marca o tempo inicial
            heapSort->resetContadores();
            heapSort->ordenarInt(copiaLocal, tamVetorInt);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[3][t] = tempo_teste;
            numeroDeComparacores[3][t] = heapSort->getNumComparacoes();
            numeroDeTrocas[3][t] = heapSort->getNumTrocas();

            //Debug - Salva o vetor ordenado pelo HeapSort
            salvaVetor("heapsort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete heapSort;
            delete[] copiaLocal;
            heapSort = NULL;
            copiaLocal = NULL;

            ////////// MeuSort (Radix) //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- MeuSort (Radix)" << endl;

            //inicia o algoritmo de ordenacao
            RadixSort<int> *radixSort = new RadixSort<int>();

            timerStart();//marca o tempo inicial
            radixSort->ordenarInt(copiaLocal, tamVetorInt);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[4][t] = tempo_teste;
            numeroDeComparacores[4][t] = 0;//está zero porque o RadixSort é um algoritmo não comparativo
            numeroDeTrocas[4][t] = 0;

            //Debug - Salva o vetor ordenado pelo RadixSort
            //salvaVetor("radixsort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete radixSort;
            delete[] copiaLocal;
            radixSort = NULL;
            copiaLocal = NULL;
        }

        Log::getInstance().line("\n---- Resultados ----");

        for(int t=0; t<numTestes; t++){
            Log::getInstance().line("\nTeste com " + to_string(testes[t]) + " registros.\n");
            for(int a=0; a<numAlgoritmos; a++){
                Log::getInstance().semEndl(algoritmos[a] + ": ");
                Log::getInstance().semEndl("Tempo de Execucao: " + to_string(temposDeExecucao[a][t])+", ");
                Log::getInstance().semEndl("Comparacoes: " + to_string(numeroDeComparacores[a][t])+", ");
                Log::getInstance().semEndl("Trocas: " + to_string(numeroDeTrocas[a][t]));
                Log::getInstance().breakLine();
            }
        }
    }

private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    //UserReview *dataset;
    int *dataset = NULL;
    int* vetorInt = NULL;
    int tamVetorInt = NULL;
    double** temposDeExecucao;
    uint64_t** numeroDeComparacores;
    uint64_t** numeroDeTrocas;

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
            dataset[i] = dts[i].id;//+ somaAsciiFromString(dts[i].user);
        }
        delete userReviews;//libera memória do leitor

        //essa parte do codigo gera uma sequencia aleatória de números
        //GeradorSequencia *gs = new GeradorSequencia();
        //gs->gerarSequencia(qtdDadosTeste);
        //dataset = gs->getDataset();
        //delete gs;
    }

    /**
    * Faz uma cópia do vetor de inteiros.
    * Isso é usado porque os algoritmos modificam o vetor
    * @return *int
    */
    int* copiaLocalVetorInt(){
        int* copia = new int[tamVetorInt];
        for(int i=0; i<tamVetorInt; i++){
            //copia[i] = dataset[i].id;
            copia[i] = dataset[i];
        }
        return copia;
    }

    /**
     * Soma os valores da posição do caractere na tabela ascii, dada a string
     * @param str String pra somar
     * @return int
     */
    int somaAsciiFromString(string str){
        int ret = 0;
        for(int i=0; i<str.length(); i++){
            ret += int(str.at(i));
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
        arqSaida.open("saidas"+getDirSep()+filename.c_str());

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
#endif // CENARIO_3_H
