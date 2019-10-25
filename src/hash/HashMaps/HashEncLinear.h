/**
    Universidade Federal de Juiz de Fora
    HashEncLinear.h
    Propósito:

    @author Lucas Ribeiro e Thiago Almeida
    @version 1.0 08/10/19
*/

#ifndef SRC_HASHENCLINEAR_H
#define SRC_HASHENCLINEAR_H

#include <iostream>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do encadeamento linear
 */
class HashEncLinear {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashEncLinear(int tam){
        this->tamanho = tam;
        this->primo = HashFunctions::encontraPrimo(tam);

        // Inicializa hashMap
        this->hashMap = new HashItemBasic[tam];
        for(int i=0; i<tam; i++){
            hashMap[i] = criaHashItemVazio();
        }
    };

    /**
     * Destrutor do hash
     */
    ~HashEncLinear(){
        delete[] hashMap;
    };

    /**
     * Insere o item no hash, usando seu metodo respectivo de lidar com as colisões
     * @param item item a ser inserido no hash
     */
    void inserir(UserReview item){
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);
        if(this->isPosicaoVazia(hs)){
            // não houve colisão - insere na tabela
            hashMap[hs] = criaHashItem(item);
        } else {
            // houve uma colisão - resolver
            // procura a próxima posição vazia na heap pelo metodo linear
            numColisoes++;
            int j=0;// conta a iteração
            int hs_search = hs+1;//auxiliar para percorrer linearmente a tabela
            while(j<tamanho){
                if(hs_search >= tamanho){
                    //chegou no fim do vetor sem resolver, busca do inicio agora
                    hs_search = 0;
                }
                if(isPosicaoVazia(hs_search)){
                    //a colisão foi resolvida
                    hashMap[hs_search] = criaHashItem(item);
                    break;
                } else {
                    numColisoes++;//contabiliza a colisão
                }
                j++;
                hs_search++;
            }
        }
    };

    /**
     * Verifica se um item está inserido no hash
     * @param item item à ser verificado
     * @return booleano indicando se o item existe no hash
     */
    bool buscar(UserReview item){
        //constroi o k com o valor de id e o nome do usuario
        int hs = HashFunctions::divisao(item.id, item.user, this->tamanho, this->primo);

        //verifica a tabela pra ver se o item está lá
        if(hashMap[hs].idRating == item.id){
            return true;
        }

        int j=1;//conta a iteração
        int hs_search = hs+1;//posição do hash
        while(j<tamanho){
            if(hashMap[hs_search].idRating == item.id){
                return true;
            }
            j++;
            hs_search++;
            if(hs_search >= tamanho){
                //chegou no fim do vetor sem resolver, busca do inicio agora
                hs_search = 0;
            }
        }

        return false;
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
    HashItemBasic *getHashMap() const {
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
        numColisoes=0;
        numComparacoes=0;
    }

    /**
     * Imprime o hashmap para debug
     */
    void imprime(){
        cout << endl << "------- Imprime a tabela Hash -------" << endl << endl;
        for(int i=0; i<tamanho; i++){
            cout << "#" << i << ": ";
            cout << "id: " << hashMap[i].idRating << ", ";
            cout << "user: " << hashMap[i].name << endl;
        }
    }
private:
    int tamanho; // Tamanho do da lista que está sendo utilizado para guardar os items do hash
    HashItemBasic* hashMap; // Lista de hashItems sendo usado para guardar os itens inseridos
    int numColisoes; // Contador de colisões
    int numComparacoes; // Contador de comparações
    int primo; // Numero primo sendo utilizado no hash de divisão

    /**
     * Cria um novo item para o hash
     * @param ur Review à ser transformado em um item do hash
     * @return item para ser inserido no hash
     */
    HashItemBasic criaHashItem(UserReview ur){
        HashItemBasic h;
        h.idRating = ur.id;
        h.name = ur.user;
        return h;
    };

    /**
     * Cria um item vazio para inicializar o hash
     * @return item vazio para o hash
     */
    HashItemBasic criaHashItemVazio(){
        HashItemBasic h;
        h.name = "";
        h.idRating = -1;
        return h;
    }

    /**
     * Testa se a posição inserida está vazia
     * @param pos posição à ser testada
     * @return booleano indicando se a posição da lista está ocupada ou não
     */
    bool isPosicaoVazia(int pos){
        numComparacoes++;
        return hashMap[pos].idRating == -1;
    };

};


#endif //SRC_HASHENCLINEAR_H
