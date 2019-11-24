/**
    Universidade Federal de Juiz de Fora
    No.h
    Propósito: Implementação de um no generico para as arvores.

    @author 
    @version 1.0 
*/

<<<<<<< Updated upstream
#ifndef NOB_H
#define NOB_H
=======
#ifndef SRC_TRABALHO2_NoB_H
#define SRC_TRABALHO2_No_H

class NoB
{
private:
    int *chave; // Vetor de chaves
    int t; // Grau min
    NoB **C; // vetor de ponteiros dos filhos
    int n; //numero de chaves
    bool folha; // booleano se é folha

public:
    NoB(int t1, bool folha1)
    {
        t = t1;
        folha = folha1;

        chave = new int[2 * t - 1];
        C = new NoB *[2 * t];

        n = 0;
    }

    NoB *procura(int k)
    {
        int i = 0;
        while (i < n && k > chave[i])
            i++;

        if (chave[i] == k)
            return this;

        if (folha == true)
            return NULL;

        return C[i]->procura(k);
    }

    int achachave(int k)
    {
        int idx = 0;
        while (idx < n && chave[idx] < k)
            ++idx;
        return idx;
    }

    void inserenaocheio(int k)
    {
        int i = n - 1;

        if (folha == true)
        {

            while (i >= 0 && chave[i] > k)
            {
                chave[i + 1] = chave[i];
                i--;
            }

            chave[i + 1] = k;
            n = n + 1;
        }
        else
        {

            while (i >= 0 && chave[i] > k)
                i--;

            if (C[i + 1]->n == 2 * t - 1)
            {
                dividefilho(i + 1, C[i + 1]);

                if (chave[i + 1] < k)
                    i++;
            }
            C[i + 1]->inserenaocheio(k);
        }
    }

    void dividefilho(int i, NoB *y)
    {

        NoB *z = new NoB(y->t, y->folha);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->chave[j] = y->chave[j + t];

        if (y->folha == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            chave[j + 1] = chave[j];

        chave[i] = y->chave[t - 1];

        n = n + 1;
    }

    void remove(int k)
    {

        int idx = achachave(k);

        if (idx < n && chave[idx] == k)
        {

            if (folha)
                removefolha(idx);
            else
                removenaofolha(idx);
        }
        else
        {

            if (folha)
            {
                cout << "A chave " << k << " não existe na arvore\n";
                return;
            }

            bool flag = ((idx == n) ? true : false);

            if (C[idx]->n < t)
                preenche(idx);

            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
        return;
    }

    void removefolha(int idx)
    {

        for (int i = idx + 1; i < n; ++i)
            chave[i - 1] = chave[i];

        n--;

        return;
    }

    void removenaofolha(int idx)
    {

        int k = chave[idx];

        if (C[idx]->n >= t)
        {
            int pred = getPred(idx);
            chave[idx] = pred;
            C[idx]->remove(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            int succ = getSucc(idx);
            chave[idx] = succ;
            C[idx + 1]->remove(succ);
        }

        else
        {
            juntar(idx);
            C[idx]->remove(k);
        }
        return;
    }

    int getPred(int idx)
    {

        NoB *cur = C[idx];
        while (!cur->folha)
            cur = cur->C[cur->n];

        return cur->chave[cur->n - 1];
    }
>>>>>>> Stashed changes

#include <iostream>

using namespace std;

/**
 * Classe que ordena uma lista usando o metodo de BubbleSort
 * @tparam T Tipo do item da lista
 */
template <class T>
class NoB
 public:
        No(int t, bool isleaf){
           
           
        };
        ~No(){
            delete[] key;
            delete[] child;
            key = NULL;
            child = NULL;
          
        };   

  // A function to traverse all nodes in a subtree rooted with this node 
    void percorre(){

        { 
    // There are n keys and n+1 children, travers through n keys 
    // and first n children 
    int i; 
    for (i = 0; i < n; i++) 
    { 
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted with child C[i]. 
        if (isLeaf == false) 
            C[i]->percorre();
        cout << " " << keys[i]; 
    } 
  
    // Print the subtree rooted with last child 
    if (isLeaf == false) 
        C[i]->percorre();
} 



    } 
  
    // A function to search a key in the subtree rooted with this node.     
    No *search(int k){ 
    // Find the first key greater than or equal to k 
    int i = 0; 
    while (i < n && k > keys[i]) 
        i++; 
  
    // If the found key is equal to k, return this node 
    if (keys[i] == k) 
        return this; 
  
    // If the key is not found here and this is a leaf node 
    if (leaf == true) 
        return NULL; 
  
    // Go to the appropriate child 
    return C[i]->search(k); 
}    // returns NULL if k is not present. 

 // A utility function to insert a new key in the subtree rooted with 
    // this node. The assumption is, the node must be non-full when this 
    // function is called 
    void inserirNaoCheio(int k){
    { 
    // Initialize index as index of rightmost element 
    int i = n-1; 
  
    // If this is a leaf node 
    if (leaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && keys[i] > k) 
        { 
            keys[i+1] = keys[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        keys[i+1] = k; 
        n = n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && keys[i] > k) 
            i--; 
  
        // See if the found child is full 
        if (C[i+1]->n == 2*t-1) 
        { 
            // If the child is full, then split it 
            dividirFilho(i+1, C[i+1]);
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i+1] < k) 
                i++; 
        } 
        C[i+1]->insertNonFull(k); 
    } 
} 
    // A utility function to split the child y of this node. i is index of y in 
    // child array C[].  The Child y must be full when this function is called 
    void duvidirFilho(int i, BTreeNode *y){
    // Create a new node which is going to store (t-1) keys 
    // of y 
    NoB *z = new NoB(y->t, y->leaf);
    z->n = t - 1; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->C[j] = y->C[j+t]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    // Link the new child to this node 
    C[i+1] = z; 
  
    // A key of y will move to this node. Find the location of 
    // new key and move all greater keys one space ahead 
    for (int j = n-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    // Copy the middle key of y to this node 
    keys[i] = y->keys[t-1]; 
  
    // Increment count of keys in this node 
    n = n + 1; 
}

     void remove(int k)
     {
         int idx = findKey(k);

         // The key to be removed is present in this node
         if (idx < n && keys[idx] == k)
         {

             // If the node is a leaf node - removeFromLeaf is called
             // Otherwise, removeFromNonLeaf function is called
             if (leaf)
                 removeFromLeaf(idx);
             else
                 removeFromNonLeaf(idx);
         }
         else
         {

             // If this node is a leaf node, then the key is not present in tree
             if (leaf)
             {
                 cout << "The key "<< k <<" is does not exist in the tree\n";
                 return;
             }

             // The key to be removed is present in the sub-tree rooted with this node
             // The flag indicates whether the key is present in the sub-tree rooted
             // with the last child of this node
             bool flag = ( (idx==n)? true : false );

             // If the child where the key is supposed to exist has less that t keys,
             // we fill that child
             if (C[idx]->n < t)
                 fill(idx);

             // If the last child has been merged, it must have merged with the previous
             // child and so we recurse on the (idx-1)th child. Else, we recurse on the
             // (idx)th child which now has atleast t keys
             if (flag && idx > n)
                 C[idx-1]->remove(k);
             else
                 C[idx]->remove(k);
         }
         return;
     }

// A function to remove the idx-th key from this node - which is a leaf node
     void removeFromLeaf (int idx)
     {

         // Move all the keys after the idx-th pos one place backward
         for (int i=idx+1; i<n; ++i)
             keys[i-1] = keys[i];

         // Reduce the count of keys
         n--;

         return;
     }

// A function to remove the idx-th key from this node - which is a non-leaf node
     void removeFromNonLeaf(int idx)
     {

         int k = keys[idx];

         // If the child that precedes k (C[idx]) has atleast t keys,
         // find the predecessor 'pred' of k in the subtree rooted at
         // C[idx]. Replace k by pred. Recursively delete pred
         // in C[idx]
         if (C[idx]->n >= t)
         {
             int pred = getPred(idx);
             keys[idx] = pred;
             C[idx]->remove(pred);
         }

             // If the child C[idx] has less that t keys, examine C[idx+1].
             // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
             // the subtree rooted at C[idx+1]
             // Replace k by succ
             // Recursively delete succ in C[idx+1]
         else if  (C[idx+1]->n >= t)
         {
             int succ = getSucc(idx);
             keys[idx] = succ;
             C[idx+1]->remove(succ);
         }

             // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
             // into C[idx]
             // Now C[idx] contains 2t-1 keys
             // Free C[idx+1] and recursively delete k from C[idx]
         else
         {
             merge(idx);
             C[idx]->remove(k);
         }
         return;
     }

// A function to get predecessor of keys[idx]
     int getPred(int idx)
     {
         // Keep moving to the right most node until we reach a leaf
         NoB *cur=C[idx];
         while (!cur->leaf)
             cur = cur->C[cur->n];

         // Return the last key of the leaf
         return cur->keys[cur->n-1];
     }

     int getSucc(int idx)
     {

         // Keep moving the left most node starting from C[idx+1] until we reach a leaf
         NoB *cur = C[idx+1];
         while (!cur->leaf)
             cur = cur->C[0];

         // Return the first key of the leaf
         return cur->keys[0];
     }

// A function to fill child C[idx] which has less than t-1 keys
     void fill(int idx)
     {

         // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
         // from that child
         if (idx!=0 && C[idx-1]->n>=t)
             borrowFromPrev(idx);

             // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
             // from that child
         else if (idx!=n && C[idx+1]->n>=t)
             borrowFromNext(idx);

             // Merge C[idx] with its sibling
             // If C[idx] is the last child, merge it with with its previous sibling
             // Otherwise merge it with its next sibling
         else
         {
             if (idx != n)
                 merge(idx);
             else
                 merge(idx-1);
         }
         return;
     }

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
     void borrowFromPrev(int idx)
     {

         NoB *child=C[idx];
         NoB *sibling=C[idx-1];

         // The last key from C[idx-1] goes up to the parent and key[idx-1]
         // from parent is inserted as the first key in C[idx]. Thus, the  loses
         // sibling one key and child gains one key

         // Moving all key in C[idx] one step ahead
         for (int i=child->n-1; i>=0; --i)
             child->keys[i+1] = child->keys[i];

         // If C[idx] is not a leaf, move all its child pointers one step ahead
         if (!child->leaf)
         {
             for(int i=child->n; i>=0; --i)
                 child->C[i+1] = child->C[i];
         }

         // Setting child's first key equal to keys[idx-1] from the current node
         child->keys[0] = keys[idx-1];

         // Moving sibling's last child as C[idx]'s first child
         if(!child->leaf)
             child->C[0] = sibling->C[sibling->n];

         // Moving the key from the sibling to the parent
         // This reduces the number of keys in the sibling
         keys[idx-1] = sibling->keys[sibling->n-1];

         child->n += 1;
         sibling->n -= 1;

         return;
     }

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
     void borrowFromNext(int idx)
     {

         NoB *child=C[idx];
         NoB *sibling=C[idx+1];

         // keys[idx] is inserted as the last key in C[idx]
         child->keys[(child->n)] = keys[idx];

         // Sibling's first child is inserted as the last child
         // into C[idx]
         if (!(child->leaf))
             child->C[(child->n)+1] = sibling->C[0];

         //The first key from sibling is inserted into keys[idx]
         keys[idx] = sibling->keys[0];

         // Moving all keys in sibling one step behind
         for (int i=1; i<sibling->n; ++i)
             sibling->keys[i-1] = sibling->keys[i];

         // Moving the child pointers one step behind
         if (!sibling->leaf)
         {
             for(int i=1; i<=sibling->n; ++i)
                 sibling->C[i-1] = sibling->C[i];
         }

         // Increasing and decreasing the key count of C[idx] and C[idx+1]
         // respectively
         child->n += 1;
         sibling->n -= 1;

         return;
     }

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
     void merge(int idx)
     {
         NoB *child = C[idx];
         NoB *sibling = C[idx+1];

         // Pulling a key from the current node and inserting it into (t-1)th
         // position of C[idx]
         child->keys[t-1] = keys[idx];

         // Copying the keys from C[idx+1] to C[idx] at the end
         for (int i=0; i<sibling->n; ++i)
             child->keys[i+t] = sibling->keys[i];

         // Copying the child pointers from C[idx+1] to C[idx]
         if (!child->leaf)
         {
             for(int i=0; i<=sibling->n; ++i)
                 child->C[i+t] = sibling->C[i];
         }

         // Moving all keys after idx in the current node one step before -
         // to fill the gap created by moving keys[idx] to C[idx]
         for (int i=idx+1; i<n; ++i)
             keys[i-1] = keys[i];

         // Moving the child pointers after (idx+1) in the current node one
         // step before
         for (int i=idx+2; i<=n; ++i)
             C[i-1] = C[i];

         // Updating the key count of child and the current node
         child->n += sibling->n+1;
         n--;

         // Freeing the memory occupied by sibling
         delete(sibling);
         return;
     }


     friend class ArvoreB;
        
private:
        //parametros correspondentes a arvore B
        int *keys; //vetor que armazena as chaves
        int t;
        No** child; //vetor com os filhos
        int n; //numero de elementos do nó
        //parametros comuns
        bool isLeaf; // true se for nó folha
     
        T value; //Valor ou objeto armazenado

        
};

#endif // NOB_H
