/**
    Universidade Federal de Juiz de Fora
    HashAvaliacoes.h
    Propósito:

    @author Lucas Ribeiro, Thiago Almeida
    @version 1.0 10/10/19
*/


#ifndef SRC_HASHENCSEPARADOAVALIACOES_H
#define SRC_HASHENCSEPARADOAVALIACOES_H

#include <iostream>
#include "../UserReview.h"
#include "HashItemSeparadoParte2.h"
#include "../hash/HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do endereçamento separado
 */
class HashAvaliacoes {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashAvaliacoes(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemSeparadoParte2[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    /**
     * Destrutor do hash
     */
    ~HashAvaliacoes(){
        for(int i = 0; i<this->tamanho; i++){
            if(hashMap[i].prox != nullptr){
                deleteRecursivo(hashMap[i].prox);
            }
        }
        delete[] hashMap;
    };

    /**
     * Insere o item no hash, usando seu metodo respectivo de lidar com as colisões
     * @param item item a ser inserido no hash
     */
    void inserir(string usuario){
        int hs = HashFunctions::divisao(0, usuario, this->tamanho, this->primo);

        //procura o item
        if(contaFrequencia(usuario)){
            //o item já existe e foi incrementada a frequencia
            return;
        }

        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(usuario);
        } else {
            HashItemSeparadoParte2* currentPointer = hashMap[hs].prox;
            if(currentPointer != nullptr){
                this->numComparacoes++;
                this->numColisoes++;
                while(currentPointer->prox != nullptr){
                    this->numComparacoes++;
                    this->numColisoes++;
                    currentPointer = currentPointer->prox;
                }
            }
            else {
                this->numComparacoes++;
                hashMap[hs].prox = new HashItemSeparadoParte2(usuario);
                return;
            }
            currentPointer->prox = new HashItemSeparadoParte2(usuario);
        }
    };

    /**
     * Verifica se um item está inserido no hash
     * @param item item à ser verificado
     * @return booleano indicando se o item existe no hash
     */
    bool buscar(string usuario){
        int hs = HashFunctions::divisao(0, usuario, this->tamanho, this->primo);
        if(hashMap[hs].conteudo == usuario) return true;
        HashItemSeparadoParte2* currentPointer = hashMap[hs].prox;
        if(currentPointer == nullptr) return false;
        while(currentPointer->prox != nullptr){
            if(currentPointer->conteudo == usuario) return true;
            currentPointer = currentPointer->prox;
        }
        return currentPointer->conteudo == usuario;
    }

    /**
     * Verifica se um item está inserido no hash, se estiver, incrementa o contador de frequencia
     * @param categoria item à ser verificado
     * @return booleano indicando se o item foi incrementado
     */
    bool contaFrequencia(string usuario){

        int hs = HashFunctions::divisao(0, usuario, this->tamanho, this->primo);
        /*cout << hs << ", "<<tamanho<<", ";
        cout << hashMap[hs].conteudo << ", ";
        cout << hashMap[hs].conteudo.size() << endl;*/

        if(hashMap[hs].conteudo == usuario){
            //incrementa o contador de frequencia
            hashMap[hs].frequencia++;
            return true;
        }

        HashItemSeparadoParte2* currentPointer = hashMap[hs].prox;
        if(currentPointer == nullptr) return false;
        while(currentPointer->prox != nullptr){
            if(currentPointer->conteudo == usuario){
                //incrementa o contador de frequencia
                currentPointer->frequencia++;
                return true;
            }
            currentPointer = currentPointer->prox;
        }
        return currentPointer->conteudo == usuario;
    }

    /**
     * Retorna o tamanho da lista por trás do hash
     * @return tamanho do hash (ocupado + desocupado)
     */
    int getTamanho() const {
        return tamanho;
    };

    /**
     * Retorna a lista de items que tem por trás do hash
     * @return lista por trás do hash
     */
    HashItemSeparadoParte2 *getHashMap() const {
        return hashMap;
    };

    /**
     * Retorna o número de colisões que ocorreram na inserção desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de colisões que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumColisoes() const {
        return numColisoes;
    };

    /**
     * Retorna o número de comparações que ocorreram na inserção desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de comparações que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumComparacoes() const {
        return numComparacoes;
    };

    /**
     * Reseta os contadores de volta para seu valor inicial (0)
     */
    void resetContadores(){
        numColisoes = 0;
        numComparacoes = 0;
    };

    /**
     * Imprime o hashmap para debug
     */
    void imprime(){
        cout << endl << "------- Imprime a tabela Hash -------" << endl << endl;
        for(int i=0; i<tamanho; i++){
            cout << "#" << i << ": ";
            cout << "id: " << hashMap[i].conteudo << ", ";
            cout << "user: " << hashMap[i].frequencia << ", ";
            cout << "encadeamento: ";
            HashItemSeparadoParte2 *p = hashMap[i].prox;
            while(p != nullptr){
                cout << "{ " << p->conteudo << ", " << p->frequencia << "} ";
                p = p->prox;
            }
            cout << endl;
        }
    }

private:
    int tamanho; // Tamanho do da lista que está sendo utilizado para guardar os items do hash
    HashItemSeparadoParte2* hashMap; // Lista de hashItems sendo usado para guardar os itens inseridos
    int numColisoes; // Contador de colisões
    int numComparacoes; // Contador de comparações
    int primo; // Numero primo sendo utilizado no hash de divisão

    /**
     * Cria um novo item para o hash
     * @param ur Review à ser transformado em um item do hash
     * @return item para ser inserido no hash
     */
    HashItemSeparadoParte2 criaHashItem(string conteudo){
        HashItemSeparadoParte2 h;
        h.conteudo = conteudo;
        h.frequencia = 1;
        h.prox = nullptr;
        return h;
    };

    /**
     * Cria um item vazio para inicializar o hash
     * @return item vazio para o hash
     */
    HashItemSeparadoParte2 criaHashItemVazio(){
        HashItemSeparadoParte2 h;
        h.conteudo = "";
        h.frequencia = 1;
        h.prox = nullptr;
        return h;
    }

    /**
     * Testa se a posição inserida está vazia
     * @param pos posição à ser testada
     * @return booleano indicando se a posição da lista está ocupada ou não
     */
    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].conteudo == "";
    };

    void deleteRecursivo(HashItemSeparadoParte2* deletado){
        if(deletado->prox != nullptr){
            this->deleteRecursivo(deletado->prox);
        }
        delete deletado;
    }
};
#endif //SRC_HASHENCSEPARADOAVALIACOES_H
