#ifndef RETURN_H_
#define RETURN_H_

#include "libraryItem.h"
#include "transaction.h"
#include <iostream>
#include <string>

using namespace std;

class Return :public Transaction
{

public:
    Return();
    Return(const Return&);
    virtual ~Return();

    virtual bool setBasicInfo(istream &is);
    virtual void display(ostream &os) const;
    virtual Transaction *create();
    virtual bool execute();
};

#endif

