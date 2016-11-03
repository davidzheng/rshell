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
    //fixme
    return false;
}
