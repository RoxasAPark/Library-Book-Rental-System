#ifndef HISTORY_H_
#define HISTORY_H_

#include "transaction.h"
#include <iostream>
#include <string>

using namespace std;

// Like Checkout and Return, History also
// inherits from the Transaction class.
// History is a transaction that allows
// patrons to view their history of transactions
// they've performed ever since entering the system

class History :public Transaction
{

public:
    History();
    History(const History&);
    ~History();

    virtual bool setBasicInfo(istream &is);
    virtual Transaction *create();
    virtual void display(ostream &os) const;
    virtual bool execute();
};

#endif
