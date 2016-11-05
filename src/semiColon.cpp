#ifndef __SEMICOLON_CPP__
#define __SEMICOLON_CPP__

#include <iostream>
#include "Base.h"
#include "semiColon.h"

using namespace std;

//Constructors
semiColon::semiColon(){}

semiColon::semiColon(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

/*void semiColon::printCommand(){ // Testing purposes only
    this->rightChild->printCommand();
}*/

// Member functions
bool semiColon::runCommand(){
    leftChild->runCommand(); // Calls runCommand on both children. Returns true if rightChild returns true
    if(rightChild->runCommand() == true){
        return true;
    }
    else{
        return false;
    }
}
#endif
