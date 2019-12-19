#ifndef PERIODICAL_H_
#define PERIODICAL_H_

#include "book.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Periodical :public Book
{
private:
    int year;
    int month;
public:
    Periodical();
    Periodical(const Periodical&);
    virtual ~Periodical();

    virtual ostream &display(ostream &os, bool availability = true) const;
    virtual void setBasicInfo(istream &is);
    void setBasicInfo(int y, int m, string t);
    void setQueryInfo(istream &is);
    virtual void setAdditionalInfo(istream &is);
    int getYear() { return year; };
    int getMonth() { return month; };

    virtual bool valid() const;

    virtual bool operator==(const LibraryItem&) const;
    virtual bool operator<(const LibraryItem&) const;

    virtual LibraryItem *create();

    friend ostream &operator<<(ostream &os, Periodical *p);
};

#endif

