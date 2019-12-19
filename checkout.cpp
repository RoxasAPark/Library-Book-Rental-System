#include "checkout.h"

#include "patron.h"

//----------------------------------------------------------------------------
// Default Constructor

Checkout::Checkout() 
{
    setType('C');
    setName("Checkout");
}

//----------------------------------------------------------------------------
// Copy constructor (not implemented since there's no reason to duplicate
// transactions into a hash table)

Checkout::Checkout(const Checkout&) 
{

}

//----------------------------------------------------------------------------
// Destructor
// not implemented because you need the parent class to do 
// the clearing of the data

Checkout::~Checkout() 
{

}

//----------------------------------------------------------------------------
// setBasicInfo() 
// not implemented because you already have the parent class
// reading in the transactions

bool Checkout::setBasicInfo(istream &is) 
{
    return true;
}

//----------------------------------------------------------------------------
// display() isplay the full transaction

void Checkout::display(ostream &os) const 
{
    os << " " << name << " ";
    if (item != nullptr)
        item->display(os, false);
    else
        cout << "ERROR: " << "Can't find item for checkout" 
		<< endl;
}

//----------------------------------------------------------------------------
// create() uses a factory to create the transaction object

Transaction *Checkout::create() 
{
    Transaction *c = new Checkout();
    return c;
}

//----------------------------------------------------------------------------
// execute() returns true if the checkout of an item is successful

bool Checkout::execute() 
{
    bool result = true;

    if ((patron != nullptr) && (item != nullptr)) 
    {
        if (item->getCopiesLeft() > 0) // checkout operation 
            item->decreaseCopies();
        else 
        {
            cout << "ERROR: " << "Can't check out item (";
            //item->display(cerr);
            cout << "), no copies left!" << endl;
        }
    }
    else 
    {
        if (patron == nullptr) // invalid patron
            cout << "ERROR: "
            << "Can't perform checkout, no valid patron given!" 
            << endl;
        if (item == nullptr) // invalid item
            cout << "ERROR: "
            << "Can't perform checkout, no valid item given!" 
            << endl;

        result = false;
    }
    return result;
}

