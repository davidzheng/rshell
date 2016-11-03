#include <iostream>
#include "Base.h"
#include "OR.h"

using namespace std;

OR::OR(){}

OR::OR(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}


bool OR::runCommand(){
    //fixme
    return false;
}
               
