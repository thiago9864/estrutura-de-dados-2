cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(hashing)
include_directories(ordenacao)

add_executable(src
    hashing/HashEndAberto.h
    hashing/HashingDuplo.h
    ordenacao/BubbleSort.h
    ordenacao/HeapSort.h
    ordenacao/InsertionSort.h
    ordenacao/MergeSort.h
    ordenacao/QuickSort.h
    ordenacao/QuickSortInsertion.h
    ordenacao/RadixSort.h
    ordenacao/SelectionSort.h
    GameInfo.h
    LeitorBase.h
    LeitorGameInfo.h
    LeitorUserReviews.h
    LeitorUsersRated.h
    Log.h
    main.cpp
    UserReview.h
    UsersRated.h)
