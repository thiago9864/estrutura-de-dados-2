/**
    Universidade Federal de Juiz de Fora
    HashCategorias.h
    Propósito:

    @author Luan Ciribelli
    @version 1.0 10/10/19
*/

#ifndef SRC_HASHCATEGORIAS_H
#define SRC_HASHCATEGORIAS_H

#include <iostream>
#include "../GameInfo.h"
#include "HashItemSeparadoGameInfo.h"
#include "../hash/HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do endereçamento separado
 */
class HashCategorias {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashCategorias(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemSeparadoGameInfo[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    /**
     * Destrutor do hash
     */
    ~HashCategorias(){
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
    void inserir(GameInfo item){
        //concatena todas as categorias em uma só string pra gerar o hash
        vector<string> categorias = item.boardgamecategory;
        string str_categorias = "";
        for(int i=0; i<categorias.size();i++){
            str_categorias += categorias[i];
        }

        int hs = HashFunctions::divisao(item.id, str_categorias, this->tamanho, this->primo);
        if(this->isPosicaoVazia(hs)){
            hashMap[hs] = criaHashItem(item);
        } else {
            HashItemSeparadoGameInfo* currentPointer = hashMap[hs].prox;
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
                hashMap[hs].prox = new HashItemSeparadoGameInfo(item.id, item.boardgamecategory);
                return;
            }
            currentPointer->prox = new HashItemSeparadoGameInfo(item.id, item.boardgamecategory);
        }
    };

    /**
     * Verifica se um item está inserido no hash
     * @param item item à ser verificado
     * @return booleano indicando se o item existe no hash
     */
    bool buscar(GameInfo item){
        //concatena todas as categorias em uma só string pra gerar o hash
        vector<string> categorias = item.boardgamecategory;
        string str_categorias = "";
        for(int i=0; i<categorias.size();i++){
            str_categorias += categorias[i];
        }

        int hs = HashFunctions::divisao(item.id, str_categorias, this->tamanho, this->primo);

        if(hashMap[hs].idGame == item.id) return true;
        HashItemSeparadoGameInfo* currentPointer = hashMap[hs].prox;
        if(currentPointer == nullptr) return false;
        while(currentPointer->prox != nullptr){
            if(currentPointer->idGame == item.id) return true;
            currentPointer = currentPointer->prox;
        }
        return currentPointer->idGame == item.id;
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
    HashItemSeparadoGameInfo *getHashMap() const {
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
            cout << "idGame: " << hashMap[i].idGame << ", ";

            vector<string> categorias = hashMap[i].boardgamecategory;
            string str_categorias = "";
            for(int i=0; i<categorias.size();i++){
                if(i>0){
                    str_categorias += ", ";
                }
                str_categorias += categorias[i];
            }
            cout << "categorias: " << str_categorias << ", ";
            cout << "encadeamento: ";
            HashItemSeparadoGameInfo *p = hashMap[i].prox;
            while(p != nullptr){
                cout << "{ " << p->idGame << "} ";
                p = p->prox;
            }
            cout << endl;
        }
    }

private:
    int tamanho; // Tamanho do da lista que está sendo utilizado para guardar os items do hash
    HashItemSeparadoGameInfo* hashMap; // Lista de hashItems sendo usado para guardar os itens inseridos
    int numColisoes; // Contador de colisões
    int numComparacoes; // Contador de comparações
    int primo; // Numero primo sendo utilizado no hash de divisão

    /**
     * Cria um novo item para o hash
     * @param GameInfo à ser transformado em um item do hash
     * @return item para ser inserido no hash
     */
    HashItemSeparadoGameInfo criaHashItem(GameInfo gi){
        HashItemSeparadoGameInfo g;
        g.idGame = gi.id;
        g.boardgamecategory = gi.boardgamecategory;
        g.prox = nullptr;
        return g;
    };

    /**
     * Cria um item vazio para inicializar o hash
     * @return item vazio para o hash
     */
    HashItemSeparadoGameInfo criaHashItemVazio(){
        HashItemSeparadoGameInfo g;
        g.boardgamecategory = vector<string>();
        g.idGame = -1;
        g.prox = nullptr;
        return g;
    }

    /**
     * Testa se a posição inserida está vazia
     * @param pos posição à ser testada
     * @return booleano indicando se a posição da lista está ocupada ou não
     */
    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].idGame == -1;
    };

    void deleteRecursivo(HashItemSeparadoGameInfo* deletado){
        if(deletado->prox != nullptr){
            this->deleteRecursivo(deletado->prox);
        }
        delete deletado;
    }
};
#endif //SRC_HASHCATEGORIAS_H
