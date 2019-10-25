/**
    Universidade Federal de Juiz de Fora
    HashEncQuadratrico.h
    Propósito:

    @author Lucas Ribeiro e Thiago Almeida
    @version 1.0 08/10/19
*/


#ifndef SRC_HASHENCQUADRATICO_H
#define SRC_HASHENCQUADRATICO_H

#include <iostream>
#include <cmath>
#include "../../UserReview.h"
#include "../Items/HashItemBasic.h"
#include "../HashFunctions.h"

using namespace std;

/**
 * Hash que resolve suas colisões pelo metodo do encadeamento quadratico
 */
class HashEncQuadratico {
public:

    /**
     * Construtor do hash
     * @param tam tamanho da lista que vai guardar o hash
     */
    HashEncQuadratico(int tam){
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
    ~HashEncQuadratico(){
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
            numColisoesQuad++;
            int j=1;// conta a iteração
            int hs_search = hs+1;//auxiliar para percorrer linearmente a tabela
            resolvendoComHashQuadratico=true;//inicia com hash quadratico

            while(j<tamanho){
                if(hs_search >= tamanho){
                    //fim do vetor, tenta pegar do inicio com a diferença restante
                    hs_search -= tamanho;

                    if(hs_search >= tamanho){
                        //se ainda for maior que o tamanho da tabela, muda de estratégia
                        resolvendoComHashQuadratico=false;
                        numMudancasEstrategia++;
                        hs_search=hs+1;//vai resetar a posição do hash pra tentar o linear
                        j=1;
                    }
                }

                if(isPosicaoVazia(hs_search)){
                    //a colisão foi resolvida
                    hashMap[hs_search] = criaHashItem(item);
                    break;
                } else {
                    if(resolvendoComHashQuadratico){
                        numColisoesQuad++;//contabiliza a colisão quadratica
                    } else {
                        numColisoesLin++;
                    }
                }

                //calcula o proximo salto
                if(resolvendoComHashQuadratico){
                    //estrategia para sondagem quadrática
                    hs_search = hs + pow(2, j);
                } else {
                    //estrategia para sondagem linear
                    hs_search++;
                }
                j++;
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

        resolvendoComHashQuadratico=true;

        int j=1;//conta a iteração
        int hs_search = hs+1;//posição do hash
        while(j<tamanho){
            if(hs_search >= tamanho){
                //fim do vetor, tenta pegar do inicio com a diferença restante
                hs_search -= tamanho;

                if(hs_search >= tamanho){
                    //se ainda for maior que o tamanho da tabela, muda de estratégia
                    resolvendoComHashQuadratico=false;
                    hs_search=hs+1;//vai resetar a posição do hash pra tentar o linear
                    j=1;
                }
            }

            //compara pra ver se encontrou
            if(hashMap[hs_search].idRating == item.id){
                return true;
            }

            //calcula o proximo salto
            if(resolvendoComHashQuadratico){
                //estrategia para sondagem quadrática
                hs_search = hs + pow(2, j);
            } else {
                //estrategia para sondagem linear
                hs_search++;
            }

            j++;
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
     * Retorna o número de colisões que ocorreram na inserção, enquanto na estrategia quadratica, desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de colisões quadraticas que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumColisoesQuadraticas() const {
        return numColisoesQuad;
    };

    /**
     * Retorna o número de colisões que ocorreram na inserção, enquanto na estrategia linear, desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de colisões lineares que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumColisoesLineares() const {
        return numColisoesLin;
    };

    /**
     * Retorna o número de vezes que foi utilizada uma mudança de estrategia durante a inserção desde o ultimo resetContadores ou da criação do hash
     * (Caso resetContadores nunca tenha sido usado)
     * @return número de mudanças de estrategia que ocorreram na inserção desde quando a contagem começou pela ultima vez
     */
    int getNumMudancasDeEstrategia() const {
        return numMudancasEstrategia;
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
        numMudancasEstrategia=0;
        numColisoesLin=0;
        numColisoesQuad=0;
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
    int numColisoesQuad; // Contador de colisões quadraticas
    int numColisoesLin; // Contador de colisões lineares
    int numMudancasEstrategia; // Contador de mudanças de estrategia
    int numComparacoes; // Contador de comparações
    bool resolvendoComHashQuadratico; // Indicador do tipo de resolução de conflito sendo usado atualmente
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


#endif //SRC_HASHENCQUADRATICO_H
