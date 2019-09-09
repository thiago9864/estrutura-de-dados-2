/**
    Universidade Federal de Juiz de Fora
    Log.h
    Propósito: Registra os logs num arquivo e imprime na tela.

    @author Thiago Almeida
    @version 1.0 10/06/19
*/

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Log {

public:
    static Log& getInstance()
    {
        static Log instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

private:
    Log() {} // Constructor? (the {} brackets) are needed here.
    ~Log(){
        // Destructor
        fechaArquivoDeSaida();
    }

    // C++ 03
    // ========
    // Don't forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    Log(Log const&);            // Don't Implement
    void operator=(Log const&); // Don't implement

    ofstream arqSaida;

public:

    /**
     * Abre o arquivo de saída para escrita.
     * @param nomeArqSaida caminho do arquivo de saida
     */
    void iniciaArquivoSaida(string caminhoArqSaida)
    {
        cout << caminhoArqSaida << endl;
        //abre arquivo para saida
        arqSaida.open(caminhoArqSaida.c_str());

        //verifica se o arquivo foi aberto
        if (!arqSaida || !arqSaida.is_open())
        {
            cout << "Impossivel abrir o arquivo de saida para escrita";
            exit(1); // sai do programa se nao conseguir abrir o arquivo
        }
    }

    void line(string texto){
        cout << texto << endl;
        arqSaida << texto << endl;
    }

    void lineArquivo(string texto){
        arqSaida << texto << endl;
    }

    void semEndl(string texto){
        cout << texto;
        arqSaida << texto;
    }

    void breakLine(){
        cout << endl;
        arqSaida << endl;
    }

    /**
     * Fecha o arquivo de saída para escrita.
     */
    void fechaArquivoDeSaida(){
        if(arqSaida.is_open()){
            arqSaida.close();
        }
    }

    void salvaLinhaNoArquivo(string linha, string caminhoArquivo){

        //abre arquivo
        ofstream arqLinha;
        arqLinha.open(caminhoArquivo.c_str(), std::ios_base::app);

        //verifica se o arquivo foi aberto
        if (!arqLinha || !arqLinha.is_open()){
            cout << "Impossivel abrir o arquivo para escrita";
        } else {
            arqLinha << linha << endl;
        }

        arqLinha.close();
    }
};


#endif //LOG_H
