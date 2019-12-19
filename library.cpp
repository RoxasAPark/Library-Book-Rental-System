#include "library.h"


//----------------------------------------------------------------------------
// Default Constructor

Library::Library() 
{
    // initialize inventory trees with proper names
    // to allow legibly formatted output
    invTree['F' - 'A'].setGenreName("Fiction");
    invTree['P' - 'A'].setGenreName("Periodicals");
    invTree['Y' - 'A'].setGenreName("Youth");
}

//---------------------------------------------------------------------------
//Copy Constructor

Library::Library(const Library&other) 
{

}

//----------------------------------------------------------------------------
// Destructor to clean up memory

Library::~Library() 
{
    // clear patron table
    for (auto p : patronTable) 
    {
        if (p != nullptr) 
            delete p;
    }

    // clear inventory
    for (int i = 0; i < 26; i++) {
        if (invTree[i].isEmpty() == false)
            invTree[i].deleteTree();
    }
}

//----------------------------------------------------------------------------
// displayInventory() displays all types of books in a sorted order
// The sorted order depends on the genre

void Library::displayInventory() 
{
    cout << "Periodicals tree:" << endl;
    cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
        << left << setw(PRINT_WIDTH_MONTH)
        << "MONTH"
        << left << setw(PRINT_WIDTH_TITLE)
        << "TITLE"
        << "AVAIL" << endl;
    cout << invTree['P' - 'A'];
    cout << "Youth tree:" << endl;
    cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
        << left << setw(PRINT_WIDTH_TITLE)
        << "TITLE"
        << left << setw(PRINT_WIDTH_AUTHOR)
        << "AUTHOR"
        << "AVAIL" << endl;
    cout << invTree['Y' - 'A'];
    cout << "Ficton tree:" << endl;
    cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
        << left << setw(PRINT_WIDTH_AUTHOR)
        << "AUTHOR"
        << left << setw(PRINT_WIDTH_TITLE)
        << "TITLE"
        << "AVAIL" << endl;
    cout << invTree['F' - 'A'];
}

//----------------------------------------------------------------------------
// displayPatron() outputs a list of patrons via an iterator

void Library::displayPatrons() 
{
    cout << "Patrons:" << endl;

    for (auto p : patronTable) 
    {
        if (p != nullptr) 
            cout << p << endl;
    }
}

//----------------------------------------------------------------------------
// readPatrons() reads in a list of patrons from a txt file

bool Library::readPatrons(istream &is) 
{
    bool result = true;

    while (is.eof() == false) 
    {
        // print out input lines in bold (used for debugging)
        //cout << "\e[1mread line: " << line << "\e[0m" << endl;

        //istringstream procLine{line};
        // create a patron object using the
        // given input stream
        Patron *pat = new Patron(is);
        if (pat->valid() == false)
        {
            if (is.eof() == false) 
            {
                cout << "ERROR: " << "Read invalid data for patron: "
                    << pat << endl;
                result = false;
            }

            // the object is destroyed here, in case it is invalid
            delete pat;
            break;
        }
        else 
            patronTable[pat->getID()] = pat;
    }

    return result;
}

//----------------------------------------------------------------------------
// readLibrary() reads in a library system from a given txt file
// that shows a list of items to insert

bool Library::readLibrary(istream &is) 
{
    bool result = true;

    while (is.eof() == false) 
    {
        // create a library item (Fiction, Periodical or Youth)
        // from the given input stream
        LibraryItem *item = itemCreator.createBook(is);

        if (item != nullptr) 
        {
            int type = item->getType() - 'A';

            // if the item is not valid, it's destroyed in
            // the else branch
            if (item->valid() == true) 
                invTree[type].insert(item);
            else 
            {
                cout << "ERROR: " << "Read invalid data for book: ";
                item->display(cout);
                delete item;
                result = false;
            }
        }
    }

    return result;
}

//----------------------------------------------------------------------------
// processCommands() can perform transactions, manage inventory of items,
// and display the inventory of items
// returns true if all actions are successful

bool Library::processCommands(istream &is) 
{
    bool result = true;

    while (is.eof() == false) 
    {
        char cmd = 0x00;
        int patronID = 0;
        string line{};

        // first read line to string and then into
        // input string stream.
        // this allows further processing without bothering
        // about the cursor position in the file stream
        getline(is, line);
        istringstream procLine{ line };

        // print out input lines in bold (used for debugging)
        //cout << "\e[1mread line: " << line << "\e[0m" << endl;

        procLine >> cmd;

        // special case -> catch display command
        // because it's less effort to just directly print
        // the sorted trees than creating a transaction, which then
        // needs some pointer or reference back to the library
        // to display the trees.
        if (cmd == 'D') 
        {
            cout << "List of inventory:" << endl << endl;
            int i = 0;

            // this loop prints all genres (all binTrees that
            // are not empty)
            for (i = 0; i < 26; i++) 
            {
                if (invTree[i].isEmpty() == false) 
                {
                    cout << "Genre " << invTree[i].getGenreName() 
                        << ":" << endl;

                    // print header line for Fiction
                    if ((i + 'A') == 'F') 
                    {
                        cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
                            << left << setw(PRINT_WIDTH_AUTHOR)
                            << "AUTHOR"
                            << left << setw(PRINT_WIDTH_TITLE)
                            << "TITLE"
                            << "AVAIL" << endl;
                    }

                    // print header line for Youth
                    if ((i + 'A') == 'Y') 
                    {
                        cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
                            << left << setw(PRINT_WIDTH_TITLE)
                            << "TITLE"
                            << left << setw(PRINT_WIDTH_AUTHOR)
                            << "AUTHOR"
                            << "AVAIL" << endl;
                    }

                    // print header line for Periodical
                    if ((i + 'A') == 'P') {
                        cout << left << setw(PRINT_WIDTH_YEAR) << "YEAR"
                            << left << setw(PRINT_WIDTH_MONTH)
                            << "MONTH"
                            << left << setw(PRINT_WIDTH_TITLE)
                            << "TITLE"
                            << "AVAIL" << endl;
                    }

                    cout << invTree[i];
                    cout << endl;
                }
            }
        }
        else 
        {
            // reset stringstream (just assign command line again)
            istringstream procLine2{ line };
            //procLine.clear();

            // create Transaction object through Factory
            Transaction *t = itemCreator.createTransaction(procLine2);

            if (t != nullptr) 
            {
                // a valid Transaction must contain a valid Patron id
                if (procLine2 >> patronID) 
                {
                    if (patronTable[patronID] != nullptr) 
                    {
                        // if Patron is valid, assign it to the transaction
                        t->setPatron(patronTable[patronID]);

                        // create a temporary library item, which is only
                        // used to look for the actual item in the
                        // inventory trees
                        LibraryItem *tmp =
                            itemCreator.createBook(procLine2, true);

                        if (tmp != nullptr) 
                        {
                            LibraryItem *item =
                                invTree[tmp->getType() - 'A'].retrieve(tmp);

                            // no need to check for nullptr here, it will just
                            // be assigned by that function. all other members 
                            // of Transaction check for a valid pointer
                            t->setLibraryItem(item);
                            delete tmp;
                        }
                        else 
                        {
                            // display error only for checkouts and returns
                            // history does not have an item
                            if (t->getType() != 'H')
                                cout << "ERROR: " << "Could not find item "
                                << procLine2.str() << " in library" << endl;
                        }

                        t->setBasicInfo(is);

                        // only archive succesful transactions
                        // (invalid ones may not have a valid item)
                        if (t->execute() == true) 
                        {
                            if (t->getType() != 'H')
                                patronTable[patronID]->addTransaction(move(t));
                            else 
                            {
                                // temporary created transactions (like to 
                                // display a patron's history) are not needed
                                // any longer
                                delete t;
                            }
                        }
                        else 
                        {
                            // if transaction was not successful,
                            // make sure that both, the transaction and the item
                            // that was used to look up a book in the library
                            // are properly deleted
                            delete t;
                        }
                    }
                    else 
                    {
                        cout << "ERROR: " << "Invalid patron ID given: "
                            << patronID << endl;
                        delete t;
                    }
                }
                else 
                {
                    if (procLine2.str().length() > 0) 
                    {
                        cout << "ERROR: "
                            << "Invalid command (without patron ID): "
                            << procLine2.str() << endl;
                    }
                    delete t;
                }
            }
        }

    }

    return result;
}

//----------------------------------------------------------------------------
// operator[] makes the hash table lookup O(1)

Patron *Library::operator[] (uint32_t id) 
{
    // this overloaded operator acts as the self-coded hash table.
    // The id number of a patron is unique, so it's a perfect
    // fit for a hash key.
    // The patron can directly be accessed by its id.
    if (id < MAX_ID)
        return patronTable[id];
    else
        return nullptr;
}


