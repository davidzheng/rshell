#ifndef __OR_H__
#define __OR_H__

#include "Base.h"

using namespace std;

class OR: public Base{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        OR();
        OR(Base* leftChild, Base* rightChild);
        virtual bool runCommand() = 0;
};

#endif

