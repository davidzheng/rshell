#ifndef __CONNECTOR_CPP__
#define __CONNECTOR_CPP__

#include <iostream>
#include "Base.h"
#include "Connector.h"

using namespace std;

// Constructors
Connector::Connector(){}

// Member functions
Connector::Connector(Base* leftChild, Base* rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

/*void Connector::printCommand(){ // Testing purposes only
    rightChild->printCommand();
}*/
#endif
