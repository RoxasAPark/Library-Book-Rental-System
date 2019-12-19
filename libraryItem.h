#ifndef LIBRARYITEM_H_
#define LIBRARYITEM_H_

#include <string>
#include <iostream>

using namespace std;

#define PRINT_WIDTH_YEAR    5
#define PRINT_WIDTH_MONTH   6
#define PRINT_WIDTH_TITLE   37
#define PRINT_WIDTH_AUTHOR  23

// LibraryItem is a class of items the Library object
// stores in a collection so patrons can check them out,
// return them, and display information about them via
// the library system itself

class LibraryItem
{
private:
    int copiesLeft;
    int maxCopies;
    char type;
public:
    LibraryItem() {};
    LibraryItem(const LibraryItem &inv);

	// destructor has to be virtual because there are
	// classes inheriting data from this one

    virtual ~LibraryItem() {};
	virtual LibraryItem* create();

    void setNumberOfCopies(int copies);
    void decreaseCopies();
    void increaseCopies();

    int getCopiesLeft() const;
    int getCopiesCheckedOut() const;

    char getType() const { return type; };
    void setType(char t) { type = t; };

    virtual bool valid() const = 0;

    virtual ostream &display(ostream &os, bool availability = true) const = 0;
    virtual void setBasicInfo(istream&) = 0;
    virtual void setQueryInfo(istream&) = 0;
    virtual void setAdditionalInfo(istream&) = 0;

    //virtual string getItem() = 0;
    virtual bool operator<(const LibraryItem&) const = 0;
    virtual bool operator==(const LibraryItem&) const = 0;
};

#endif

