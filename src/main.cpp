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
//hashing
#include "hashing/EndSondagemLinear.h"
#include "hashing/EndSondagemQuadratica.h"
//cenarios
#include "cenarios/Cenario1.h"
#include "cenarios/Cenario2.h"
#include "cenarios/Cenario3.h"
#include "cenarios/Cenario4.h"

using namespace std;

void imprimeVetor(int *vetor, int tam){
    cout << "[";
    for(int i=0; i<tam; i++){
        if(i>0){
            cout << ", ";
        }
        cout << vetor[i];
    }
    cout << "]" << endl;
}


int main(int argc, char *argv[])
{
    cout << "---------- INICIO -----------" << endl;

    /*
    int numRegistros = 5;
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

    //////////////////
    cout << endl;

    LeitorUserReviews *userReviews = new LeitorUserReviews(numRegistros);

    UserReview *dataset2 = userReviews->getDataset();

    cout << numRegistros << " registros do arquivo de User Reviews" << endl;


    for(int i=0; i<numRegistros; i++){
        UserReview userReview = dataset2[i];
        cout << "id: " << userReview.id << ", ";
        cout << "user: " << userReview.user << ", ";
        cout << "rating: " << userReview.rating << endl;
    }


    //////////////////
    cout << endl;
*/
/*
    int numRegistros = 50;

    LeitorUsersRated *usersRated = new LeitorUsersRated(numRegistros);

    UsersRated *dataset3 = usersRated->getDataset();

    cout << numRegistros << " registros do arquivo de Users Rated" << endl;

    for(int i=0; i<numRegistros; i++){
        cout << "id: " << dataset3[i].id << ", ";
        cout << "users rated: " << dataset3[i].usersRated << endl;
    }

    uint64_t inicio = unix_timestamp();

    //BubbleSort<UsersRated> *bubbleSort = new BubbleSort<UsersRated>();
    //bubbleSort->ordenar(dataset3, numRegistros);

    InsertionSort<UsersRated> *insertionSort = new InsertionSort<UsersRated>();
    insertionSort->ordenar(dataset3, numRegistros);

    //SelectionSort<UsersRated> *selectionSort = new SelectionSort<UsersRated>();
    //selectionSort->ordenar(dataset3, numRegistros);

    //MergeSort<UsersRated> *mergeSort = new MergeSort<UsersRated>();
    //mergeSort->ordenar(dataset3, 0, numRegistros-1);

    //QuickSort<UsersRated> *quickSort = new QuickSort<UsersRated>();
    //quickSort->ordenar(dataset3, 0, numRegistros-1);
    */
/*
    //calcula o tempo
    uint64_t fim = unix_timestamp();
    double tempo = (fim-inicio)/(double)1000;


    //imprime o vetor

    cout << "registros do arquivo de Users Rated ordenados" << endl;
    for(int i=0; i<numRegistrosUsrRated; i++){
        cout << "id: " << dataset3[i].id << ", ";
        cout << "users rated: " << dataset3[i].usersRated << endl;
    }


    cout << inicio << ", " << fim << endl;

    cout << endl << "Tempo de execucao: " << tempo << " seg" << endl;
    */
/*
    int numRegistrosUsrReview = 10;
    LeitorUserReviews *userReviewsHash = new LeitorUserReviews(numRegistrosUsrReview);
    UserReview *dataset4 = userReviewsHash->getDataset();

    EndSondagemLinear *endSondagemLinear = new EndSondagemLinear(numRegistrosUsrReview);
    endSondagemLinear->resetContadores();

    for(int i=0; i<numRegistrosUsrReview; i++){
        endSondagemLinear->inserir(dataset4[i]);
    }

    endSondagemLinear->imprime();
    cout << "Numero de colisoes: " << endSondagemLinear->getNumColisoes() << endl;
    cout << "Numero de comparacoes: " << endSondagemLinear->getNumComparacoes() << endl;

    EndSondagemQuadratica *endSondagemQuadratica = new EndSondagemQuadratica(numRegistrosUsrReview);
    endSondagemQuadratica->resetContadores();

    for(int i=0; i<numRegistrosUsrReview; i++){
        endSondagemQuadratica->inserir(dataset4[i]);
    }
    endSondagemQuadratica->imprime();
    cout << "Numero de colisoes: " << endSondagemQuadratica->getNumColisoes() << endl;
    cout << "Numero de comparacoes: " << endSondagemQuadratica->getNumComparacoes() << endl;

*/
    cout << "------ Teste dos cenarios -------" << endl;


    //Cenario1* c1 = new Cenario1("Cenario1.txt", "cenario1_teste1.txt");

    //Cenario2* c2 = new Cenario2("Cenario2.txt", "cenario2_teste1.txt");

    Cenario3* c3 = new Cenario3("Cenario3.txt", "cenario3_teste1.txt");
    c3->realizaTeste();

    //Cenario4* c4 = new Cenario4("Cenario4.txt", "cenario4_teste1.txt");

    return 0;
}
/*
6
1000
5000
10000
50000
100000
500000
*/
