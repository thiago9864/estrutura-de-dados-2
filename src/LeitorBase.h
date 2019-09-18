/**
    Universidade Federal de Juiz de Fora
    LeitorBase.h
    Propósito: Classe com metodos basicos para a leitura 

    @version 1.0 19/08/19
*/
#ifndef LEITORBASE_H
#define LEITORBASE_H
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class LeitorBase
{
    public:

        LeitorBase(){};
        ~LeitorBase(){}; 

        /**
         * Retorna o caractere separador de diretorio do sistema
         * @return string
         */
        string getDirSep(){
            #ifdef _WIN32
                return "\\";
            #else
                return "/";
            #endif
        }

        /**
         * Colocar aqui o caminho no computador que estiver rodando
         * Isso porque tem IDEs que criam uma pasta
         * @return string
         */
        string getDiretorioPreprocessado(){
            this->caminho_diretorio_main_cpp = "C:\\Users\\Thiago\\Documents\\Repositorios\\UFJF\\estrutura-de-dados-2\\src\\";//preencher se der erro de leitura
            string path = this->caminho_diretorio_main_cpp+"datasets"+getDirSep()+"preprocessado"+getDirSep();
            return path;
        }

        /**
         * Retorna o diretorio do arquivo de saida
         * @return string
         */
        string getDiretorioArquivoDeSaida(){
            return this->caminho_diretorio_main_cpp+"saidas"+getDirSep();
        }

        /**
         * Retorna o diretorio do arquivo de entrada
         * @return string
         */
        string getDiretorioArquivoDeEntrada(){
            return this->caminho_diretorio_main_cpp+"entradas"+getDirSep();
        }
    

        /**
         * Quebra a string fornecida em strings menores dado o separador
         * @s String para quebrar
         * @c Caractere separador
         * @return vector<string>
         */
        const vector<string> explode(const string& s, const char& c)
        {
            string buff{""};
            vector<string> v;
            
            for(auto n:s)
            {
                if(n != c) buff+=n; else
                if(n == c && buff != "") { v.push_back(buff); buff = ""; }
            }
            if(buff != "") v.push_back(buff);
            
            return v;
        }

        /**
         * Gera a semente para o leitor randomico
         * @return string
         */
        void gerarSemente() {
            semente = time(NULL);
            srand (semente);
        } 

        /**
         * Obtem um numero aleatorio de 0 ao valor enviado por parametro
         * @param maxRand
         * @return float
         */
        float getRand(int maxRand){
            return rand() % maxRand;
        }
    private:
        string caminho_diretorio_main_cpp;
        int semente;
};

#endif // LEITORBASE_H