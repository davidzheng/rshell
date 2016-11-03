#include <iostream>
#include "Base.h"
#include "semiColon.h"

using namespace std;

semiColon::semiColon(){}

semiColon::semiColon(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

bool semiColon::runCommand(){
    leftChild->runCommand();
    if(rightChild->runCommand()){
        return true;
    }
    else{
        return false;
    }
}
