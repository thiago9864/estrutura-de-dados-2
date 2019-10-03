/**
    Universidade Federal de Juiz de Fora
    main.cpp

    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 main.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 main.cpp -o main & main.exe

    @author Thiago Almeida
    @version 1.0 07/08/19
*/
#include <iostream>
#include <time.h>
#include <chrono>

#include "Log.h"
//classes de entidade
#include "UserReview.h"
#include "GameInfo.h"
#include "UsersRated.h"
//classes de leitura
#include "LeitorGameInfo.h"
#include "LeitorUserReviews.h"
#include "LeitorUsersRated.h"
#include "GeradorSequencia.h"
//ordenação
#include "ordenacao/BubbleSort.h"
#include "ordenacao/InsertionSort.h"
#include "ordenacao/SelectionSort.h"
#include "ordenacao/MergeSort.h"
#include "ordenacao/QuickSort.h"
#include "ordenacao/HeapSort.h"
#include "ordenacao/QuickSortInsertion.h"
#include "ordenacao/RadixSort.h"

using namespace std;

void mainMenu();
void ordenacaoSubMenu();
void hashingSubMenu();
void cenariosSubMenu();


uint64_t unix_timestamp()
{
    uint64_t now = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    return now;
}



int main(int argc, char *argv[])
{

    cout << "---------- INICIO -----------" << endl;

    mainMenu();

    /*
    //calcula o tempo
    uint64_t inicio = unix_timestamp();
    //O que deve ser usado fica entre eles
    uint64_t fim = unix_timestamp();
    double tempo = (fim-inicio)/(double)1000;
    */

    return 0;
}

void mainMenu(){
    string userInput;
    int numberUserInput;
    bool exit = false;

    while(!exit){
        cout << "Qual das partes do trabalho voce quer executar?" << endl;
        cout << "(1) - Ordenacao" << endl;
        cout << "(2) - Hashing" << endl;
        cout << "(3) - Cenarios" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        switch (numberUserInput){
            case 1:{
                ordenacaoSubMenu();
                break;
            }
            case 2:{
                hashingSubMenu();
                break;
            }
            case 3:{
                cenariosSubMenu();
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

void ordenacaoSubMenu(){
    string stringNItemsImportados;
    cout << "Quantos itens voce quer importar? ";
    cin >> stringNItemsImportados;
    int nItemsImportados = stoi(stringNItemsImportados);

    auto *usersRated = new LeitorUsersRated(nItemsImportados);
    UsersRated *dataset3 = usersRated->getDataset();
    cout << nItemsImportados << "  Importados com sucesso" << endl << endl;

    string userInput;
    int numberUserInput;
    bool exit = false;
    while(!exit){
        cout << "Qual das partes de ordenacao voce quer executar?" << endl;
        cout << "(1) - BubbleSort" << endl;
        cout << "(2) - HeapSort" << endl;
        cout << "(3) - InsertionSort" << endl;
        cout << "(4) - MergeSort" << endl;
        cout << "(5) - SelectionSort" << endl;
        cout << "(6) - QuickSort" << endl;
        cout << "(7) - QuickSort Insertion" << endl;
        cout << "(8) - RadixSort" << endl;
        cout << "(9) - Mudar o numero de importacoes" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        switch (numberUserInput){
            case 1:{
                auto *bubbleSort = new BubbleSort<UsersRated>();
                bubbleSort->ordenar(dataset3, nItemsImportados);
                break;
            }
            case 2:{
                auto *heapSort = new HeapSort<UsersRated>();
                heapSort->ordenar(dataset3, nItemsImportados - 1);
                break;
            }
            case 3:{
                auto *insertionSort = new InsertionSort<UsersRated>();
                insertionSort->ordenar(dataset3,0 , nItemsImportados - 1);
                break;
            }
            case 4:{
                auto *mergeSort = new MergeSort<UsersRated>();
                mergeSort->ordenar(dataset3, 0, nItemsImportados - 1);
            }
            case 5:{
                auto *selectionSort = new SelectionSort<UsersRated>();
                selectionSort->ordenar(dataset3, nItemsImportados);
                break;
            }
            case 6:{
                auto *quickSort = new QuickSort<UsersRated>();
                quickSort->ordenar(dataset3, 0, nItemsImportados - 1);
                break;
            }
            case 7:{
                string stringNMaxInsertion;
                cout << "A qual o tamanho maximo para o insertionSort ser usado? ";
                cin >> stringNMaxInsertion;
                int nMaxInsertion = stoi(stringNMaxInsertion);
                auto *quickSortInsertion = new QuickSortInsertion<UsersRated>();
                quickSortInsertion->ordenar(dataset3, 0, nItemsImportados - 1, nMaxInsertion);
                break;
            }
            case 8:{
                auto *radixSort = new RadixSort<UsersRated>();
                radixSort->ordenar(dataset3, nItemsImportados);
                break;
            }
            case 9:{
                exit = true;
                ordenacaoSubMenu();
                break;
            }
            case 0:{
                exit = true;
                break;
            }
            default: cout << "Valor invalido! Insira outro" << endl;
        }
    }
}

void hashingSubMenu(){
    string stringNItemsImportados;
    cout << "Quantos itens voce quer importar? ";
    cin >> stringNItemsImportados;
    int nItemsImportados = stoi(stringNItemsImportados);

    auto *userReviews = new LeitorUserReviews(nItemsImportados);
    UserReview *dataset3 = userReviews->getDataset();
    cout << nItemsImportados << "  Importados com sucesso" << endl << endl;

    string userInput;
    int numberUserInput;
    bool exit = false;

    while(!exit){
        cout << "Qual das partes de hashing voce quer executar?" << endl;
        cout << "(1) - Hashing com Endereçamento Linear" << endl;
        cout << "(2) - Hashing com Endereçamento Quadratico" << endl;
        cout << "(3) - Hashing com Duplo Hash" << endl;
        cout << "(4) - Hashing com Encadeamento Separado" << endl;
        cout << "(5) - Hashing com Encadeamento Coalescido" << endl;
        cout << "(9) - Mudar o numero de importacoes" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        switch (numberUserInput){
            case 1:{
                //TODO: Implementar Hashing com Endereçamento Linear
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 2:{
                //TODO: Implementar Hashing com Endereçamento Quadratico
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 3:{
                //TODO: Implementar Hashing com Duplo Hash
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 4:{
                //TODO: Implementar Hashing com Encadeamento Separado
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 5:{
                //TODO: Implementar Hashing com Encadeamento Coalescido
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 9:{
                exit = true;
                hashingSubMenu();
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

void cenariosSubMenu(){
    string userInput;
    int numberUserInput;
    bool exit = false;

    while(!exit){
        cout << "Qual dos cenarios voce quer executar?" << endl;
        cout << "(1) - Cenario 1 - Impacto de diferences estruturas de dados" << endl;
        cout << "(2) - Cenario 2 - Impacto de variacoes do QuickSort" << endl;
        cout << "(3) - Cenario 3 - QuickSort X InsertionSort X MergeSort X HeapSort X MeuSort(RadixSort)" << endl;
        cout << "(4) - Cenario 4 - Tratamento de Colisoes: Enderecamento X Encadeamento" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        switch (numberUserInput){
            case 1:{
                //TODO: Implementar Cenario 1
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 2:{
                //TODO: Implementar Cenario 2
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 3:{
                //TODO: Implementar Cenario 3
                cout << "Codigo solicitado não concluido por enquanto" << endl;
                break;
            }
            case 4:{
                //TODO: Implementar Cenario 4
                cout << "Codigo solicitado não concluido por enquanto" << endl;
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
