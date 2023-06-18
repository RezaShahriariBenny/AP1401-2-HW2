#include "gtest/gtest.h"
#include "../include/hw2.h"


#include <iostream>

int main (int argc, char *argv[]) {

    if (true) // make false to run unit tests  
    { 
        //debug Section
    } 
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << RUN_ALL_TESTS() << std::endl;
    }
}