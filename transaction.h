#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <string>

#include "libraryItem.h"

using namespace std;

// forwared declaration of Patron to avoid
// circular include statements
class Patron;

// Transaction is a class of objects representing
// various actions patrons can take in a library
// (checking out books, returning books, viewing
// history of all checkouts and returns, etc.)

class Transaction
{
protected:
    //char genre;
    LibraryItem *item{ nullptr };
    Patron *patron{ nullptr };
    char type;
    string name;
public:
    Transaction();
    Transaction(const Transaction&);
    virtual ~Transaction();

    void setType(char t) { type = t; };
    char getType() const { return type; };
    void setName(string n) { name = n; };
    string getName() { return name; };

    virtual Transaction *create() = 0;
    virtual bool setBasicInfo(istream &is) = 0;
    virtual void display(ostream &os) const = 0;
    virtual bool execute() = 0;
    void setPatron(Patron *p);
    void setLibraryItem(LibraryItem *inv);
};

#endif
