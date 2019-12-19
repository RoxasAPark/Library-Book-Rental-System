#include "book.h"

//----------------------------------------------------------------------------
// Default constructor

Book::Book() : LibraryItem() 
{
    title = " ";
}

//----------------------------------------------------------------------------
// Copy constructor

Book::Book(const Book &book) 
{
    title = book.title;
}


