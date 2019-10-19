/**
    Universidade Federal de Juiz de Fora
    BaseArvores.h
    Propósito: Classe basica para concentrar metodos comuns as duas arvores implementadas

    @author Thiago Almeida
    @version 1.0 18/10/19
*/
#ifndef BASEARVORES_H
#define BASEARVORES_H
#include <iostream>

using namespace std;

/**
 * Classe que serve de base para as arvores
 */
class BaseArvores
{
    public:

        BaseArvores(){};
        ~BaseArvores(){};

        /**
         * Obtem o numero de comparacoes
         * @return uint64_t 
         */
        uint64_t getNumComparacoes(){
            return numComparacoes;
        }

        /**
         * Obtem o numero de copias
         * @return uint64_t 
         */
        uint64_t getNumCopias(){
            return numCopias;
        }

        /**
         * Reseta os contadores de estatisticas
         */
        void resetContadores(){
            numComparacoes = 0;
            numCopias = 0;
        }

        /**
         * Registra a comparacao, esse metodo deve ser chamado no codigo onde
         * tiver uma comparação entre elementos da arvore
         */
        void registraComparacao(){
            numComparacoes++;
        }

        /**
         * Registra a copia, esse metodo deve ser chamado no codigo onde
         * tiver uma copia entre elementos da arvore
         */
        void registraCopia(){
            numCopias++;
        }
        
    private:
        uint64_t numComparacoes;
        uint64_t numCopias;

};

#endif // BASEARVORES_H
