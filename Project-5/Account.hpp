//
//  Account.hpp
//  Assignment 5
//
//  Created by Danny Banko on 6/4/20.
//  Copyright © 2020 Danny Banko. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

//--------------------------  class Account  ---------------------------------
// Account: Contains information on the bank balance of an account, account
//      name, and account ID
// Assumptions:
//   -- accID is Client acctNum with integer from 0 to 9 added to the end
//   -- name is the name of the account (e.g. Prime Money Market)
//   -- balances are whole number integers
//
//----------------------------------------------------------------------------
#include <iostream>
using namespace std;

class Account {

    friend ostream& operator<<(ostream&, const Account&);
        
public:
    Account();
    ~Account();
        
    void setStartingBalance(int); // allows for account balance to be set
    void setEndingBalance(int);
    void setAccountName(string);  // allows for account name to be set
    void setAccountID(int);       // allows for accountID to be set
    int getStartBalance();
    int getEndBalance();
    Account* getAccount();        // returns pointer to account
        
    void deposit(int);            // allows for funds to be deposited
    void withdraw(int);           // allows for funds to be withdrawn
    
private:
    string accountName;
    int accountID;               // Client's acctNum * 10 + (0-9)
    int startingBalance;
    int endingBalance;
};
#endif /* Account_hpp */
