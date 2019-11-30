/**
    Universidade Federal de Juiz de Fora
    Contador.h
    Propósito: Registra contagem da arvore b.

    @author Thiago Almeida
    @version 1.0 29/11/19
*/

#ifndef CONTADOR_H
#define CONTADOR_H

#include <iostream>
#include <string>

using namespace std;

class Contador {

public:
    static Contador& getInstance()
    {
        static Contador instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

private:
    Contador() {} // Constructor? (the {} brackets) are needed here.
    ~Contador(){
        // Destructor
        resetContadores();
    }

    // C++ 03
    // ========
    // Don't forget to declare these two. You want to make sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    Contador(Contador const&);       // Don't Implement
    void operator=(Contador const&); // Don't implement

    int numComparacoes;
    int numCopias;

public:

    /**
     * Obtem o numero de comparacoes
     * @return int
     */
    int getNumComparacoes(){
        return numComparacoes;
    }

    /**
     * Obtem o numero de copias
     * @return int
     */
    int getNumCopias(){
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

    
};


#endif //CONTADOR_H
