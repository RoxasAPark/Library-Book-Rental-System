#include "transaction.h"

//----------------------------------------------------------------------------
// default constructor

Transaction::Transaction() 
{

}

//----------------------------------------------------------------------------
// copy constructor

Transaction::Transaction(const Transaction&) 
{

}

//----------------------------------------------------------------------------
// destructor

Transaction::~Transaction() 
{
    if (item != nullptr) 
    {
        // set item to nullptr - will be deleted, when
        // library is destroyed
        item = nullptr;
    }
}

//----------------------------------------------------------------------------
// create() is a virtual method

Transaction *Transaction::create() 
{
    return nullptr;
}

//----------------------------------------------------------------------------
// setPatron() gets a patron assigned to a transaction

void Transaction::setPatron(Patron *p) 
{
    patron = p;
}

//----------------------------------------------------------------------------
// setLibraryItem() sets the item of interest to the transaction

void Transaction::setLibraryItem(LibraryItem *inv) 
{
    item = inv;
}


