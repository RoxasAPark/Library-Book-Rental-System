#include "periodical.h"

//----------------------------------------------------------------------------
// Default Constructor
// Not implemented because this is a child class

Periodical::Periodical() : Book() 
{

}

//----------------------------------------------------------------------------
//Copy Constructor

Periodical::Periodical(const Periodical &periodical) : Book(periodical) 
{

}

//----------------------------------------------------------------------------
// Destructor
// Not implemented because Periodical is a child class

Periodical::~Periodical() 
{

}

//----------------------------------------------------------------------------
// display() outputs a list of periodical books

ostream &Periodical::display(ostream &os, bool availability) const 
{
    if (valid() == true) 
    {
        string avail = "";

        if (getCopiesLeft() > 0) 
            avail = "available";

        os << left << setw(PRINT_WIDTH_YEAR) << year
            << left << setw(PRINT_WIDTH_MONTH) << month
            << left << setw(PRINT_WIDTH_TITLE)
            << title.substr(0, PRINT_WIDTH_TITLE - 1);

        if (availability == true)
            os << avail << endl;
        else
            os << endl;

        return os;

    }
    else 
    {
        cout << "ERROR: "
            << "Trying to print invalid periodical!" << endl;
        return os;
    }
}

//----------------------------------------------------------------------------
// setBasicInfo reads in the txt file of books

void Periodical::setBasicInfo(istream &is) 
{
    if (is.eof() == false) 
    {
        is.get(); // reads space before title
        getline(is, title, ',');
        is >> month >> year;
        //is.get(); // reads endline after year
        setNumberOfCopies(1);
        setType('P');
    }
}

//----------------------------------------------------------------------------
// setBasicInfo() sets the data of a Periodical book

void Periodical::setBasicInfo(int y, int m, string t) 
{
    title = t;
    month = m;
    year = y;
    setNumberOfCopies(1);
    setType('P');
}

//----------------------------------------------------------------------------
// setQueryInfo() reads in the txt file of books

void Periodical::setQueryInfo(istream &is) 
{
    if (is.eof() == false) 
    {
        //is.get(); // reads space before year
        is >> year >> month;
        is.get();
        getline(is, title, ',');

        if (is.eof() == false)
            is.get(); // reads endline after month
        setNumberOfCopies(1);
        setType('P');
    }
}

//----------------------------------------------------------------------------
// setAdditionalInfo()

void Periodical::setAdditionalInfo(istream &is) 
{

}

//----------------------------------------------------------------------------
// valid() checks to make sure the data for the Periodical books are valid

bool Periodical::valid() const 
{
    if ((year > 0) && (month > 0) && (month <= 12) &&
        (title != ""))
        return true;
    else 
        return false;
}

//----------------------------------------------------------------------------
// create() uses factory logic to create a new Periodical object

LibraryItem *Periodical::create() 
{
    LibraryItem *p = new Periodical();
    return p;
}

//----------------------------------------------------------------------------
// operator==() checks for duplicates

bool Periodical::operator==(const LibraryItem &inv) const 
{
    // two periodicals are identical, if the have the same title,
    // year and month
    if ((title == static_cast<const Periodical &>(inv).title) &&
        (year == static_cast<const Periodical &>(inv).year) &&
        (month == static_cast<const Periodical &>(inv).month))
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------
// oeprator<() is for sorting purposes

bool Periodical::operator<(const LibraryItem &inv) const 
{
    // first sorted by year
    if (year < static_cast<const Periodical &>(inv).year)
        return true;
        // if still equal, sorted by month
    else if ((year == static_cast<const Periodical &>(inv).year) &&
        (month < static_cast<const Periodical &>(inv).month)) 
        return true;
        // if still equal, sorted by title
    else if ((year == static_cast<const Periodical &>(inv).year) &&
        (month == static_cast<const Periodical &>(inv).month) &&
        (title < static_cast<const Periodical &>(inv).title)) 
        return true;
    else 
        return false;
}

//----------------------------------------------------------------------------
// operator<< outputs all of the periodicals

ostream &operator<<(ostream &os, Periodical *p) 
{
    if (p != nullptr)
    {
        if (p->valid() == true) //if the item is valid
        {
            string avail = "";

            if (p->getCopiesLeft() > 0)
                avail = "available";

            return os << left << setw(PRINT_WIDTH_YEAR) << p->year
                << left << setw(PRINT_WIDTH_MONTH) << p->month
                << left << setw(PRINT_WIDTH_TITLE)
                << p->title.substr(0, PRINT_WIDTH_TITLE - 1) << " "
                << avail << endl;

        }
        else
        {
            cout << "ERROR: " << "Trying to print invalid periodical!"
                << endl;
            return os;
        }
    }
    else
        return os;
}


