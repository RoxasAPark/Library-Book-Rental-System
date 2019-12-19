#ifndef PATRON_H_
#define PATRON_H_

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

#include "transaction.h"

using namespace std;

#define MAX_ID  9999
#define PRINT_WIDTH_ID  5
#define PRINT_WIDTH_NAME    10

class Patron
{
private:
    int identification;
    string firstName = "";
    string lastName = "";
    vector<Transaction*> transactionHistory{};

public:
    Patron();
    Patron(istream&);
    Patron(const Patron&);

    virtual ~Patron();

    void displayHistory(ostream &os);
    void addTransaction(Transaction *t);

    bool valid();

    int getID() const { return identification; };
    string getfirstName() const { return firstName; };
    string getlastName() const { return lastName; };

    virtual bool operator<(const Patron &pat);
    virtual bool operator==(const Patron &pat);

    friend ostream & operator<<(ostream &os, const Patron *p);
};

#endif
