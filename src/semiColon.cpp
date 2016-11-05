#ifndef __SEMICOLON_CPP__
#define __SEMICOLON_CPP__

#include <iostream>
#include "Base.h"
#include "semiColon.h"

using namespace std;

semiColon::semiColon(){}

semiColon::semiColon(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}
/*void semiColon::printCommand(){ // Testing purposes only
    this->rightChild->printCommand();
}*/
bool semiColon::runCommand(){
    leftChild->runCommand();
    if(rightChild->runCommand() == true){
        return true;
    }
    else{
        return false;
    }
}
#endif
