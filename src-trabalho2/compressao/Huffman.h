//
// Created by lrpes on 13/11/2019.
//

#ifndef ESTRUTURA_DE_DADOS_2_HUFFMAN_H
#define ESTRUTURA_DE_DADOS_2_HUFFMAN_H
#include <iostream>
#include <string>
//#include <bits/stdc++.h>
#include "../stdc++.h"
#include "BaseCompressao.h"

using namespace std;

/**
 * Classe que guarda o metodo de compressão Huffman
 */
class Huffman : public BaseCompressao{
public:
    Huffman(){};
    ~Huffman(){};

    /**
     * Comprime a string com o metodo de compressão Huffman
     * @param stringParaCompactar (string) String a ser compactada
     */
    void compactar(string stringParaCompactar)
    {
        this->stringOriginal = stringParaCompactar;
        this->stringCompactadaASC = "";
        this->freq = unordered_map<char, int>();

        // Inicialização da tabela de frequencia
        for (char ch: stringParaCompactar) {
            this->freq[ch]++;
        }

        // Cria uma fila de nós com base na comparacao especificada abaixo
        priority_queue<NoHuffmanTree*, vector<NoHuffmanTree*>, comparacao> nosOrdenados;

        // Inicializa a folha de todos os caracteres e insere na fila de nos
        for (auto pair: freq) {
            nosOrdenados.push(getNode(pair.first, pair.second, nullptr, nullptr));
        }

        // Esse loop vai pegando os dois menores nos, coloca como filhos de um no novo e adiciona o no novo na fila
        // Ele faz isso ate sobrar so um no, que sera a raiz da arvore
        while (nosOrdenados.size() != 1)
        {
            NoHuffmanTree *left = nosOrdenados.top(); nosOrdenados.pop();
            NoHuffmanTree *right = nosOrdenados.top();	nosOrdenados.pop();

            int sum = left->freq + right->freq;
            nosOrdenados.push(getNode('\0', sum, left, right));
        }

        NoHuffmanTree* raiz = nosOrdenados.top();

        // Aqui ele chama a funcao recursiva que percorre cada folha salvando seu caminho em um dicionario
        geraCodigos(raiz, "");

        string stringCompactada;
        for (char ch: stringParaCompactar) {
            stringCompactada += this->dicionarioHuffman[ch];
        }

        string trechoStringCompactada;
        int nChTrechoStringCompactada = 0;

        for (char ch: stringCompactada) {
            trechoStringCompactada += ch;
            nChTrechoStringCompactada++;
            if(nChTrechoStringCompactada == 8){
                this->stringCompactadaASC += static_cast<char>(stoi(trechoStringCompactada, nullptr, 2));
                nChTrechoStringCompactada = 0;
                trechoStringCompactada = "";
            }
        }

        //cout << stringCompactadaASC << endl;

    }

    /**
    * Salva os conteudos original e compactado nos locais indicados
    * @param arquivoOriginal (string) Caminho que o arquivo original vai ser salvo
    * @param arquivoCompactado (string) Caminho que o arquivo compactado vai ser salvo
    * @param arquivoTabelaDeFrequencia (string) Caminho que a tabela de frequencias vai ser salva
    */
    void salvarEmDisco(string arquivoOriginal, string arquivoCompactado, string arquivoTabelaDeFrequencia){
        fileManager->salvarText(this->stringOriginal, arquivoOriginal);
        fileManager->salvarText(this->stringCompactadaASC, arquivoCompactado);
        fileManager->salvarText(this->geraCSVTabelaDeFrequencia(), arquivoTabelaDeFrequencia);
    }

    /**
     * Calcula as estatisticas relativas ao metodo de compressão
     * @param arquivoOriginal
     * @param arquivoCompactado
     */
    void calculaEstatisticas(string arquivoOriginal, string arquivoCompactado){
        int tamArquivoOriginal = this->stringOriginal.length();
        int tamArquivoCompactado = this->stringCompactadaASC.length();

        this->tamanhoEmDiscoOriginal = fileManager->getTamanhoEmDisco(arquivoOriginal);
        this->tamanhoEmDiscoCompactado = fileManager->getTamanhoEmDisco(arquivoCompactado);

        this->taxaCompressao = 1 - (tamArquivoCompactado / (double)tamArquivoOriginal);
        this->compressaoEmDisco = 1 - (this->tamanhoEmDiscoCompactado / this->tamanhoEmDiscoOriginal);
    }


    /**
     * Obtem a taxa de compressão
     * @return double
     */
    double geraTaxaCompressao(){
        return this->taxaCompressao;
    }

    /**
     * Obtem a taxa de compressão em disco
     * @return double
     */
    double geraTaxaCompressaoEmDisco(){
        return this->compressaoEmDisco;
    }

    /**
     * Obtem o tamanho do arquivo compactado em disco
     * @return int
     */
    double geraTamanhoCompactadoEmDisco(){
        return this->tamanhoEmDiscoCompactado;
    }


private:
    // Variaveis estatisticas
    double taxaCompressao;
    double compressaoEmDisco;
    double tamanhoEmDiscoCompactado;
    double tamanhoEmDiscoOriginal;

    // Variaveis compressão
    string stringOriginal;
    string stringCompactadaASC;
    unordered_map<char, int> freq;
    unordered_map<char, string> dicionarioHuffman;

    /**
     * Objeto usado como Nó para a Heap usada pelo metodo de compressão Huffman
     */
    struct NoHuffmanTree
    {
        char ch;
        int freq;
        NoHuffmanTree *left, *right;
    };

    /**
     * Função que cria um novo no para ser adicionado a heap do metodo Huffman
     * @param ch (char) Caractere que o nó representa
     * @param freq (int) Frequencia dele na tabela de frequencia
     * @param left (NoHuffmanTree*) Filho dele à esquerda
     * @param right (NoHuffmanTree*) Filho dele à direita
     * @return (NoHuffmanTree*) Nó criado
     */
    NoHuffmanTree* getNode(char ch, int freq, NoHuffmanTree* left, NoHuffmanTree* right)
    {
        NoHuffmanTree* noHuffman = new NoHuffmanTree();

        noHuffman->ch = ch;
        noHuffman->freq = freq;
        noHuffman->left = left;
        noHuffman->right = right;

        return noHuffman;
    }

    /**
     * Objeto de comparacao usado mais acima pra ordenar a heap
     */
    struct comparacao
    {
        bool operator()(NoHuffmanTree* l, NoHuffmanTree* r)
        {
            // O item de menor frequencia tem mais prioridade
            return l->freq > r->freq;
        }
    };

    /**
     * Função recursiva que gera o codigo binario para cada caractere da sua subarvore e coloca em um dicionario
     * @param raiz (NoHuffmanTree*) raiz da subarvore atual
     * @param str (string) string de inicio de todos os membros da subarvore
     */
    void geraCodigos(NoHuffmanTree *raiz, string str)
    {
        if (raiz == nullptr)
            return;

        // quando ele acha uma folha ele achou o codigo daquele caractere
        if (!raiz->left && !raiz->right) {
            this->dicionarioHuffman[raiz->ch] = str;
        }

        geraCodigos(raiz->left, str + "0");
        geraCodigos(raiz->right, str + "1");
    }

    /**
     * Gera uma string no formato CSV para armazenar a tabela de frequencia
     * @return (string) Tabela de frequencia guardada em uma string com formatação de CSV
     */
    string geraCSVTabelaDeFrequencia(){
        string CSVOutput;
        for(auto pair: this->freq){
            CSVOutput += pair.first;
            CSVOutput += "," + to_string(pair.second) + "\n";
        }
        return CSVOutput;
    }


};


#endif //ESTRUTURA_DE_DADOS_2_HUFFMAN_H
