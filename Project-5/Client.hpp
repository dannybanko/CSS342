#ifndef Client_hpp
#define Client_hpp

#include "Account.hpp"
#include <iostream>
#include <vector>
using namespace std;

//--------------------------  class Client  ----------------------------------
// Client: Stores information about a client and the related 10 bank accounts
//
// Assumptions:
//   -- Each client has 10 accounts (may or may not be empty)
//   -- Clients are sorted by their integer id
//
//----------------------------------------------------------------------------

// used for the 10 account names
const string ACCTNAME[] = {"Money Market", "Prime Money Market",
"Long-Term Bond", "Short-Term Bond", "500 Index Fund",
"Capital Value Fund", "Growth Equity Fund", "Growth Equity Fund",
"Value Fund", "Value Stock Index"};

class Transaction;

class Client {
    friend ostream& operator<<(ostream&, const Client&);
public:
    Client();         // constructor
    Client(int);      // constructor, take in int
    Client(istream&); // constructor, take in file
    ~Client();        // destructor
    
    // comparison operators for sorting and other operations
    bool operator<(const Client&) const;   // less than operator
    bool operator>(const Client&) const;   // greater than operator
    bool operator==(const Client&) const;  // equality operator
    bool operator!=(const Client&) const;  // non-equality operator
    
    Account getAccount(int); // getAccount
    string getFirstName();   // getFirstName
    string getLastName();    // getLastName
    int getAccountNumber();  // getAccountNumber
    vector<Transaction*> getHistory(); // getHistory
    
    void deposit(int, int);  // deposit
    void withdraw(int, int); // withdraw
    
    vector<Transaction*> history;  // holds history of transactions
private:
    string lastName;     // Client last name
    string firstName;    // Client first name
    int accountNumber;   // Client account number
    Account* accounts;   // array of pointers to 10 accounts
};

#endif /* Client_hpp */
