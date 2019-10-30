/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar a arvore B

    @author: Luan Reis Ciribelli
    @version 1.0 27/10/2019

https://www.geeksforgeeks.org/introduction-of-b-tree-2/
https://www.geeksforgeeks.org/insert-operation-in-b-tree/
https://www.geeksforgeeks.org/delete-operation-in-b-tree/

*/

#ifndef SRC_TRABALHO2_ARVOREB_H
#define SRC_TRABALHO2_ARVOREB_H

#include <iostream>
#include "BaseArvores.h"
#include "No.h"

Class ArvoreB : protected BaseArvores
{
private:
    No raiz;
 
    int t;
public:
//Construtor vazio
  
   
   arvoreB(int t){

        raiz = NULL;  this.t =t; 

   }

    bool buscachave(No x)
    {

        return (raiz == NULL)? NULL : raiz->search(k);
    }

    void Percorre() 
    {  if (raiz != NULL) raiz->traverse(); } 

   NoB::NoB(int _t, bool _leaf) 
{ 
    // Copy the given minimum degree and leaf property 
    t = _t; 
    isLeaf = _leaf; 
  
    // Allocate memory for maximum number of possible keys 
    // and child pointers 
    keys = new int[2*t-1]; 
    C = new NoB *[2*t]; 
  
    // Initialize the number of keys as 0 
    n = 0; 
} 
void inserir(int K)
{
  
    // If tree is empty 
    if (root == NULL) 
    { 
        // Allocate memory for root 
        raiz = new NoB(t, true); 
        raiz->keys[0] = k;  // Insert key 
        raiz->n = 1;  // Update number of keys in root 
    } 
    else // If tree is not empty 
    { 
        // If root is full, then tree grows in height 
        if (raiz->n == 2*t-1) 
        { 
            // Allocate memory for new root 
            NoB *s = new NoB(t, false); 
  
            // Make old root as child of new root 
            s->C[0] = root; 
  
            // Split the old root and move 1 key to the new root 
            s->splitChild(0, raiz); 
  
            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0; 
            if (s->keys[0] < k) 
                i++; 
            s->C[i]->insertNonFull(k); 
  
            // Change root 
            raiz = s; 
        } 
        else  // If root is not full, call insertNonFull for root 
            raiz->insertNonFull(k); 
    } 
} 
   


};

#endif //SRC_TRABALHO2_ARVOREB_H
