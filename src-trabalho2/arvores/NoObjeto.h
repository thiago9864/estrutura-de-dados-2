/**
    Universidade Federal de Juiz de Fora
    No.h
    Propósito: Implementação de um no generico para as arvores.

    @author Thiago Almeida
    @version 1.0 18/10/19
*/

#ifndef NOOBJETO_H
#define NOOBJETO_H

#include <iostream>
#include "../UserReview.h"

using namespace std;


class NoRubroNegro
{
public:
    NoRubroNegro()
    {
        this->isLeaf = false;
        this->parent = nullptr;
        this->color = 1; //o nó começa sempre como vermelho
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    };
    ~NoRubroNegro() 
    {
        parent = nullptr;
        leftChild = nullptr;
        rightChild = nullptr;
    };

    //parametros comuns
    bool isLeaf; // true se for nó folha
    NoRubroNegro *parent;  //ponteiro para o nó superior
    UserReview value;     //Valor ou objeto armazenado

    //parametros correspondentes a arvore Rubro-Negra
    int color;      //0: Preto, 1: Vermelho
    NoRubroNegro *leftChild;  //Filho a esquerda
    NoRubroNegro *rightChild; //Filho a direita
};

#endif // NOOBJETO_H