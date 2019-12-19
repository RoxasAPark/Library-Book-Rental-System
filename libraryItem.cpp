#include "libraryItem.h"

//----------------------------------------------------------------------------
// copy constructor 

LibraryItem::LibraryItem(const LibraryItem &inv) 
{
    maxCopies = inv.maxCopies;
    copiesLeft = inv.copiesLeft;
}

//----------------------------------------------------------------------------
// setNumberOfCopies() assigns each item a number of copies

LibraryItem * LibraryItem::create()
{
	return nullptr;
}

void LibraryItem::setNumberOfCopies(int copies)
{
    maxCopies = copies;
    copiesLeft = copies;
}

//----------------------------------------------------------------------------
// decreaseCopies() is current # of copies - 1

void LibraryItem::decreaseCopies() 
{
    if (copiesLeft > 0)
        copiesLeft--;
}

//----------------------------------------------------------------------------
// increaseCopies() is current # of copies + 1 

void LibraryItem::increaseCopies() 
{
    if (copiesLeft < maxCopies)
        copiesLeft++;
}

//----------------------------------------------------------------------------
// getCopiesLeft() returns the # of copies not checked out to anyone

int LibraryItem::getCopiesLeft() const 
{
    return copiesLeft;
}

//----------------------------------------------------------------------------
// getCopiesCheckedOut() returns the # of copies not returned to the library

int LibraryItem::getCopiesCheckedOut() const 
{
    return (maxCopies - copiesLeft);
}
