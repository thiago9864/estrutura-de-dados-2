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

//#include "Memoria.h"
#include "Log.h"
//classes de entidade
#include "UserReview.h"
#include "GameInfo.h"
#include "UsersRated.h"
//classes de leitura
#include "LeitorGameInfo.h"
#include "LeitorUserReviews.h"
#include "LeitorUsersRated.h"
//ordenação
#include "ordenacao/BubbleSort.h"
#include "ordenacao/InsertionSort.h"
#include "ordenacao/SelectionSort.h"
#include "ordenacao/MergeSort.h"
#include "ordenacao/QuickSort.h"
#include "ordenacao/Heapsort.h"

using namespace std;

uint64_t unix_timestamp()
{
    uint64_t now = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    return now;
}

int main(int argc, char *argv[])
{
    //Memoria memInfo;
    //cout << "Uso de memoria atual: " << memInfo.getCurrentRSS() << endl;
    //int peakMemoryIni = memInfo.getPeakRSS();

    cout << "---------- INICIO -----------" << endl;
    /*
    int numRegistros = 100;
    LeitorGameInfo *gameInfo = new LeitorGameInfo(numRegistros);

    GameInfo *dataset = gameInfo->getDataset();

    cout << numRegistros << " registros do arquivo de Game Info" << endl;


    for(int i=0; i<numRegistros; i++){
        GameInfo gameInfo = dataset[i];
        cout << "id: " << gameInfo.id << ", boardgamecategory: ";
        for(int j=0; j<gameInfo.boardgamecategory.size(); j++){
            cout << gameInfo.boardgamecategory[j] << ", ";
        }
        cout << endl;
    }
    */
    //////////////////
    cout << endl;
    /*
    LeitorUserReviews *userReviews = new LeitorUserReviews(numRegistros);

    UserReview *dataset2 = userReviews->getDataset();

    cout << numRegistros << " registros do arquivo de User Reviews" << endl;


    for(int i=0; i<numRegistros; i++){
        UserReview userReview = dataset2[i];
        cout << "id: " << userReview.id << ", ";
        cout << "user: " << userReview.user << ", ";
        cout << "rating: " << userReview.rating << endl;
    }
    */

    //////////////////
    cout << endl;

    int numRegistrosUsrRated = 5;
    LeitorUsersRated *usersRated = new LeitorUsersRated(numRegistrosUsrRated);

    UsersRated *dataset3 = usersRated->getDataset();

    cout << numRegistrosUsrRated << " registros do arquivo de Users Rated" << endl << endl;

    for(int i=0; i<numRegistrosUsrRated; i++){
        cout << "id: " << dataset3[i].id << ", ";
        cout << "users rated: " << dataset3[i].usersRated << endl;
    }

    uint64_t inicio = unix_timestamp();
    BubbleSort<UsersRated> *bubbleSort = new BubbleSort<UsersRated>();
    bubbleSort->ordenar(dataset3, numRegistrosUsrRated);

    InsertionSort<UsersRated> *insertionSort = new InsertionSort<UsersRated>();
    insertionSort->ordenar(dataset3, numRegistrosUsrRated);

    SelectionSort<UsersRated> *selectionSort = new SelectionSort<UsersRated>();
    selectionSort->ordenar(dataset3, numRegistrosUsrRated);

    MergeSort<UsersRated> *mergeSort = new MergeSort<UsersRated>();
    mergeSort->ordenar(dataset3, 0, numRegistrosUsrRated-1);

    QuickSort<UsersRated> *quickSort = new QuickSort<UsersRated>();
    quickSort->ordenar(dataset3, 0, numRegistrosUsrRated-1);

    //HeapSort<UsersRated> *heapSort = new HeapSort<UsersRated>();
    //heapSort->ordenar(dataset3, numRegistrosUsrRated-1);

    //calcula o tempo
    uint64_t fim = unix_timestamp();
    double tempo = (fim-inicio)/(double)1000;


    //imprime o vetor

    cout << endl << "registros do arquivo de Users Rated ordenados" << endl <<endl;
    for(int i=0; i<numRegistrosUsrRated; i++){
        cout << "id: " << dataset3[i].id << ", ";
        cout << "users rated: " << dataset3[i].usersRated << endl;
    }


    //cout << inicio << ", " << fim << endl;

    cout << endl << "Tempo de execucao: " << tempo << " seg" << endl;
    /*
    int memUsada = memInfo.getPeakRSS() - peakMemoryIni;
    float memUsadaKB = memUsada / (float)1024;
    //cout << "Uso de memoria atual: " << memInfo.getCurrentRSS() << endl;
    if(memUsada < 1024){
        cout << "Maximo de memoria usada: " << memUsada << " Bytes" << endl;
    } else if(memUsadaKB < 1024){
        cout << "Maximo de memoria usada: " << memUsadaKB << "Kb" << endl;
    } else {
        float memUsadaMB = memUsadaKB / (float)1024;
        cout << "Maximo de memoria usada: " << memUsadaMB << "Mb" << endl;
    }
    */

    return 0;
}
