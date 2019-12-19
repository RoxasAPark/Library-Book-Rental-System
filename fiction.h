#ifndef FICTION_H_
#define FICTION_H_

#include "book.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Fiction class inherits from the Book class since it's a type of book

using namespace std;

class Fiction :public Book
{
    friend ostream &operator<<(ostream &os, Fiction *p);

private:
    string author{}; // what fiction books are sorted by
    int year{};
public:
    Fiction();
    Fiction(const Fiction &fiction);
    virtual ~Fiction();

    virtual ostream &display(ostream &os, bool availability = true) const;
    virtual void setBasicInfo(istream&);
    virtual void setQueryInfo(istream &is);
    virtual void setAdditionalInfo(istream&);

    virtual bool valid() const;

    // == and < exist for sorting purposes
    virtual bool operator==(const LibraryItem&) const;
    virtual bool operator<(const LibraryItem&) const;

    virtual LibraryItem *create();
};

#endif
