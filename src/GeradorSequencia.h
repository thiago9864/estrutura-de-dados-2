/**
    Universidade Federal de Juiz de Fora
    GeradorSequencia.h
    Propósito: Gerador de sequencias aleatorias de inteiros unicos

    @version 1.0 27/09/19
*/
#ifndef GERADORSEQUENCIA_H
#define GERADORSEQUENCIA_H
#include <iostream>

using namespace std;

class GeradorSequencia : protected LeitorBase
{
    public:

        GeradorSequencia(){};
        ~GeradorSequencia(){
            delete[] vetorInt;
            vetorInt = NULL;
        };

        void gerarSequencia(int tamSequencia){

            if(vetorInt != NULL){
                delete[] vetorInt;
                vetorInt = NULL;
            }

            this->tamSequencia = tamSequencia;
            vetorInt = new int[tamSequencia];

            for(int i=0; i<tamSequencia; i++){
                vetorInt[i] = -1;
            }

            gerarSemente();

            int numGerados=0;
            while(numGerados<tamSequencia){
                int rnd = getRand(tamSequencia);

                if(vetorInt[rnd] == -1){
                    vetorInt[rnd] = numGerados;
                    numGerados++;
                }

                //if(numGerados%1000 == 0){
                    //cout << numGerados << endl;
                //}
            }

        }

        int* getDataset(){
            int* copia = new int[tamSequencia];
            for(int i=0; i<tamSequencia; i++){
                copia[i] = vetorInt[i];
            }
            return copia;
        }

        void imprimeVetor(){
            cout << "[";
            for(int i=0; i<tamSequencia; i++){
                if(i>0){
                    cout << ", ";
                }
                cout << vetorInt[i];
            }
            cout << "]" << endl;
        }

    private:
        int *vetorInt=NULL;
        int tamSequencia=0;

};

#endif // GERADORSEQUENCIA_H
