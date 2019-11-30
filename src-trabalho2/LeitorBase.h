/**
    Universidade Federal de Juiz de Fora
    LeitorBase.h
    Propósito: Classe com metodos basicos para a leitura

    @version 1.0 19/08/19
*/
#ifndef LEITORBASE_H
#define LEITORBASE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <stdio.h>
#include <time.h>
#include <random>
#include <chrono>
#include "UserReview.h"
#include <sys/types.h>
#include <sys/stat.h>

#if defined(_WIN32)
//includes para windows
#include <windows.h>

#elif defined(__APPLE__) && defined(__MACH__)
//includes para mac
//#include <unistd.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
//includes para linux
//#include <unistd.h>

#endif

using namespace std;

class LeitorBase
{
    public:

        LeitorBase(){
            criaDiretoriosNecessarios();
        };
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
            //this->caminho_diretorio_main_cpp = "D:\\Projetos\\ED2\\estrutura-de-dados-2\\src\\";//preencher se der erro de leitura
            this->caminho_diretorio_main_cpp = "";
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
         * Retorna o diretorio do arquivo temporario da compressao
         * @return string
         */
        string getDiretorioTempCompressao(){
            return this->caminho_diretorio_main_cpp+"temp_compressao"+getDirSep();
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
            if(s == "" || s.length()<=0){
                cout << "explode(): string vazia" << endl;
                return vector<string>();
            }

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
            generator.seed(semente);
        }

        /**
         * Obtem um numero aleatorio de 0 ao valor enviado por parametro
         * @param maxRand
         * @return int
         */
        int getRand(int maxRand){
            uniform_int_distribution<int> distribuition(0, maxRand);
            return distribuition(generator);
        }

        /**
         * Inicia contagem de tempo
         */
        void timerStart(){
            start = std::chrono::system_clock::now();
        }

        /**
         * Obtem a diferenca de tempo em segundos
         * @return double
         */
        double timerEnd(){
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            double duracao = elapsed_seconds.count();
            return duracao;
        }

        /**
        * Retorna a data atual como string no formato dd-mm-yyyy hh:mm:ss
        * @return string
        */
        string getCurrentDateAsString(){
            time_t rawtime;
            struct tm * timeinfo;
            char buffer[80];

            time (&rawtime);
            timeinfo = localtime(&rawtime);

            strftime(buffer,sizeof(buffer),"%d_%m_%Y_%H_%M_%S",timeinfo);
            string str(buffer);

            return str;
        }

        /**
        * Debug: Salva o vetor de inteiros em um arquivo
        * @param filename Nome do arquivo
        * @param vetor Vetor de inteiros
        * @param tam Tamanho do vetor
        */
        void salvaVetor(string filename, UserReview* vetor, int tam){
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
                arqSaida << vetor[i].id << endl;
            }

            if(arqSaida.is_open()){
                arqSaida.close();
            }
        }

    private:
        string caminho_diretorio_main_cpp;
        default_random_engine generator;
        int semente;
        std::chrono::time_point<std::chrono::system_clock> start, end;


        void criaDiretoriosNecessarios(){
            criarDiretorioSeNaoExiste(getDiretorioArquivoDeSaida());
            criarDiretorioSeNaoExiste(getDiretorioTempCompressao());
        }

        int criarDiretorioSeNaoExiste(string caminho){
            if(directoryExists(caminho.c_str()) == false){
                cout << "o diretorio '" << caminho << "' nao foi encontrado e sera criado" << endl;
                #if defined(_WIN32)
                /* Windows -------------------------------------------------- */
                std::wstring stemp = std::wstring(caminho.begin(), caminho.end());
                LPCWSTR sw = stemp.c_str();
                return CreateDirectoryW(sw, NULL );
                #elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
                /* Linux/Mac -------------------------------------------------- */
                string comando = "mkdir \""+caminho+"\"";
                system(comando.c_str());
                return 1;//mkdir(caminho.c_str(), 0777);
                #endif
            }
        }

        bool directoryExists(const char* dirName) {
            #if defined(_WIN32)
                DWORD attribs = ::GetFileAttributesA(dirName);
                if (attribs == INVALID_FILE_ATTRIBUTES) {
                    return false;
                }
                return (attribs & FILE_ATTRIBUTE_DIRECTORY);
            #elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
                struct stat info;
                if( stat( dirName, &info ) != 0 )
                    return false;
                else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows 
                    return true;
                else
                    return false;
            #endif
        }

};

#endif // LEITORBASE_H
