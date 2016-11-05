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
        // Constructors
        semiColon();
        semiColon(Base* leftChild, Base* rightChild);
        // Member functions
        virtual bool runCommand();
        //void printCommand(); // For testing purposes only
};

#endif

