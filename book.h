#ifndef BOOK_H_
#define BOOK_H_

#include "libraryItem.h"
#include <iostream>
#include <string>

//----------------------------------------------------------------------------
// Book is a derived class that inherits from the LibraryItem class.
// A Book is a special type of a LibraryItem object that holds the title
// since books have titles. 

using namespace std;

class Book: public LibraryItem
{
protected:
    string title{}; // all books must have a title 
public:
    Book(); // default constructor
    Book(const Book&); // copy constructor
    virtual ~Book() {}; // destructor is virtual because it's a parent class

    virtual ostream &display(ostream &os, bool avail = true) const = 0;

    virtual void setBasicInfo(istream &is) = 0;
    virtual void setQueryInfo(istream &is) = 0;
    virtual void setAdditionalInfo(istream &is) = 0;
    string getTitle() { return title; };

    // checks if the LibraryItem object exists in the library's collection
    // of LibraryUten objects

    virtual bool valid() const = 0;

    // operators == and < exist for sorting purposes
    virtual bool operator==(const LibraryItem&) const = 0;
    virtual bool operator<(const LibraryItem&) const = 0;

    // uses a factory to create Book objects
    // purpose: to avoid switches and redundantly using new
    // every time we want to add more books to the library

    virtual LibraryItem *create() = 0;
};

#endif
