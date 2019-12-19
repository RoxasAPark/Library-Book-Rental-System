#include "factory.h"

//----------------------------------------------------------------------------
// Default constructor

Factory::Factory() 
{
    // Initializing inventory types, so they
    // can be created using the Factory
    inventoryTable['F' - 'A'] = new Fiction();
    inventoryTable['P' - 'A'] = new Periodical();
    inventoryTable['Y' - 'A'] = new Youth();

    // Initialize transaction types
    transactionTable['C' - 'A'] = new Checkout();
    transactionTable['H' - 'A'] = new History();
    transactionTable['R' - 'A'] = new Return();
}

//----------------------------------------------------------------------------
// Copy constructor

Factory::Factory(const Factory& other) 
{

}

//----------------------------------------------------------------------------
// Destructor clears all hash tables to clean up memory

Factory::~Factory() 
{
    // clear inventory table
    for (auto i : inventoryTable) 
    {
        if (i != nullptr)
            delete i;
    }

    // clear transaction table
    for (auto t : transactionTable) 
    {
        if (t != nullptr)
            delete t;
    }
}

//----------------------------------------------------------------------------
// createBook() creates LibraryItem objects accordingly based on additional
// info about the book (genre, etc.)

LibraryItem *Factory::createBook(istream &is, bool parseType) 
{
    LibraryItem *item = nullptr;
    char genre;
    char type;

    if (is.eof() == false) 
    {
        // filter out end of line, end of file etc.
        // in case of end of line/file, jump to else branch
        // otherwise, read the rest of the line
        if (is >> genre) 
        {
            if ((genre >= 'A') && (genre <= 'Z')) 
            {
                if (inventoryTable[genre - 'A'] != nullptr) 
                {
                    item = inventoryTable[genre - 'A']->create();

                    // reuse that snippet of code to read
                    // books from the command file, where they
                    // contain the extra 'H' for hard-copy.
                    if ((parseType == true) && (is.eof() == false))
                    {
                        // the 'H' is saved into type, but not
                        // further used at the moment
                        is >> type;
                        is.get();

                        // if processing a command 'C' or 'R'
                        // put together query info (does not contain
                        // year)
                        if (item != nullptr)
                            item->setQueryInfo(is);
                    }
                    else 
                    {
                        // if processing an inventory item that is
                        // added to the library, add 
                        // all basic info (including the year)
                        if (item != nullptr)
                            item->setBasicInfo(is);
                    }
                }
                else 
                {
                    // print this error only if there are further
                    // data given.
                    // if it is just an end of line, ignore it
                    // (otherwise, the end of file shows up as
                    // unknown entry)
                    if (is.eof() == false)
                    {
                        string tmp;
                        getline(is, tmp);
                        cout << "ERROR: " << "Ignoring unknown entry: "
                            << genre << " " << tmp << endl;
                    }
                }
            }
        }
    }

    return item;
}

//----------------------------------------------------------------------------
// createTransaction() creates transaction objects
// to add to a hash table of transactions that exist in the library system

Transaction *Factory::createTransaction(istream &is) 
{
    Transaction *t = nullptr;
    char type;
    string line;

    if (is.eof() == false) 
    {
        if (is >> type) 
        {
            if ((type >= 'A') && (type <= 'Z')) 
            {
                if (transactionTable[type - 'A'] != nullptr) 
                {
                    // create a transaction item according to
                    // the given type ('C', 'R' or 'H')
                    t = transactionTable[type - 'A']->create();
                }
                else 
                {
                    // print this error only if the function
                    // encounters irrelevant data of any type
                    // if it is just an end of line, ignore it
                    // (otherwise, the end of file shows up as
                    // unknown entry)
                    if (is.eof() == false) 
                    {
                        string tmp;
                        getline(is, tmp);
                        cout << "ERROR: " << "Ignoring unknown entry: "
                            << type << " " << tmp << endl;
                    }
                }
            }
        }
        else 
        {
            // a single char is an invalid command in any case
            if (is.eof() == false)
                cout << "ERROR: " << "Read invalid command " << endl;
        }
    }

    return t;
}



