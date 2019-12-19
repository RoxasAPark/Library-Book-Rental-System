#include "return.h"

#include "patron.h"

//----------------------------------------------------------------------------
// Default Constructor

Return::Return() 
{
    setType('R');
    setName("Return");
}

//----------------------------------------------------------------------------
// Copy constructor (not implemented since there's no reason to duplicate
// transactions into a hash table)

Return::Return(const Return&) 
{

}

//----------------------------------------------------------------------------
// Destructor
// not implemented because you need the parent class to do 
// the clearing of the data

Return::~Return() 
{

}

//----------------------------------------------------------------------------
// setBasicInfo() 
// not implemented because you already have the parent class
// reading in the transactions

bool Return::setBasicInfo(istream &is) 
{
    return true;
}

//----------------------------------------------------------------------------
// display() displays the subject patron and the item to return

void Return::display(ostream &os) const 
{
    os << " " << name << " ";
    if (item != nullptr)
        item->display(os, false);
    else
        cout << "ERROR: " << "Can't find item for return" << endl;
}

//----------------------------------------------------------------------------
// create() uses a factory to create a Return object

Transaction *Return::create() 
{
    Transaction *r = new Return();
    return r;
}

//----------------------------------------------------------------------------
// execute() returns true if the checkout of an item is successful

bool Return::execute() 
{
    bool result = true;

    if ((patron != nullptr) && (item != nullptr)) 
    {
        // here, the item is "returned"
        item->increaseCopies();
    }
    else 
    {
        if (patron == nullptr)
            cout << "ERROR: "
            << "Can not perform return, no valid patron given!" << endl;
        if (item == nullptr)
            cout << "ERROR: "
            << "Can not perform return, no valid item given!" << endl;

        result = false;
    }
    return result;
}

