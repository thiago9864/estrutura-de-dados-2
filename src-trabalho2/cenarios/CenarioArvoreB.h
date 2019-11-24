/**
    Universidade Federal de Juiz de Fora
    CenarioArvoreB.h
    Propósito: Implementação do cenario da arvore B do trabalho 2.

    @author Thiago Almeida, Luan Ciribelli
    @version 1.0 18/10/19
*/

#ifndef CENARIOARVOREB_H
#define CENARIOARVOREB_H
#include <iostream>
#include <string>

#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"

using namespace std;

class CenarioArvoreB : protected LeitorBase
{
public:
    CenarioArvoreB(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
    };

    ~CenarioArvoreB(){
        testes=NULL;
        delete[] datasetInteiros;
        delete[] datasetObjetos;
        datasetInteiros=NULL;
        datasetObjetos=NULL;
    };

    /**
    * Metodo principal do teste
    */
    void realizaTeste(){

        uint64_t inicio;

        numAlgoritmos = 4;
        algoritmos = new string[numAlgoritmos];
        algoritmos[0] = "Arvore B (Objetos, com d=2)";
        algoritmos[1] = "Arvore B (Objetos, com d=20)";
        algoritmos[2] = "Arvore B (Inteiros, com d=2)";
        algoritmos[3] = "Arvore B (Inteiros, com d=20)";

        //cria os vetores de teste
        temposDeExecucao = new double*[numAlgoritmos];
        numeroDeComparacores = new uint64_t*[numAlgoritmos];
        numeroDeCopias = new uint64_t*[numAlgoritmos];

        //inicia os vetores de teste com zero
        for(int a=0; a<numAlgoritmos; a++){
            temposDeExecucao[a] = new double[numTestes];
            numeroDeComparacores[a] = new uint64_t[numTestes];
            numeroDeCopias[a] = new uint64_t[numTestes];
            for(int t=0; t<numTestes; t++){
                temposDeExecucao[a][t] = 0;
                numeroDeComparacores[a][t] = 0;
                numeroDeCopias[a][t] = 0;
            }
        }

        //preenche header do csv
        Log::getInstance().lineArquivo("Número de Testes,Algoritmo,Tempo de Execução,Número de Comparações,Número de Copias");

        //Loop entre os testes do arquivo de configuração
        for(int t=0; t<numTestes; t++){

            cout << endl << "Executando o teste com " << testes[t] << " registros" << endl;
            tamDataset = testes[t];//marca aqui o tamanho do vetor de ints do teste

            //obtem dados do teste com a semente atual
            carregaDadosTeste(tamDataset);

            //cópias de teste
            UserReview* copiaLocalObjetos;
            int* copiaLocalInteiro;

            double tempo_teste;

            ////////// Arvore B com objetos e d=2 //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalObjetos = copiaLocalVetor<UserReview>(datasetObjetos, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[0] << endl;

            //inicialização do algoritmo
            /*
             colocar codigo aqui
            */
           //arvore->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            /*
             colocar codigo aqui
            */

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = 0;/* arvore->getNumComparacoes(); */
            numeroDeCopias[0][t] = 0;/* arvore->getNumCopias(); */
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            //delete arvore;
            delete[] copiaLocalObjetos;
            //arvore = NULL;
            copiaLocalObjetos = NULL;

            ////////// Arvore B com objetos e d=20 //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalObjetos = copiaLocalVetor<UserReview>(datasetObjetos, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[1] << endl;

            //inicialização do algoritmo
            /*
             colocar codigo aqui
            */
            //arvore->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            /*
             colocar codigo aqui
            */

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[1][t] = tempo_teste;
            numeroDeComparacores[1][t] = 0;/* arvore->getNumComparacoes(); */
            numeroDeCopias[1][t] = 0;/* arvore->getNumCopias(); */
            salvaLinhaResultado(1, t);

            //libera memoria desse teste
            //delete arvore; // colocar variavel do algoritmo aqui
            delete[] copiaLocalObjetos;
            //arvore = NULL; // colocar variavel do algoritmo aqui
            copiaLocalObjetos = NULL;


            ////////// Arvore B com inteiros e d=2 //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalInteiro = copiaLocalVetor<int>(datasetInteiros, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[2] << endl;

            //inicialização do algoritmo
            /*
             colocar codigo aqui
            */
           //arvore->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            /*
             colocar codigo aqui
            */

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[2][t] = tempo_teste;
            numeroDeComparacores[2][t] = 0;/* arvore->getNumComparacoes(); */
            numeroDeCopias[2][t] = 0;/* arvore->getNumCopias(); */
            salvaLinhaResultado(2, t);

            //libera memoria desse teste
            //delete arvore;
            delete[] copiaLocalInteiro;
            //arvore = NULL;
            copiaLocalInteiro = NULL;

            ////////// Arvore B com inteiros e d=20 //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalInteiro = copiaLocalVetor<int>(datasetInteiros, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[3] << endl;

            //inicialização do algoritmo
            /*
             colocar codigo aqui
            */
            //arvore->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            /*
             colocar codigo aqui
            */

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[3][t] = tempo_teste;
            numeroDeComparacores[3][t] = 0;/* arvore->getNumComparacoes(); */
            numeroDeCopias[3][t] = 0;/* arvore->getNumCopias(); */
            salvaLinhaResultado(3, t);

            //libera memoria desse teste
            //delete arvore; // colocar variavel do algoritmo aqui
            delete[] copiaLocalInteiro;
            //arvore = NULL; // colocar variavel do algoritmo aqui
            copiaLocalInteiro = NULL;

        }
    }

private:
    string nomeArquivoEntrada;
    int numTestes;
    int* testes;
    UserReview *datasetObjetos = NULL;//vetor de objetos do dataset
    int *datasetInteiros = NULL;//vetor de inteiros dos ids do dataset
    int tamDataset;
    double** temposDeExecucao;
    uint64_t** numeroDeComparacores;
    uint64_t** numeroDeCopias;
    string *algoritmos;
    int numAlgoritmos;

    void salvaLinhaResultado(int indice_algoritmo, int indice_teste){
        string linha = "";

        linha += to_string(testes[indice_teste]) + ",";
        linha += algoritmos[indice_algoritmo] + ",";
        linha += to_string(temposDeExecucao[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(numeroDeComparacores[indice_algoritmo][indice_teste]) + ",";
        linha += to_string(numeroDeCopias[indice_algoritmo][indice_teste]);

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

        LeitorUserReviews *userReviews = new LeitorUserReviews(qtdDadosTeste);
        UserReview* dts = userReviews->getDataset();

        if(datasetObjetos != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] datasetObjetos;
        }
        if(datasetInteiros != NULL){
            //limpa memoria se tiver alguma coisa nele
            delete[] datasetInteiros;
        }

        this->datasetObjetos = new UserReview[qtdDadosTeste];
        this->datasetInteiros = new int[qtdDadosTeste];

        //monta vetor de inteiros
        for(int i=0; i<qtdDadosTeste; i++){
            datasetObjetos[i] = dts[i];
            datasetInteiros[i] = dts[i].id;
        }

        delete userReviews;//libera memória do leitor
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
#endif // CENARIOARVOREB_H
