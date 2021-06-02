#include "BSTree.hpp"

//----------------------------------------------------------------------------
// constructor
BSTree::BSTree() {
    root = nullptr;
    // may need to set left/right to nullptr
}

//----------------------------------------------------------------------------
// destructor, calls makeEmpty()
BSTree::~BSTree() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// makeEmpty
void BSTree::makeEmpty() {
    // base case, tree is empty
    if (root == nullptr) {
        return;
    }
    // call to recursive helper
    makeEmptyHelper(root);
}

//----------------------------------------------------------------------------
// makeEmptyHelper
void BSTree::makeEmptyHelper(Node* &current) {
    // base case, if node is nullptr break out of function
    if (current == nullptr) {
        return;
    }
    
    // recursive calls
    makeEmptyHelper(current->left);  // traverse left subtree
    makeEmptyHelper(current->right); // traverse right subtree
    
    delete current->data;       // deletes the Client
    current->data = nullptr;
    delete current;             // deletes the tree Node
    current = nullptr;
    // may need to set left/right to null ptr
}

//----------------------------------------------------------------------------
// insert
bool BSTree::insert(Client* toInsert) {
    // call to recursive helper
    return insertHelper(root, toInsert);
}

//----------------------------------------------------------------------------
// insertHelper
bool BSTree::insertHelper(Node* &current, Client* toPtr) {
    if (current == nullptr) {
        current = new Node;     // creates new node
        current->data = toPtr;  // sets client to node
        current->left = current->right = nullptr;
        return true;
    }
    
    // conditions to check which subtree to traverse
    if (*toPtr < *current->data) {                   // left subtree
        return insertHelper(current->left, toPtr);   // walk left
    } else if (*toPtr > *current->data) {            // right subtree
        return insertHelper(current->right, toPtr);  // walk right
    }
    return false;
}

//----------------------------------------------------------------------------
// retrieve
bool BSTree::retrieve(const Client& toRetrieve, Client* &ptrClient) const {
    // base case, tree is empty
    if (root == nullptr) {
        return false;
    }
    
    // root is the target to retrieve
    if (*root->data == toRetrieve) {
        ptrClient = root->data;
        return true;
    }
    
    // call to recursive helper
    return retrieveHelper(toRetrieve, ptrClient, root);
}

//----------------------------------------------------------------------------
// retrieveHelper
bool BSTree::retrieveHelper(const Client& toRetrieve, Client* &ptrClient,
                            Node* current) const {
    // base case client is not in BST
    if (current == nullptr) {
        return false;
    }
    
    // base case, if the node = object set ptrClient to node address,
    // and return true
    if (toRetrieve == *current->data) {
        ptrClient = current->data;
        return true;
    }
    
    if (toRetrieve < *current->data) {        // traverse left subtree
        if (current->left != nullptr) {
            return retrieveHelper(toRetrieve, ptrClient, current->left);
        }
    } else if (toRetrieve > *current->data) { // traverse right sub tree
        if (current->right != nullptr) {
            return retrieveHelper(toRetrieve, ptrClient, current->right);
        }
    }
    return false;
}

//----------------------------------------------------------------------------
// display

void BSTree::display() const {
    // base case, empty tree
    if (root == nullptr) {
        return;
    }
    
    // call to recursive helper
    return displayHelper(root);
}

//----------------------------------------------------------------------------
// displayHelper

void BSTree::displayHelper(Node* current) const {
    if (current == nullptr) {
        return;
    }
    // prints left subrtree first, then root, then right subtree (in-order
    // traversal)
    displayHelper(current->left);
    cout << *current->data << " ";
    displayHelper(current->right);
}

//----------------------------------------------------------------------------
// isEmpty()
bool BSTree::isEmpty() const {
    // tree is empty if root is == nullptr
    if (root == nullptr) {
        return true;
    } else {
        return false;
    }
}
