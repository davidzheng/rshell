#ifndef __semiColon_H__
#define __semiColon_H__

#include "Connector.h"
#include "semiColon.h"

using namespace std;

class semiColon: public Connector{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        semiColon();
        semiColon(Base* leftChild, Base* rightChild);
        virtual bool runCommand();
        //void printCommand(); // For testing purposes only
};

#endif

