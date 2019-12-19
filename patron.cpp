#include "patron.h"

using namespace std;

//----------------------------------------------------------------------------
// Default constructor

Patron::Patron() 
{
    firstName = "";
    lastName = "";
    identification = 0;
}

//----------------------------------------------------------------------------
// parameterized costructor to read in a txt file of patrons

Patron::Patron(istream &is) 
{
    if (is.eof() == false) 
    {
        if (!(is >> identification >> lastName >> firstName)) 
        {
            identification = 0;
            firstName = "";
            lastName = "";
            cout << "ERROR: " << "Error while reading patron from file"
                << endl;
        }
    }
}

//----------------------------------------------------------------------------
// Copy Constructor

Patron::Patron(const Patron &pat) 
{
    identification = pat.identification;
    firstName = pat.firstName;
    lastName = pat.lastName;
}

//----------------------------------------------------------------------------
// Destructor clears table of transactions to clean up memory

Patron::~Patron() 
{
    for (auto t : transactionHistory)
        delete t;
}

//----------------------------------------------------------------------------
// displayHistory() outputs the entire history of specific patrons'
// transactions

void Patron::displayHistory(ostream &os) 
{
    os << "Transaction history of: " << this << " ("
        << transactionHistory.size() << " items)" << endl;;

    for (auto t : transactionHistory) 
    {
        if (t != nullptr) 
            t->display(os);
        else 
        {
            cout << "ERROR: "
                << "Trying to print non-existing transaction"
                << endl;
        }
    }

    os << endl;
}

//----------------------------------------------------------------------------
// addTransaction() pushes a transaction to the list

void Patron::addTransaction(Transaction *t) 
{
    transactionHistory.push_back(t);
}

//----------------------------------------------------------------------------
// valid() makes sure the patron has a valid 4 digit ID number
// and a valid first and lasrt name

bool Patron::valid() 
{
    if ((identification > 0) && (identification <= MAX_ID) &&
        (firstName != "") && (lastName != ""))
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// operator< compares the ID numbers of patrons

bool Patron::operator<(const Patron &pat) 
{
    // only need to check for identification here because
    // this uniquely identifies a patron
    if (identification < pat.identification)
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// operator== checks for duplicates

bool Patron::operator==(const Patron &pat) 
{
    // only need to check for identification here because
    // this uniquely identifies a patron
    if (identification == pat.identification)
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// operator<< outputs patrons based on their info

ostream &operator<<(ostream &os, const Patron *p) 
{
    return os << left << setw(PRINT_WIDTH_ID)
        << p->identification
        << setw(PRINT_WIDTH_NAME)
        << p->lastName.substr(0, PRINT_WIDTH_NAME - 1)
        << setw(PRINT_WIDTH_NAME)
        << p->firstName.substr(0, PRINT_WIDTH_NAME - 1);
}


