#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "patron.h"
#include "factory.h"
#include "binTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Library objects can manage transactions and the 
// inventory of books the Library object has

class Library
{
private:
    // this table is the self-coded hash table
    // the patron id serves as key.
    // access through the overloaded [] operator
    Patron *patronTable[MAX_ID + 1]{ nullptr };
    binTree invTree[26];
    Factory itemCreator;
public:
    Library();
    Library(const Library&);
    ~Library();

    void displayInventory();
    void displayPatrons();

    bool readPatrons(istream &is);
    bool readLibrary(istream &is);
    bool processCommands(istream &is);

    Patron *operator[] (uint32_t id);
};

#endif

