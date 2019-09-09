/**
    Universidade Federal de Juiz de Fora
    LeitorBase.h
    Propósito: Classe com metodos basicos para a leitura 

    @version 1.0 19/08/19
*/
#ifndef LEITORBASE_H
#define LEITORBASE_H
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class LeitorBase
{
    public:

        LeitorBase(){};
        ~LeitorBase(){}; 

        string getDirSep(){
            #ifdef _WIN32
                return "\\";
            #else
                return "/";
            #endif
        }
        const vector<string> explode(const string& s, const char& c)
        {
            string buff{""};
            vector<string> v;
            
            for(auto n:s)
            {
                if(n != c) buff+=n; else
                if(n == c && buff != "") { v.push_back(buff); buff = ""; }
            }
            if(buff != "") v.push_back(buff);
            
            return v;
        }
        void gerarSemente() {
            semente = time(NULL);
            srand (semente);
        } 
        float getRand(int maxRand){
            return rand() % maxRand;
        }
    private:

        int semente;
};

#endif // LEITORBASE_H