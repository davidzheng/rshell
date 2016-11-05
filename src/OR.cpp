#ifndef __OR_CPP__
#define __OR_CPP__

#include <iostream>
#include "Base.h"
#include "OR.h"

using namespace std;

// Constructors
OR::OR(){}

OR::OR(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

// Member functions
bool OR::runCommand(){
    if(leftChild->runCommand() == false){ // Calls runCommand() on rightChild if leftChild returned false. Else return true.
	    if(rightChild->runCommand() == true){
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}

#endif
