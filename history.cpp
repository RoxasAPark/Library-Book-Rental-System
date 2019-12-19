#include "history.h"

#include "patron.h"

//----------------------------------------------------------------------------
// Default Constructor

History::History() 
{
    setType('H');
    setName("History");
}


//----------------------------------------------------------------------------
// Copy Constructor

History::History(const History &h) 
{

}


//----------------------------------------------------------------------------
// Destructor

History::~History() 
{

}


//----------------------------------------------------------------------------
// setBasicInfo() unimplemented because it's a virtual method 

bool History::setBasicInfo(istream &is) 
{
    return true;
}

//----------------------------------------------------------------------------
// create() creates a new History object via inheritance from the transaction
// class and returns it

Transaction *History::create() 
{
    Transaction *h = new History();
    return h;
}

//----------------------------------------------------------------------------
// display() outputs the patron's history of transactions

void History::display(ostream &os) const 
{
    patron->displayHistory(os);
}

//----------------------------------------------------------------------------
// execute() returns true if the output of a patron's history encountered
// no problems

bool History::execute() 
{
    display(cout);
    return true;
}

