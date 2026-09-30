#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"

int main(){
    std::cout<<"Running Tests...\n";
    testAll();
    testAllExtins();
    std::cout<<"Finished LO Tests!"<<std::endl;
}