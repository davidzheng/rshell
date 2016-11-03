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
    //fixme
    return false;
}
