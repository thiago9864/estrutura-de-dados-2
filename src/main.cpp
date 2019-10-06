/**
    Universidade Federal de Juiz de Fora
    main.cpp

    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 main.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 main.cpp -o main & main.exe

    @author Lucas Ribeiro, Thiago Almeida
    @version 2.0 03/10/19
*/
#include <iostream>
#include <time.h>
#include <chrono>

#include "Log.h"
#include "LeitorBase.h"

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

//hashing
#include "hashing/EndSondagemLinear.h"
#include "hashing/EndSondagemQuadratica.h"
//#include "hashing/HashingDuplo.h"

//cenarios
#include "cenarios/Cenario1.h"
#include "cenarios/Cenario2.h"
#include "cenarios/Cenario3.h"
#include "cenarios/Cenario4.h"

using namespace std;

void mainMenu();
void ordenacaoSubMenu();
void hashingSubMenu();
void cenariosSubMenu();

//essa função faz uma copia do dataset, pois os metodos de ordenação modificam o vetor
template <class T>
T* copiaDataset(T *vetor, int tam){
    T *ret = new T[tam];
    for(int i=0; i<tam; i++){
        ret[i] = vetor[i];
    }
    return ret;
}

int main(int argc, char *argv[])
{

    cout << "---------- INICIO -----------" << endl;

    mainMenu();

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
    //medição de tempo
    LeitorBase base;

    string stringNItemsImportados;
    cout << "Quantos itens voce quer importar? ";
    cin >> stringNItemsImportados;
    int nItemsImportados = stoi(stringNItemsImportados);

    auto *usersReviews = new LeitorUserReviews(nItemsImportados);
    UserReview *dataset3 = usersReviews->getDataset();
    cout << nItemsImportados << "  Importados com sucesso" << endl << endl;
    base.salvaVetor("vetor_dataset.csv", dataset3, nItemsImportados);


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
        cout << "(8) - QuickSort Mediana" << endl;
        cout << "(9) - RadixSort" << endl;
        cout << "(10) - Mudar o numero de importacoes" << endl;
        cout << "(0) - Sair" << endl;
        cout << "Numero desejado: ";
        cin >> userInput;
        numberUserInput = stoi(userInput);

        //faz uma copia do dataset pra ser ordenada
        UserReview *aux_dataset = copiaDataset<UserReview>(dataset3, nItemsImportados);

        //base.salvaVetor("vetor_dataset_copia.csv", aux_dataset, nItemsImportados);

        switch (numberUserInput){
            case 1:{
                auto *bubbleSort = new BubbleSort<UserReview>();
                base.timerStart();
                bubbleSort->resetContadores();
                bubbleSort->ordenar(aux_dataset, nItemsImportados);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete bubbleSort;
                bubbleSort = NULL;
                break;
            }
            case 2:{
                auto *heapSort = new HeapSort<UserReview>();
                base.timerStart();
                heapSort->resetContadores();
                heapSort->ordenar(aux_dataset, nItemsImportados);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete heapSort;
                heapSort = NULL;
                break;
            }
            case 3:{
                auto *insertionSort = new InsertionSort<UserReview>();
                base.timerStart();
                insertionSort->resetContadores();
                insertionSort->ordenar(aux_dataset, nItemsImportados);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete insertionSort;
                insertionSort = NULL;
                break;
            }
            case 4:{
                auto *mergeSort = new MergeSort<UserReview>();
                base.timerStart();
                mergeSort->resetContadores();
                mergeSort->ordenar(aux_dataset, 0, nItemsImportados - 1);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete mergeSort;
                mergeSort = NULL;
                break;
            }
            case 5:{
                auto *selectionSort = new SelectionSort<UserReview>();
                base.timerStart();
                selectionSort->resetContadores();
                selectionSort->ordenar(aux_dataset, nItemsImportados);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete selectionSort;
                selectionSort = NULL;
                break;
            }
            case 6:{
                auto *quickSort = new QuickSort<UserReview>();
                base.timerStart();
                quickSort->resetContadores();
                quickSort->ordenar(aux_dataset, 0, nItemsImportados - 1);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete quickSort;
                quickSort = NULL;
                break;
            }
            case 7:{
                //string stringNMaxInsertion;
                //cout << "A qual o tamanho maximo para o insertionSort ser usado? ";
                //cin >> stringNMaxInsertion;
                int nMaxInsertion = 10;//stoi(stringNMaxInsertion);
                auto *quickSortInsertion = new QuickSortInsertion<UserReview>();
                base.timerStart();
                quickSortInsertion->resetContadores();
                quickSortInsertion->ordenar(aux_dataset, 0, nItemsImportados - 1, nMaxInsertion);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete quickSortInsertion;
                quickSortInsertion = NULL;
                break;
            }
            case 8:{
                auto *quickSortMediana = new QuickSortMediana<UserReview>();
                base.timerStart();
                quickSortMediana->resetContadores();
                quickSortMediana->ordenar(aux_dataset, 0, nItemsImportados - 1);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete quickSortMediana;
                quickSortMediana = NULL;
                break;
            }
            case 9:{
                auto *radixSort = new RadixSort<UserReview>();
                base.timerStart();
                radixSort->ordenar(aux_dataset, nItemsImportados);
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl << endl;
                delete radixSort;
                radixSort = NULL;
                break;
            }
            case 10:{
                exit = true;
                delete[] aux_dataset;
                aux_dataset = NULL;
                ordenacaoSubMenu();
                break;
            }
            case 0:{
                exit = true;
                break;
            }
            default: cout << "Valor invalido! Insira outro" << endl;
        }
        if(aux_dataset != NULL){
            delete[] aux_dataset;
            aux_dataset = NULL;
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

    //medição de tempo
    LeitorBase base;

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
                auto *endSondagemLinear = new EndSondagemLinear(nItemsImportados);
                endSondagemLinear->resetContadores();
                base.timerStart();
                //faz a inserção dos registros
                for(int i=0; i<nItemsImportados; i++){
                    endSondagemLinear->inserir(dataset3[i]);
                }
                //resultados
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl;
                cout << "Numero de colisoes: " << endSondagemLinear->getNumColisoes() << endl;
                cout << "Numero de comparacoes: " << endSondagemLinear->getNumComparacoes() << endl << endl;
                delete endSondagemLinear;
                endSondagemLinear = NULL;
                break;
            }
            case 2:{
                auto *endSondagemQuadratica = new EndSondagemQuadratica(nItemsImportados);
                endSondagemQuadratica->resetContadores();
                base.timerStart();
                //faz a inserção dos registros
                for(int i=0; i<nItemsImportados; i++){
                    endSondagemQuadratica->inserir(dataset3[i]);
                }
                //resultados
                cout << "Concluiu em " << base.timerEnd() << " segundos." << endl;
                cout << "Numero de colisoes: " << endSondagemQuadratica->getNumColisoes() << endl;
                cout << "Numero de comparacoes: " << endSondagemQuadratica->getNumComparacoes() << endl << endl;
                delete endSondagemQuadratica;
                endSondagemQuadratica = NULL;
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
    //medição de tempo
    LeitorBase base;

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
                auto *cenario1 = new Cenario1("Cenario1.txt", "cenario1 "+base.getCurrentDateAsString()+".csv");
                cenario1->realizaTeste();
                delete cenario1;
                break;
            }
            case 2:{
                auto *cenario2 = new Cenario2("Cenario2.txt", "cenario2 "+base.getCurrentDateAsString()+".csv");
                cenario2->realizaTeste();
                delete cenario2;
                break;
            }
            case 3:{
                auto *cenario3 = new Cenario3("Cenario3.txt", "cenario3 "+base.getCurrentDateAsString()+".csv");
                cenario3->realizaTeste();
                delete cenario3;
                break;
            }
            case 4:{
                auto *cenario4 = new Cenario4("Cenario4.txt", "cenario4 "+base.getCurrentDateAsString()+".csv");
                cenario4->realizaTeste();
                delete cenario4;
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
