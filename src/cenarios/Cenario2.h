/**
    Universidade Federal de Juiz de Fora
    Cenario2.h
    Propósito: Implementação do Segundo cenário da parte 1 do trabalho.

    @author Thiago Almeida, Luan Ciribeli
    @version 1.1 06/10/19
*/

#ifndef CENARIO_2_H
#define CENARIO_2_H
#include <iostream>
#include <string>

#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"
#include "../ordenacao/Quicksort.h"
#include "../ordenacao/QuickSortMediana.h"
#include "../ordenacao/QuickSortInsertion.h"

using namespace std;

class Cenario2 : protected LeitorBase
{
public:
    Cenario2(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);

    };

    ~Cenario2(){
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
        algoritmos[0] = "Quicksort";
        algoritmos[1] = "Quicksort Insertion (m=10)";
        algoritmos[2] = "Quicksort Insertion (m=100)";
        algoritmos[3] = "Quicksort Mediana (k=3)";
        algoritmos[4] = "Quicksort Mediana (k=5)";



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

        //preenche header do csv
        Log::getInstance().lineArquivo("Teste,Número de Testes,Algoritmo,Tempo de Execução,Número de Comparações,Número de Trocas");

        //Loop entre os testes do arquivo de configuração
        for(int t=0; t<numTestes; t++){
            cout << endl << "Executando o teste com " << testes[t] << " registros" << endl;
            tamVetorInt = testes[t];//marca aqui o tamanho do vetor de ints do teste

            //obtem dados do teste com a semente atual
            carregaDadosTeste(tamVetorInt);

            int* copiaLocal;//copia do vetor de testes usada no algoritmo
            double tempo_teste;


            ////////// QuickSort //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSort" << endl;

            //inicia o algoritmo de ordenacao
            QuickSort<int> *quickSort = new QuickSort<int>();

            timerStart();//marca o tempo inicial
            quickSort->resetContadores();
            quickSort->ordenarInt(copiaLocal, 0, tamVetorInt);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = quickSort->getNumComparacoes();
            numeroDeTrocas[0][t] = quickSort->getNumTrocas();
            salvaLinhaResultado(0, t);

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete[] copiaLocal;
            delete quickSort;
            quickSort = NULL;
            copiaLocal = NULL;

            ////////// QuickSortInsertion (m=10) //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSortInsertion (m=10)" << endl;

            //inicia o algoritmo de ordenacao
            QuickSortInsertion<int> *quickSortInsertion = new QuickSortInsertion<int>();

            timerStart();//marca o tempo inicial
            quickSortInsertion->resetContadores();
            quickSortInsertion->ordenarInt(copiaLocal, 0, tamVetorInt-1, 10);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[1][t] = tempo_teste;
            numeroDeComparacores[1][t] = quickSortInsertion->getNumComparacoes();
            numeroDeTrocas[1][t] = quickSortInsertion->getNumTrocas();
            salvaLinhaResultado(1, t);

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete quickSortInsertion;
            delete[] copiaLocal;
            quickSortInsertion = NULL;
            copiaLocal = NULL;

            ////////// QuickSortInsertion (m=100) //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSortInsertion (m=100)" << endl;

            //inicia o algoritmo de ordenacao
            QuickSortInsertion<int> *quickSortInsertion_m100 = new QuickSortInsertion<int>();

            timerStart();//marca o tempo inicial
            quickSortInsertion_m100->resetContadores();
            quickSortInsertion_m100->ordenarInt(copiaLocal, 0, tamVetorInt-1, 100);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[2][t] = tempo_teste;
            numeroDeComparacores[2][t] = quickSortInsertion_m100->getNumComparacoes();
            numeroDeTrocas[2][t] = quickSortInsertion_m100->getNumTrocas();
            salvaLinhaResultado(2, t);

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete quickSortInsertion_m100;
            delete[] copiaLocal;
            quickSortInsertion_m100 = NULL;
            copiaLocal = NULL;

            ////////// QuickSortMediana k=3 //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSortMediana (k=3)" << endl;

            //inicia o algoritmo de ordenacao
            QuickSortMediana<int> *quickSortMediana = new QuickSortMediana<int>();

            timerStart();//marca o tempo inicial
            quickSortMediana->resetContadores();
            quickSortMediana->ordenarInt(copiaLocal, 3, 0, tamVetorInt-1);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[3][t] = tempo_teste;
            numeroDeComparacores[3][t] = quickSortMediana->getNumComparacoes();
            numeroDeTrocas[3][t] = quickSortMediana->getNumTrocas();
            salvaLinhaResultado(3, t);

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete quickSortMediana;
            delete[] copiaLocal;
            quickSortMediana = NULL;
            copiaLocal = NULL;

            ////////// QuickSortMediana k=5 //////////

            copiaLocal = copiaLocalVetorInt();
            cout << "- QuickSortMediana (k=5)" << endl;

            //inicia o algoritmo de ordenacao
            QuickSortMediana<int> *quickSortMediana_k5 = new QuickSortMediana<int>();

            timerStart();//marca o tempo inicial
            quickSortMediana_k5->resetContadores();
            quickSortMediana_k5->ordenarInt(copiaLocal, 5, 0, tamVetorInt-1);
            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[4][t] = tempo_teste;
            numeroDeComparacores[4][t] = quickSortMediana_k5->getNumComparacoes();
            numeroDeTrocas[4][t] = quickSortMediana_k5->getNumTrocas();
            salvaLinhaResultado(4, t);

            //Debug - Salva o vetor ordenado pelo QuickSort
            //salvaVetor("quicksort_ordenado_"+to_string(tamVetorInt)+".csv", copiaLocal, tamVetorInt);

            //libera memoria desse teste
            delete quickSortMediana_k5;
            delete[] copiaLocal;
            quickSortMediana_k5 = NULL;
            copiaLocal = NULL;

        }
    }

private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    //UserReview *dataset;
    int *dataset = NULL;
    int *vetorInt = NULL;
    int tamVetorInt = NULL;
    double** temposDeExecucao;
    uint64_t** numeroDeComparacores;
    uint64_t** numeroDeTrocas;
    string *algoritmos;
    int numAlgoritmos;

    void salvaLinhaResultado(int indice_algoritmo, int indice_teste){
        string linha = "";

        linha += to_string(indice_teste) + ",";
        linha += to_string(testes[indice_teste]) + ",";
        linha += algoritmos[indice_algoritmo] + ",";
        linha += to_string(temposDeExecucao[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(numeroDeComparacores[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(numeroDeTrocas[indice_algoritmo][indice_teste]);

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
#endif // CENARIO_2_H
