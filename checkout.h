#ifndef CHECKOUT_H_
#define CHECKOUT_H_

#include "transaction.h"
#include <iostream>
#include <string>

// Checkout is a derived class inheriting from the
// Transaction class because Checkout is a type of
// transaction a patron can make

using namespace std;

class Patron;

class Checkout :public Transaction
{
public:
    Checkout(); // default constructor
    Checkout(const Checkout&); // copy constructor
    ~Checkout(); // destructor to clean up memory

    virtual bool setBasicInfo(istream &is);

	// display the transaction (patron and item)
    virtual void display(ostream &os) const;
    virtual Transaction *create();

    // prevents us from needing switches to process
    // transactions
    virtual bool execute();
};

#endif
