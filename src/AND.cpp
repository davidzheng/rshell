#ifndef __AND_CPP__
#define __AND_CPP__

#include <iostream>
#include "Base.h"
#include "AND.h"
using namespace std;

// Constructors
AND::AND() {}

AND::AND(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

// Member functions
bool AND::runCommand(){ 
    if(leftChild->runCommand() == true){ // Calls runCommand() on right child if the left child returned true
        if(rightChild->runCommand() == true){ // If right child returns true, AND::runCommand() should return true. Else, return false.
            return true;
        }
    }
    return false;
}

#endif
