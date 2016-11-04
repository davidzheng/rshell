#include <iostream>
#include "Base.h"
#include "Connector.h"

using namespace std;

Connector::Connector(){}

Connector::Connector(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

void Connector::printCommand(){
    rightChild->printCommand();
}
