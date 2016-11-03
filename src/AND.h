#ifndef __AND_H__
#define __AND_H__

#include "Connector.h"
#include "AND.h"
using namespace std;

class AND: public Connector{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        AND();
        AND(Base* leftChild, Base* rightChild);
        virtual bool runCommand();
};

#endif

