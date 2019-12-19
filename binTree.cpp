#include "binTree.h"

//----------------------------------------------------------------------------
// Default Constructor

binTree::binTree() 
{
    root = NULL;
}

//----------------------------------------------------------------------------
// Copy Constructor

binTree::binTree(const binTree& other) 
{

}

//----------------------------------------------------------------------------
// Destructor to clean up memory

binTree::~binTree() 
{
    if (isEmpty() == false)
        deleteTree(); // delete the tree of all the nodes it possesses
}

//----------------------------------------------------------------------------
// isEmpty() checks if the tree is empty or not

bool binTree::isEmpty() const 
{
    return root == NULL;
}

//----------------------------------------------------------------------------
// insert() BST inserts a LibraryItem object into the tree
// same implementation as in lab 2
// logic borrowed from Dr.Carol Zander with permission
// No cheating intended

bool binTree::insert(LibraryItem *itemPtr) 
{
    if (itemPtr != nullptr) 
    {
        Node* ptr = new Node; 
        ptr->book = itemPtr;
        itemPtr = NULL;
        ptr->left = ptr->right = NULL;

        if (isEmpty() ) 
        {
            root = ptr;
        }
        else 
        {
            Node* current = root;
            bool inserted = false; 

            while (!inserted) 
            {
                if (*(ptr->book) == *(current->book)) // duplicate detected
                {
                    delete ptr;
                    ptr = NULL;
                    return false;
                }
                else if (*(ptr->book) < *(current->book)) // book is smaller
                {
                    if (current->left == NULL) 
                    {
                        current->left = ptr;
                        inserted = true;
                    }
                    else
                        current = current->left; // one step left
                }
                else // book is larger than current
                {
                    if (current->right == NULL) 
                    { 
                        current->right = ptr;
                        inserted = true;
                    }
                    else
                        current = current->right; // one step right
                }
            }
        }

        return true;
    }
    else 
        return false;
}

//----------------------------------------------------------------------------
// retrieve() returns a specific LibraryItem object passed in as a parameter
// with help from the helper function retrieveHelper()

LibraryItem *binTree::retrieve(const LibraryItem *target) 
{
    Node *tmp = nullptr;

    // recursive call to perform the search and retrieval
    tmp = retrieveHelper(root, target);

    if (tmp != nullptr) 
        return tmp->book; // target LibraryItem object found
    else
        return nullptr; // target LibraryItem object never existed
}

Node *binTree::retrieveHelper(Node *root, const LibraryItem *target) 
{
    if (root != nullptr) 
    {
        // comparing target LibraryItem object with the others
        if (*target == *(root->book)) 
        {
            return root; // target found
        }
        else if (*target < *(root->book)) // use recursion accordingly
        {
            return retrieveHelper(root->left, target);
        }
        else
            return retrieveHelper(root->right, target);
    }
    else
        return nullptr; // target LibraryItem object never existed
}

//----------------------------------------------------------------------------
// deleteTree() deletes the tree with the use of the helper function
// emptyHelper()

void binTree::deleteTree() 
{
    emptyHelper(root);
}

void binTree::emptyHelper(Node *& current) 
{
    if (current == NULL) 
    {
        return;
    }

    emptyHelper(current->left); // empty left side
    emptyHelper(current->right); // empty right side

    if (current->book != NULL)
        delete current->book; // delete the data 

    if (current != NULL) // delete the node itself
    {
        delete current;
        current = NULL;
    }
}

//----------------------------------------------------------------------------
// operator<< uses inorder traversal to walk through the tree
// and output every node visited through the traversal
// via the helper function printHelper()

ostream &operator<<(ostream &os, const binTree &bt) 
{
    if (bt.isEmpty() == false) // if the tree contains LibraryItem objects
        bt.printHelper(os, bt.root); // traverse and output the data

    return os;
}

ostream &binTree::printHelper(ostream &os, Node *current) const 
{
    if (current == nullptr) // if there's nothing to visit
        return os;
    else // inorder traversal
    {
        printHelper(os, current->left);
        current->book->display(os);
        printHelper(os, current->right);
        return os;
    }
}


