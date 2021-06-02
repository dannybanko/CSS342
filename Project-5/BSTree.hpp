#ifndef BSTree_hpp
#define BSTree_hpp

#include "Client.hpp"

//--------------------------  class BSTree -----------------------------------
// BSTree: This class is the container for all the Client objects. Just like
//      any other BST, the left hand subtree is smaller than the root node,
//      and the right hand is greater than the rootNode.
// Assumptions:
//   -- display will call the other classes operator<< to print information
//   -- Doesnt care about the individual information of the Client objects,
//      just holds Client object in the node->data
//   -- display() will print the BSTree in an in-order traversal fashion
//----------------------------------------------------------------------------

class BSTree {
public:
    BSTree();   // constructor
    ~BSTree();  // calls makeEmpty which deallocates all memory
    void makeEmpty(); //empties the current tree, deallocates all memory
    
    // insert object into the tree, parameter holds pointer to object
    // to insert
    bool insert(Client*);
    // retrieve object, first parameter is object to retrieve
    // second parameter holds pointer to found object, nullptr if not found
    bool retrieve(const Client&, Client*&) const;
    void display() const; // displays the contents of a tree to cout
    bool isEmpty() const; // returns true if tree is empty
    
private:
    struct Node { // glue that holds data properly
        Client* data;
        Node* right;
        Node* left;
    };
    Node* root;
    
    void makeEmptyHelper(Node*&);        // recursive helper for make empty
    bool insertHelper(Node* &, Client*); // recursive helper for insert
    // recursice helper for retrieve
    bool retrieveHelper(const Client&, Client*&, Node*) const;
    void displayHelper(Node*) const;     // recursive helper for display
    
    
};

#endif /* BSTree_hpp */
