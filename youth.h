#ifndef YOUTH_H_
#define YOUTH_H_

#include "book.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Youth is a child class since it's 
// a type of Book object

class Youth :public Book
{
private:
    string author{};
    int year{};

public:
    Youth();
    Youth(const Youth& youth);
    virtual ~Youth();

    virtual ostream &display(ostream &os, bool availability = true) const;
    virtual void setBasicInfo(istream &is);
    virtual void setQueryInfo(istream &is);
    virtual void setAdditionalInfo(istream &is);

    virtual bool valid() const;

    virtual bool operator==(const LibraryItem&) const;
    virtual bool operator<(const LibraryItem&) const;

    virtual LibraryItem *create();

    friend ostream &operator<<(ostream &os, Youth *p);
};

#endif

