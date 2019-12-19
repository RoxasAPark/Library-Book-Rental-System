#include "youth.h"

//----------------------------------------------------------------------------
// Default Constructor

Youth::Youth() : Book() 
{
    author = "";
}

//----------------------------------------------------------------------------
// Copy constructor

Youth::Youth(const Youth &youth) : Book(youth)
{
    author = youth.author;
    year = youth.year;
}

//----------------------------------------------------------------------------
// Destructor is virtual

Youth::~Youth() 
{

}

//----------------------------------------------------------------------------
// display() outputs the youth book

ostream &Youth::display(ostream &os, bool availability) const 
{
    if (valid() == true) 
    {
        stringstream avail{};
        avail << to_string(getCopiesLeft()) << "/"
            << to_string(getCopiesLeft() + getCopiesCheckedOut())
            << " available";

        os << left << setw(PRINT_WIDTH_YEAR) << year
            << left << setw(PRINT_WIDTH_TITLE)
            << title.substr(0, PRINT_WIDTH_TITLE - 1)
            << left << setw(PRINT_WIDTH_AUTHOR)
            << author.substr(0, PRINT_WIDTH_AUTHOR - 1);

        if (availability == true)
            os << avail.str() << endl;
        else
            os << endl;

        return os;

    }
    else 
    {
        cout << "ERROR: " << "Trying to print invalid youth!" 
            << endl;
        return os;
    }
}

//----------------------------------------------------------------------------
// setBasicInfo() reads the list of books from a txt file

void Youth::setBasicInfo(istream &is)
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
        setType('Y');
    }
}

//----------------------------------------------------------------------------
// setQueryInfo() just doesn't have spaces before data

void Youth::setQueryInfo(istream &is) 
{
    if (is.eof() == false) 
    {
        getline(is, title, ',');
        is.get(); // reads space between , and author 
        getline(is, author, ',');
        is.get(); // reads endline after author
        setNumberOfCopies(5);
        setType('Y');
    }
}

//----------------------------------------------------------------------------
// setAdditionalInfo() is virtual

void Youth::setAdditionalInfo(istream &is) 
{

}

//----------------------------------------------------------------------------
// valid() verifies the Youth books have a title and an author

bool Youth::valid() const 
{
    if ((title != "") && (author != ""))
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// create() uses factory to create a Youth book object

LibraryItem *Youth::create() 
{
    LibraryItem *y = new Youth();
    return y;
}

bool Youth::operator==(const LibraryItem &inv) const 
{
    // Two youth books are equal if the have the same title
    // and author.
    // The year can not be checked here because the
    // checkouts and returns in the command file do not 
    // give a year.
    if ((title == static_cast<const Youth &>(inv).title) &&
        (author == static_cast<const Youth &>(inv).author))
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// operator< exists for sorting purposes

bool Youth::operator<(const LibraryItem &inv) const 
{
    // first sorted by title
    if (title < static_cast<const Youth &>(inv).title) 
        return true;
        // if equal, sorted by author
    else if ((title == static_cast<const Youth &>(inv).title)
        && (author < static_cast<const Youth &>(inv).author)) 
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// operator<<() ostream outputs the Youth books

ostream &operator<<(ostream &os, Youth *p)
{
    if (p != nullptr)
    {
        if (p->valid() == true) 
        {
            return os << left << setw(PRINT_WIDTH_YEAR) << p->year
                << left << setw(PRINT_WIDTH_AUTHOR)
                << p->author.substr(0, PRINT_WIDTH_AUTHOR - 1)
                << left << setw(PRINT_WIDTH_TITLE)
                << p->title.substr(0, PRINT_WIDTH_TITLE - 1) << endl;

        }
        else 
        {
            cout << "ERROR: " << "Trying to print invalid youth!" 
                << endl;
            return os;
        }
    }
    else
        return os;
}


