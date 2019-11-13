/**
    Universidade Federal de Juiz de Fora
    FileManager.h
    Propósito: Classe que lida com leitura e escrita dos arquivos da compressão

    @version 1.0 26/10/19
*/
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class FileManager : protected LeitorBase
{
    public:

        FileManager(){};
        ~FileManager(){};

        /**
        * Salva um conteudo de texto no arquivo indicado
        * @param conteudo (string) Conteudo do arquivo a ser salvo
        * @param arquivo (string) Caminho do arquivo que vai ser salvo
        */
        void salvarText(string conteudo, string arquivo){
            ofstream fout;

            //salva o arquivo e sobrescreve o seu conteudo
            fout.open(arquivo.c_str(), fstream::out | fstream::trunc);
            fout << conteudo;
            fout.close();
        }

        /**
        * Salva um conteudo de um vetor de inteiros (de 8 a 16bits) no arquivo indicado
        * @param conteudo (vector<int>) Conteudo do arquivo a ser salvo
        * @param arquivo (string) Caminho do arquivo que vai ser salvo
        */
        void salvarIntVector(vector<int> conteudo, string arquivo){
            ofstream fout;

            fout.open(arquivo.c_str(), fstream::out | fstream::binary);

            //verifica se o arquivo foi aberto
            if (!fout || !fout.is_open())
            {
                cout << "Impossivel abrir o arquivo '" << arquivo << "' para escrita" << endl;
                return;
            }

            string lsb, msb, hex;
            int bufferSize = conteudo.size()*2;
            char *buffer = new char[bufferSize];
            int p=0;

            for(int i=0; i < conteudo.size(); i++){
                //converte o inteiro para uma string hex
                hex = intToHexString(conteudo[i]);

                //quebra a string em duas partes, a mais e menos significativa
                if(hex.length()<=2){
                    msb = "0";
                    lsb = hex;
                } else {
                    lsb = hex.substr(hex.length()-2,2);
                    msb = hex.substr(0,hex.length()-2);
                }

                //completa com o 0 se faltar
                if(msb.length()==1){
                    msb = "0" + msb;
                }
                if(lsb.length()==1){
                    lsb = "0" + lsb;
                }

                //inclui no buffer a representação char da string hex
                buffer[p] = char(hexStringToInt(msb));
                buffer[p+1] = char(hexStringToInt(lsb));

                //proxima dupla do buffer
                p+=2;
            }

            //escreve o buffer
            fout.write (buffer, bufferSize);
            fout.close();
        }

        /**
        * Faz a leitura do arquivo compactado indicado
        * @param arquivo (string) Caminho do arquivo compactado
        * @return vector<int> Vetor de inteiros (de 8 a 16 bits)
        */
        vector<int> ler(string arquivo){
            ifstream fin (arquivo.c_str(), ifstream::binary);
            vector<int> retorno;

            //verifica se o arquivo foi aberto
            if (!fin || !fin.is_open())
            {
                cout << "Impossivel abrir o arquivo '" << arquivo << "' para leitura" << endl;
                return retorno;
            }

            // get length of file:
            fin.seekg (0, fin.end);
            int length = fin.tellg();
            fin.seekg (0, fin.beg);

            char *buffer = new char [length];

            // lê os dados do arquivo no buffer
            fin.read (buffer, length);
            fin.close();

            for(int i=0; i<length;i+=2){
                //obtem as duplas em mais e menos significativo do buffer
                auto c_msb = (unsigned char)buffer[i];
                auto c_lsb = (unsigned char)buffer[i+1];

                //converte de char para string hex
                string msb_s = intToHexString((int)c_msb);
                string lsb_s = intToHexString((int)c_lsb);

                //completa o zero
                if(msb_s.length()==1){
                    msb_s = "0" + msb_s;
                }
                if(lsb_s.length()==1){
                    lsb_s = "0" + lsb_s;
                }

                //monta a string hex
                string h_str = msb_s + lsb_s;

                //adiciona o inteiro correspondente a string hex
                retorno.push_back(hexStringToInt(h_str));
            }

            return retorno;
        }

        /**
        * Obtem o tamanho em disco (em bytes) do arquivo indicado
        * @param arquivo (string) Caminho do arquivo a verificar
        * @return int
        */
        int getTamanhoEmDisco(string arquivo){
            ifstream fin (arquivo.c_str(), ifstream::binary);
            int tamanho=0;

            //verifica se o arquivo foi aberto
            if (!fin || !fin.is_open())
            {
                cout << "Impossivel abrir o arquivo '" << arquivo << "' para leitura" << endl;
                return 0;
            }

            // get length of file:
            fin.seekg (0, fin.end);
            tamanho = fin.tellg();
            fin.seekg (0, fin.beg);

            fin.close();

            return tamanho;
        }

    private:

        /**
        * Converte um inteiro para uma string hextadecimal
        * @param numero (int) Numero a converter
        * @return string
        */
        string intToHexString(int numero){
            std::stringstream stream;
            stream << std::hex << numero;
            std::string result( stream.str() );
            return result;
        }

        /**
        * Converte uma string hextadecimal para uma inteiro
        * @param hexStr (string) String a converter
        * @return int
        */
        int hexStringToInt(string hexStr){
            unsigned int x;
            std::stringstream ss;
            ss << std::hex << hexStr;
            ss >> x;
            return x;
        }
};

#endif // FILEMANAGER_H
