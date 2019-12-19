#ifndef FACTORY_H_
#define FACTORY_H_

#include "book.h"
#include "fiction.h"
#include "periodical.h"
#include "transaction.h"
#include "youth.h"
#include "checkout.h"
#include "return.h"
#include "history.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book;
class Transaction;

// Factory class is a factory that generates Transaction
// and LibraryItem objects without having to use 'new'
// redundantly every time we want more objects to work with.
// The class also uses hash tables: One for LibraryItem objects
// and one for Transaction objects so the Factory itself can
// keep track of which objects they've created before. 

class Factory
{
private:
    LibraryItem *inventoryTable[26]{ nullptr }; 
    Transaction *transactionTable[26]{ nullptr };
public:
    Factory();
    Factory(const Factory&);
    ~Factory();

    // create a LibraryItem object based on the type
    LibraryItem *createBook(istream &is, bool parseType = false);

    // create a Transaction object based on type
    Transaction *createTransaction(istream &is);
};

#endif

