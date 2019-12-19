#ifndef BINTREE_H_
#define BINTREE_H_

#include "book.h"
#include <iostream>
#include <string>

using namespace std;

// Node is a struct that represents a node object in a 
// binary search tree
// ***********************************************************
struct Node
{
	// right child
    Node *right; 

	// left child
    Node *left; 

	// Data inside the node
	// In this case, it's a LibraryItem object that represents
	// a library book
    LibraryItem *book; 
};

// binTree is a class that represents a binary search tree
// for holding library books (LibraryItem objects)
// ***********************************************************
class binTree
{
    // outputs the tree via an inorder traversal
    friend ostream &operator<<)ostream &os, const binTree &bt);

private:
	// first node in the binary search tree
	Node *root; 
   
	// genre of a library book
    string genreName; 

    // helper function to empty the binary search tree of all
	// library books
    void emptyHelper(Node *& current); 

    // helper function to find a specific book from the 
	// binary search tree
    Node *retrieveHelper(Node *root, const LibraryItem *inv);

    // helper function for the << operator
	// to output all books in the binary search tree
	// via an inorder traversal
    ostream &printHelper(ostream &os, Node *) const;
public:
	// default constructor
    binTree(); 

	// copy constructor to make a copy of an existing
	// binary search tree
    binTree(const binTree&); 

	// destructor that clears the binary search tree
	// of all library books to clear up space in memory
    ~binTree(); 

	// assign a library book object a genre
    void setGenreName(string name) { genreName = name; };

	// get the name of the genre of a book
    string getGenreName() { return genreName; };

	// function to check if the binary search tree is
	// empty. Return true if empty, otherwise return false
    bool isEmpty() const; 

	// Insert a library book into the binary search tree.
	// If the insert fails for some reason, return false,
	// otherwise return true to indicate a successful
	// insert
    bool insert(LibraryItem *inv);

	// function to retrieve a book from the
	// binary search tree
    LibraryItem *retrieve(const LibraryItem *inv);

	// Delete all books in the binary search tree
    void deleteTree(); 

};

#endif
