#include <iostream>
#include <fstream>
#include <vector>

#include "library.h"
#include "periodical.h"
#include "fiction.h"
#include "youth.h"
#include "binTree.h"
#include "transaction.h"
#include "factory.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    Library lib;

    ifstream inFile;
    inFile.open("Smalldata4patrons.txt", ios::binary | ios::in);

    if (inFile.is_open()) 
    {
        lib.readPatrons(inFile);
        inFile.close();
    }
    else
        cout << "ERROR: Cannot open patrons file!" << endl;

    inFile.open("Smalldata4books.txt", ios::binary | ios::in);

    if (inFile.is_open()) 
    {
        lib.readLibrary(inFile);
        inFile.close();
    }
    else 
        cout << "ERROR: Cannot open books file!" << endl;

    inFile.open("Smalldata4commands.txt", ios::binary | ios::in);

    if (inFile.is_open()) 
    {
        lib.processCommands(inFile);
        inFile.close();
    }
    else 
        cout << "ERROR: Cannot open commands file!" << endl;

	system("pause");
}

