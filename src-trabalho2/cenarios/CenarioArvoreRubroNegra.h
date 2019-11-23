/**
    Universidade Federal de Juiz de Fora
    CenarioArvoreRubroNegra.h
    Propósito: Implementação do cenario da arvore rubro-negra do trabalho 2.

    @author Thiago Almeida, Renan Nunes
    @version 1.0 18/10/19
*/

#ifndef CENARIOARVORERUBRONEGRA_H
#define CENARIOARVORERUBRONEGRA_H
#include <iostream>
#include <string>

#include "../LeitorUserReviews.h"
#include "../Log.h"
#include "../LeitorBase.h"
#include "../arvores/ArvoreRubroNegra.h"

using namespace std;

class CenarioArvoreRubroNegra : protected LeitorBase
{
public:
    CenarioArvoreRubroNegra(string nomeArquivoEntrada, string nomeArquivoSaida){
        this->numTestes = numTestes;
        this->testes = testes;
        this->nomeArquivoEntrada = nomeArquivoEntrada;

        carregaConfiguracao();

        Log::getInstance().fechaArquivoDeSaida();
        Log::getInstance().iniciaArquivoSaida(this->getDiretorioArquivoDeSaida()+nomeArquivoSaida);
    };

    ~CenarioArvoreRubroNegra(){
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

        numAlgoritmos = 2;
        algoritmos = new string[numAlgoritmos];
        algoritmos[0] = "Arvore Vermelho-Preto (Objetos)";
        algoritmos[1] = "Arvore Vermelho-Preto (Inteiros)";

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

            ////////// Arvore Vermelho-Preta com objetos //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalObjetos = copiaLocalVetor<UserReview>(datasetObjetos, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[0] << endl;

            //inicialização do algoritmo
            auto arvore = new ArvoreRubroNegra<UserReview>();
            arvore->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            for(int i=0; i<tamDataset; i++){
                arvore->inserir(copiaLocalObjetos[i]);
            }

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[0][t] = tempo_teste;
            numeroDeComparacores[0][t] = arvore->getNumComparacoes();
            numeroDeCopias[0][t] = arvore->getNumCopias();
            salvaLinhaResultado(0, t);

            //libera memoria desse teste
            delete arvore;
            delete[] copiaLocalObjetos;
            arvore = NULL;
            copiaLocalObjetos = NULL;

            ////////// Arvore Vermelho-Preta com inteiros //////////

            //rodar isso sempre antes de qualquer ordenação
            copiaLocalInteiro = copiaLocalVetor<int>(datasetInteiros, tamDataset);

            //debug - nome do algoritmo
            cout << algoritmos[1] << endl;

            //inicialização do algoritmo
            auto arvoreInt = new ArvoreRubroNegra<int>();
            arvoreInt->resetContadores();

            timerStart();//marca o tempo inicial

            // aqui roda o algoritmo
            for(int i=0; i<tamDataset; i++){
                arvoreInt->inserir(copiaLocalInteiro[i]);
            }

            tempo_teste = timerEnd();//marca o tempo final

            //salva os resultados
            temposDeExecucao[1][t] = tempo_teste;
            numeroDeComparacores[1][t] = arvoreInt->getNumComparacoes();
            numeroDeCopias[1][t] = arvoreInt->getNumCopias();
            salvaLinhaResultado(1, t);

            //libera memoria desse teste
            delete arvoreInt; // colocar variavel do algoritmo aqui
            delete[] copiaLocalInteiro;
            arvoreInt = NULL; // colocar variavel do algoritmo aqui
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
#endif // CENARIOARVORERUBRONEGRA_H
