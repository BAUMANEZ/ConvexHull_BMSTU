//
//  main.cpp
//  Travelling Salesman
//
//  Created by Арсений Токарев on 07.05.2021.
//
#ifndef RoutesGenerator
#define RoutesGenerator

#include <iostream>
#include <fstream>
#include "Helpers/Algorithms.cpp"

int main(int argc, const char * argv[]) {
    //auto routes1 = Routes(INPUT_FILE_PATH);
    //routes1.run(1);
    TwoOptAlgorithm().run();
    return 0;
}

#endif
