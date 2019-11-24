/**
    Universidade Federal de Juiz de Fora
    LZW.h
    Propósito: Classe que representa o algoritmo de compressão/decompressão LZW

    @author Thiago Almeida
    @version 1.0 25/10/19
*/
#ifndef LZW_H
#define LZW_H
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "BaseCompressao.h"

using namespace std;

/**
 * Classe que guarda o metodo de compressão Lempel–Ziv–Welch
 */
class LZW : public BaseCompressao
{
    public:

        LZW(){};
        ~LZW(){};

        /**
        * Função de compactação do metodo Lempel–Ziv–Welch
        * @param stringParaCompactar (string) Conteudo a compactar
        */
        void compactar(string stringParaCompactar){
            int p=0;
            int textoLen = stringParaCompactar.length();
            int prcAnt=0;

            //armazena a string original por referencia
            //porque vai salvar ela em um arquivo pra conferir a taxa de compressão
            //em disco
            this->stringParaCompactar = stringParaCompactar;

            this->output.clear();

            string C;//Atual
            string N;//Proximo

            //inicia a tabela com os caracteres ASCII estentido
            unordered_map<string, int> stringTable;

            for (int i = 0; i <= 255; i++) {
                string ch = "";
                ch += char(i);
                stringTable[ch] = i;
            }
            int ultimaChave = 255;

            C = stringParaCompactar[0];//seta primeiro caracter como atual

            while(true){
                //obtem o item atual da tabela
                int chaveC=-1;
                auto res_busca = stringTable.find(C);
                if ( res_busca != stringTable.end() ){
                    chaveC = res_busca->second;
                } else {
                    cout << "Erro na tabela ascii" << endl;
                    exit(1);
                }

                if(p>=(textoLen-1)){
                    //ultima iteração - adiciona o ultimo item a saida
                    output.push_back(chaveC);
                    break;
                } else {
                    N = stringParaCompactar[p+1];

                    //procura a sequencia C+N na tabela
                    if(stringTable.find(C+N) == stringTable.end()){
                        //não encontrou a sequencia

                        //adiciona a sequencia a tabela
                        ultimaChave++;
                        stringTable[C+N] = ultimaChave;

                        //adiciona a chave do atual ao vetor de saida
                        output.push_back(chaveC);

                        //avança para o proximo caractere
                        p++;
                        C = stringParaCompactar[p];

                    } else {
                        //a sequencia foi encontrada
                        C = C+N;//define como atual a sequencia encontrada
                        p++;//move o indice do caracter para o proximo
                    }

                    //debug para calcular a porcentagem de andamento
                    int prc = (p/(float)textoLen)*100;
                    if(prc != prcAnt){
                        prcAnt = prc;
                        if(prc % 10 == 0){
                            cout << "prc: " << prc << endl;
                        }
                    }
                }
            }
        }

        /**
        * Função de descompactação do metodo Lempel–Ziv–Welch
        * @param arquivo (string) Caminho do arquivo compactado
        */
        void descompactar(string arquivo){

            //obtem conteudo do arquivo compactado
            vector<int> input = fileManager->ler(arquivo);

            if(input.size() == 0){
                cout << "O arquivo não tem conteudo ou está corrompido" << endl;
                return;
            }

            //inicia a tabela com os caracteres ASCII estentido
            unordered_map<int, string> stringTable;

            for (int i = 0; i <= 255; i++) {
                string ch = "";
                ch += char(i);
                stringTable[i] = ch;
            }

            int p=1;
            int ultimaChave=255;
            string saida="";

            int O, N;
            string S, C;

            O = input[0];//primeiro caracter da entrada
            C = "";
            S = "";

            saida += stringTable[O];//tradução do primeiro caracter para a saida

            //loop enquanto tem caracteres para decodificar
            while(p<input.size()){

                //proximo caracter
                N = input[p];

                auto res_N = stringTable.find(N);

                if(res_N == stringTable.end()){
                    //Se o proximo caracter não estiver na tabela
                    S = stringTable[O];
                    S = S+C;
                } else {
                    S = stringTable[N];
                }

                saida += S;//acrescenta o valor de S a saida
                C="";
                C += S[0];
                ultimaChave++;
                stringTable[ultimaChave] = stringTable[O]+C;//adiciona chave a tabela
                O = N;
                p++;
            }


            stringDesompactada = saida;

            if(stringParaCompactar == stringDesompactada){
                cout << "Compressao e descompressao funcionando." << endl;
            }
        }

        /**
        * Salva o conteudo original e compactado em arquivos distintos
        * @param arquivoOriginal (string) Caminho do arquivo original
        * @param arquivoCompactado (string) Caminho do arquivo compactado
        */
        void salvarEmDisco(string arquivoOriginal, string arquivoCompactado){
            this->arquivoCompactado = arquivoCompactado;
            this->arquivoOriginal = arquivoOriginal;
            BaseCompressao::salvarEmDisco(arquivoOriginal, stringParaCompactar, arquivoCompactado, output);
        }

        /**
        * Calcula as estatisticas do algoritmo
        */
        void calculaEstatisticas(){
            BaseCompressao::calculaEstatisticas(arquivoOriginal, stringParaCompactar, arquivoCompactado, output);
        }

    private:
        vector<int> output;//saida codificada
        string stringParaCompactar;
        string stringDesompactada;
        string arquivoCompactado;
        string arquivoOriginal;

};

#endif // LZW_H
