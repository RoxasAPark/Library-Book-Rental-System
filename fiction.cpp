#include "fiction.h"

//----------------------------------------------------------------------------
// Default constructor

Fiction::Fiction() : Book() 
{

}

//----------------------------------------------------------------------------
// Copy constructor

Fiction::Fiction(const Fiction &fiction) : Book(fiction) 
{

}

//----------------------------------------------------------------------------
// destructor

Fiction::~Fiction() 
{

}

//----------------------------------------------------------------------------
// display() outputs the fiction book if and only if exists
// in the library's inventory of books (LibraryItem class holds the inventory)

ostream &Fiction::display(ostream &os, bool availability) const 
{
    
    if (valid() == true) // if the book exists
    {
        // the book is available if there are any copies left
        stringstream avail{}; 
        avail << to_string(getCopiesLeft()) << "/"
            << to_string(getCopiesLeft() + getCopiesCheckedOut())
            << " available";

        // output all of the info a patron would need to know about the book
        os << left << setw(PRINT_WIDTH_YEAR) << year
            << left << setw(PRINT_WIDTH_AUTHOR)
            << author.substr(0, PRINT_WIDTH_AUTHOR - 1)
            << left << setw(PRINT_WIDTH_TITLE)
            << title.substr(0, PRINT_WIDTH_TITLE - 1);

        if (availability == true)
            os << avail.str() << endl;
        else
            os << endl;

        return os;

    }
    else // if the book doesn't exist in the libary's collection
    {
        cerr << "ERROR: " << "Trying to print invalid fiction!" << endl;
        cerr << "ERROR: " << "year: " << year << " author: " << author
            << " title: " << title << endl;
        return os;
    }
}

//----------------------------------------------------------------------------
// setBasicInfo() reads a list of Fiction book objects from a txt file

void Fiction::setBasicInfo(istream &is) 
{
    if (is.eof() == false) 
    {
        is.get(); // reads space before author
        getline(is, author, ',');
        is.get(); // reads space between , and title
        getline(is, title, ',');
        is >> year;
        is.get(); // reads endline after year
        setNumberOfCopies(5);
        setType('F');
    }
}

//----------------------------------------------------------------------------
// setQueryInfo() has similar behavior to setBasicInfo()
// but the point is Fiction and Book are objects of different formats

void Fiction::setQueryInfo(istream &is) 
{
    if (is.eof() == false) 
    {
        getline(is, author, ',');
        is.get(); // reads space between , and title
        getline(is, title, ',');
        is.get(); // reads endline after year
        setNumberOfCopies(5);
        setType('F');
    }
}

//----------------------------------------------------------------------------
// setAdditionalInfo() is unimplemented here because this method is pure
// virtual in the class Fiction inherits from 

void Fiction::setAdditionalInfo(istream &is) 
{

}

//----------------------------------------------------------------------------
// valid() checks if the Fiction book object exists

bool Fiction::valid() const 
{
    if ((title != "") && (author != ""))
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// create() creates and returns a new Fiction object via a factory

LibraryItem *Fiction::create() 
{
    LibraryItem *f = new Fiction();
    return f;
}

//----------------------------------------------------------------------------
// operator==() checks if the book has the same author and title

bool Fiction::operator==(const LibraryItem &inv) const 
{
    // Two fiction books are equal if they have the same title
    // and author
    return ((title == static_cast<const Fiction &>(inv).title) &&
        (author == static_cast<const Fiction &>(inv).author));
}

//----------------------------------------------------------------------------
// operator<() sorts the books by author
// should the authors be the same, the operator sorts the books by title

bool Fiction::operator<(const LibraryItem &inv) const 
{
    // sorted by author
    if (author < static_cast<const Fiction &>(inv).author) 
    {
        return true;
    }
    else if ((author == static_cast<const Fiction &>(inv).author) &&
        (title < static_cast<const Fiction &>(inv).title)) // same author?
    {
        return true; // then sort by title
    }
    else 
    {
        return false;
    }
}

//----------------------------------------------------------------------------
// operator<< outputs the Fiction books if they exist in the library's
// collection of LibraryItem objects

ostream &operator<<(ostream &os, Fiction *p) 
{
    if (p != nullptr) 
    {
        if (p->valid() == true) // output the book's info if the book exists
        {
            return os << left << setw(PRINT_WIDTH_YEAR) << p->year
                << left << setw(PRINT_WIDTH_AUTHOR)
                << p->author.substr(0, PRINT_WIDTH_AUTHOR - 1)
                << left << setw(PRINT_WIDTH_TITLE)
                << p->title.substr(0, PRINT_WIDTH_TITLE - 1) << endl;

        }
        else 
        {
            cout << "ERROR: " << "Trying to print invalid fiction!" << endl;
            return os;
        }
    }
    else 
    {
        return os;
    }
}
