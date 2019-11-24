/**
    Universidade Federal de Juiz de Fora
    BaseCompressao.h
    Propósito: Classe basica para concentrar metodos comuns aos dois metodos de compressão implementados

    @author Thiago Almeida
    @version 1.0 18/10/19
*/
#ifndef BASECOMPRESSAO_H
#define BASECOMPRESSAO_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "FileManager.h"

using namespace std;

/**
 * Classe que serve de base para as arvores
 */
class BaseCompressao
{
    public:

        BaseCompressao(){
            fileManager = new FileManager();
        };
        ~BaseCompressao(){
            delete fileManager;
        };

        /**
         * Obtem a taxa de compressão
         * @return double
         */
        double getTaxaCompressao(){
            return taxaCompressao;
        }

        /**
         * Obtem a taxa de compressão em disco
         * @return double
         */
        double getTaxaCompressaoEmDisco(){
            return compressaoEmDisco;
        }

        /**
         * Obtem o tamanho do arquivo compactado em disco
         * @return int
         */
        double getTamanhoCompactadoEmDisco(){
            return tamanhoEmDiscoCompactado;
        }

        /**
        * Salva os conteudos original e compactado nos locais indicados
        * @param arquivoOriginal (string) Caminho que o arquivo original vai ser salvo
        * @param conteudoArqOriginal (string) Conteudo do arquivo original
        * @param arquivoCompactado (string) Caminho que o arquivo compactado vai ser salvo
        * @param conteudoArqCompactado (vector<int>) Conteudo do arquivo compactado
        */
        void salvarEmDisco(string arquivoOriginal, string conteudoArqOriginal, string arquivoCompactado, vector<int> conteudoArqCompactado){
            fileManager->salvarText(conteudoArqOriginal, arquivoOriginal);
            fileManager->salvarIntVector(conteudoArqCompactado, arquivoCompactado);
        }

        /**
        * Calcula dados estatísticos sobre o algoritmo
        * @param arquivoOriginal (string) Caminho que o arquivo original vai ser salvo
        * @param conteudoArqOriginal (string) Conteudo do arquivo original
        * @param arquivoCompactado (string) Caminho que o arquivo compactado vai ser salvo
        * @param conteudoArqCompactado (vector<int>) Conteudo do arquivo compactado
        */
        void calculaEstatisticas(string arquivoOriginal, string conteudoArqOriginal, string arquivoCompactado, vector<int> conteudoArqCompactado){
            int tamArquivoOriginal = conteudoArqOriginal.length();
            int tamArquivoCompactado = conteudoArqCompactado.size();

            tamanhoEmDiscoOriginal = fileManager->getTamanhoEmDisco(arquivoOriginal);
            tamanhoEmDiscoCompactado = fileManager->getTamanhoEmDisco(arquivoCompactado);

            taxaCompressao = 1 - (tamArquivoCompactado / (double)tamArquivoOriginal);
            compressaoEmDisco = 1 - (tamanhoEmDiscoCompactado / tamanhoEmDiscoOriginal);
        }

    private:
        double taxaCompressao;
        double compressaoEmDisco;
        double tamanhoEmDiscoCompactado;
        double tamanhoEmDiscoOriginal;

    protected:
        FileManager *fileManager;

};

#endif // BASECOMPRESSAO_H
