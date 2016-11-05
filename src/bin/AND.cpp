#ifndef __AND_CPP__
#define __AND_CPP__

#include <iostream>
#include "Base.h"
#include "AND.h"
using namespace std;

AND::AND() {}

AND::AND(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

bool AND::runCommand(){
    if(leftChild->runCommand() == true)
    {
        if(rightChild->runCommand() == true)
        {
            return true;
        }
    }
    return false;
}

#endif
