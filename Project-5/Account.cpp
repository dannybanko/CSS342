#include "Account.hpp"

//----------------------------------------------------------------------------
// constructor
Account::Account() {
    accountName = " ";
    accountID = 0;
    startingBalance = 0;
    endingBalance = 0;; // starts endingBalance to be
                        // the same as startingBalance
}

//----------------------------------------------------------------------------
// destructor
Account::~Account() {
}

//----------------------------------------------------------------------------
// getAccount
Account* Account::getAccount() {
    return this;
}

//----------------------------------------------------------------------------
// setStartingBalance
void Account::setStartingBalance(int balance) {
    startingBalance = balance;
}

//----------------------------------------------------------------------------
// setEndingBalance
void Account::setEndingBalance(int balance) {
    endingBalance = balance;
}

//----------------------------------------------------------------------------
// getStartBalance
int Account::getStartBalance() {
    return startingBalance;
}

//----------------------------------------------------------------------------
// getEndBalance
int Account::getEndBalance() {
    return endingBalance;
}

//----------------------------------------------------------------------------
// setAccountName
void Account::setAccountName(string name) {
    accountName = name;
}

//----------------------------------------------------------------------------
// setAccountID
void Account::setAccountID(int accountNumber) {
    accountID = accountNumber;
}

//----------------------------------------------------------------------------
// deposit
void Account::deposit(int depositFunds) {
    endingBalance += depositFunds;
}

//----------------------------------------------------------------------------
// withdraw
void Account::withdraw(int withdrawFunds) {
    endingBalance -= withdrawFunds;
}

//----------------------------------------------------------------------------
// operator<<
ostream& operator<<(ostream& output, const Account& toPrint) {
    output << toPrint.startingBalance;
    
    return output;
}
