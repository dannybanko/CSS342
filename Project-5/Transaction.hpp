#ifndef Transaction_hpp
#define Transaction_hpp

#include <iostream>
#include "Client.hpp"
using namespace std;

class Transaction {
    friend ostream& operator<<(ostream&, const Transaction&);
public:
    Transaction();              // constructor
    Transaction(istream&);      // constructor, reads from file
    ~Transaction();             // destructor
    
    bool checkValidTransactionType();  // check if valid transaction type
    bool checkValidTransaction();      // check if valid transaction
    char getTransactionType();         // get transaction type
    
    int getFromClient();   // get from client
    int gerToClient();     // get to client
    int getFromAccount();  // get from account
    int getToAccount();    // get to account
    int getFunds();        // get funds
    
private:
    char transactionType;              // 'D', 'M', 'W', or 'H'
    int funds;    
    int fromClient;
    int toClient;
    int fromAcc;
    int toAcc;
};
#endif /* Transaction_hpp */
