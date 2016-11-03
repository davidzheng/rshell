#ifndef __OR_H__
#define __OR_H__

#include "Connector.h"
#include "OR.h"

using namespace std;

class OR: public Connector{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        OR();
        OR(Base* leftChild, Base* rightChild);
        virtual bool runCommand();
};

#endif

