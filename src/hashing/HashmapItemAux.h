#ifndef HASHMAPITEMAUX  _H
#define HASHMAPITEMAUX_H

#include "../UserReview.h"
#include "ListaEncadeada.h"

class HashMapItemAux {
    public:
        int hs;
        float rating;
        string user;
        Lista* a=new Lista;
};

#endif // HASHMAPITEMAUX_H
