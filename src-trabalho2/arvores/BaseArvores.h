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
#include "../Contador.h"

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
         * @return int
         */
        int getNumComparacoes(){
            return numComparacoes + Contador::getInstance().getNumComparacoes();
        }

        /**
         * Obtem o numero de copias
         * @return int
         */
        int getNumCopias(){
            return numCopias + Contador::getInstance().getNumCopias();
        }

        /**
         * Reseta os contadores de estatisticas
         */
        void resetContadores(){
            numComparacoes = 0;
            numCopias = 0;
            Contador::getInstance().resetContadores();
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
        int numComparacoes;
        int numCopias;

};

#endif // BASEARVORES_H
