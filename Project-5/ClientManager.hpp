#ifndef ClientManager_hpp
#define ClientManager_hpp

#include <queue>
#include "BSTree.hpp"
#include "Transaction.hpp"

//--------------------------  class ClientManager ----------------------------
// ClientManager: Holds the BSTree of Client objects, and STL queue of
//      transactions. Is responsible for opening and passing .txt files
//      to Client and Transaction constructors. Is repsonsible for building
//      and running the business.
// Assumptions:
//   -- There are two .txt files, one for Client objects and their account
//      information. The other for transaction information
//   -- performs the transactions, reliant on client and account transaction
//      functions
//
//----------------------------------------------------------------------------

class ClientManager {
public:
    ClientManager();    // constructor
    ~ClientManager();   // desctructor
    
    void buildTree();                // builds BSTree of Clients
        
    void buildQueueTransactions();   // builds ququq of Transactions
    void displayQueueTransactions(); // just used for displaying queue
        
    // prints LOSE report Client and Account information
    void displayReport() const;
        
    void deposit(Transaction*);  // deposit code
    void withdraw(Transaction*); // withdraw code
    void move(Transaction*);     // move code
    void history(Transaction*);  // history code, uses vector for container
    
    void runBuisiness();         // runs the transactions

private:  // private data
    BSTree clientTree; // container for Client objects
    
    // containter for Transaction objects
    queue<Transaction*> clientTransactions;
    
};
#endif /* ClientManager_hpp */
