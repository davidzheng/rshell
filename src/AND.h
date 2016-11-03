#ifndef __AND_H__
#define __AND_H__

#include "Base.h"
using namespace std;

class AND: public Base{
    protected:
        Base* leftChild;
        Base* rightChild;
    public:
        AND();
        AND(Base* leftChild, Base* rightChild);
        virtual bool runCommand() = 0;
};

#endif

