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

using namespace std;

/**
 * Classe que serve de base para as arvores
 */
class BaseCompressao
{
    public:

        BaseCompressao(){};
        ~BaseCompressao(){};

        /**
         * Obtem a taxa de compressão
         * @return double 
         */
        double getTaxaCompressao(){
            return taxaCompressao;
        }

        /**
         * Obtem o tamanho do arquivo em disco
         * @return double 
         */
        double getTamanhoEmDisco(){
            return tamanhoEmDisco;
        }

        void calculaEstatisticas(uint64_t tamanhoStringEntrada, uint64_t tamanhoStringSaida, string caminhoArquivoEmDisco){
            taxaCompressao=0;
            tamanhoEmDisco=0;
        }

    private:
        double taxaCompressao;
        double tamanhoEmDisco;
};

#endif // BASECOMPRESSAO_H
