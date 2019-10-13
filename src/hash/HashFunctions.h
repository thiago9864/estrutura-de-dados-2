/**
    Universidade Federal de Juiz de Fora
    HashFunctions.h
    Propósito:

    @author Lucas Ribeiro
    @version 1.0 08/10/19
*/
#ifndef SRC_HASHFUNCTIONS_H
#define SRC_HASHFUNCTIONS_H

#include <iostream>

using namespace std;

/**
 * Guarda funções estaticas que são usadas em diversos hashes
 */
class HashFunctions {
public:
    /**
     * Função de hashing de divisão que transforma o nome e o id em um valor numerico
     * para ser utilizado na inserção
     * @param id id do item que usará a função
     * @param nome nome do item que usará a função
     * @param tamTable tamanho da lista do hash
     * @param primo número primo que será utilizado na divisão
     * @return resultado da conta realizada pelo hasher
     */
    static int divisao(int id, string nome, int tamTable, int primo){
        return (geraNumeroHashable(id, nome) % primo) % tamTable;
    };

    /**
     * Função de hashing de multiplicação que transforma o nome e o id em um valor numerico
     * para ser utilizado na inserção
     * @param id id do item que usará a função
     * @param nome nome do item que usará a função
     * @param tamTable tamanho da lista do hash
     * @return resultado da conta realizada pelo hasher
     */
    static int multiplicacao(int id, string nome, int tamTable){
        int hashValue = geraNumeroHashable(id, nome);
        return 1 + (int)(10*(hashValue*0.61803399-(int)(hashValue*0.61803399)));
    };

    /**
     * LEGACY - Função utilizada para gerar um múmero primo ou com poucos divisores
     * para ser usado no hashing de divisão
     * @param x tamanho do hash
     * @return numero primo ou com poucos divisores
     */
    static int encontraPrimo(int x){

        long long int nNew = ((x * 2 + 3) - 2)/ 2;
        bool* colore = new bool[nNew + 1];
        for(long long int k = 0; k < nNew + 1; k++){
            colore[k] = false;
        }
        int primo = x;

        for(int i = 1; i <= nNew; i++){
            for(long long int j = i;(i + j + 2* i * j) <= nNew; j++){
                try{
                    colore[i + j + 2 * i * j] = true;
                } catch(exception e){
                    break;
                }
            }

            for(long long int k = x/2; k < nNew + 1; k++){
                if(!colore[k] && (k * 2 + 1) > x){
                    primo = k * 2 + 1;
                    break;
                }
            }
        }

        return primo;
    };

private:
    /**
     * Função auxiliar que gera um inteiro a partir do id e do nome inseridos
     * @param id id à ser usado na função
     * @param nome nome à ser usado na função
     * @return inteiro que a função gera a partir do nome e do id
     */
    static int geraNumeroHashable(int id, string nome){
        // Conta as letras pelo asc code
        int totalLetras = 0;
        for(int i = 0; i<nome.length(); i++){
            totalLetras = totalLetras + int(nome.at(i));
        }
        return totalLetras + id;
    };
};


#endif //SRC_HASHFUNCTIONS_H
