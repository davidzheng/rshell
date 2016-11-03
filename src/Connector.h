#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Base.h"

using namespace std;

class Connector: public Base{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        Connector();
        Connector(Base* leftChild, Base* rightChild);
        virtual bool runCommand() = 0;        
};

#endif
