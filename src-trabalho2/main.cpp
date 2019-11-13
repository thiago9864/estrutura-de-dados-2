/**
    Universidade Federal de Juiz de Fora
    main.cpp

    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 main.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 main.cpp -o main & main.exe

    @author Lucas Ribeiro, Thiago Almeida
    @version 3.0 18/10/19
*/
#include <iostream>

#include "LeitorBase.h"

//cenarios
#include "cenarios/CenarioArvoreB.h"
#include "cenarios/CenarioArvoreRubroNegra.h"
#include "cenarios/CenarioCompressaoStrings.h"

#include "compressao/FileManager.h"

using namespace std;

void mainMenu();
void cenariosSubMenu();

int main(int argc, char *argv[])
{
    mainMenu();
    return 0;
}

void mainMenu(){
    string userInput;
    LeitorBase base;
    int numberUserInput;
    bool exit = false;

    while(!exit){
        cout << "Qual das partes do trabalho voce quer executar?" << endl;
        cout << "(1) - Arvore B" << endl;
        cout << "(2) - Arvore Vermelho-Preta" << endl;
        cout << "(3) - Compressao de Strings" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        switch (numberUserInput){
            case 1:{
                auto *arvoreB = new CenarioArvoreB("ArvoreB.txt", "ArvoreB "+base.getCurrentDateAsString()+".csv");
                arvoreB->realizaTeste();
                delete arvoreB;
                break;
            }
            case 2:{
                auto *arvoreRubroNegra = new CenarioArvoreRubroNegra("ArvoreRubroNegra.txt", "ArvoreRubroNegra "+base.getCurrentDateAsString()+".csv");
                arvoreRubroNegra->realizaTeste();
                delete arvoreRubroNegra;
                break;
            }
            case 3:{
                auto *compStrings = new CenarioCompressaoStrings("CompressaoStrings.txt", "CompressaoStrings "+base.getCurrentDateAsString()+".csv");
                compStrings->realizaTeste();
                delete compStrings;
                break;
            }
            case 0:{
                exit = true;
                break;
            }
            default:{
                cout << "Valor invalido! Insira outro" << endl;
            }
        }
    }
}
