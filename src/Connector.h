#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Base.h"

using namespace std;

class Connector: public Base{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        // Constructors
        Connector();
        Connector(Base* leftChild, Base* rightChild);
        // Member functions
        virtual bool runCommand() = 0;       
        void printCommand();
};

#endif
