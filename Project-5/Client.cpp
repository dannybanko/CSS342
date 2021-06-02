#include "Client.hpp"
#include "Transaction.hpp"
#include <iomanip>

//----------------------------------------------------------------------------
// constructor
Client::Client() {
    firstName = " ";
    lastName = " ";
    accountNumber = 0;
    accounts = new Account[10];
}

//----------------------------------------------------------------------------
// constructor to create partial client
Client::Client(int id) {
    firstName = " ";
    lastName = " ";
    accountNumber = id;
    accounts = new Account[10];
}

//----------------------------------------------------------------------------
// constructor, reads in data
Client::Client(istream& input) {
    input >> lastName >> firstName >> accountNumber; // read in Client data
    accounts = new Account[10]; // new array of pointers
    // check for eof
    if (input.eof()) {
        return; // break out of function
    }
    int balance;
    for (int i = 0; i < 10; i++) {
        input >> balance;
        accounts[i].setAccountName(ACCTNAME[i]);          // accountName
        accounts[i].setAccountID(accountNumber * 10 + i); // accountId
        accounts[i].setStartingBalance(balance);          // startingBalance
        accounts[i].setEndingBalance(balance);            // endingBalance
    }
}

//----------------------------------------------------------------------------
// destructor
Client::~Client() {
    delete [] accounts;
}

//----------------------------------------------------------------------------
// operator<
bool Client::operator<(const Client& other) const {
    return (accountNumber < other.accountNumber);
}

//----------------------------------------------------------------------------
// operator>
bool Client::operator>(const Client& other) const {
    return (accountNumber > other.accountNumber);
}

//----------------------------------------------------------------------------
// operator==
bool Client::operator==(const Client& other) const {
    return (accountNumber == other.accountNumber);
}

//----------------------------------------------------------------------------
// operator!=
bool Client::operator!=(const Client& other) const {
    return (accountNumber != other.accountNumber);
}

//----------------------------------------------------------------------------
// getAccount
Account Client::getAccount(int accountNum) {
    return accounts[accountNum];
}

//----------------------------------------------------------------------------
// getFirstName
string Client::getFirstName() {
    return firstName;
}

//----------------------------------------------------------------------------
// getLastName
string Client::getLastName() {
    return lastName;
}

//----------------------------------------------------------------------------
// getAccountNumber
int Client::getAccountNumber() {
    return accountNumber;
}

//----------------------------------------------------------------------------
// getHistory
vector<Transaction*> Client::getHistory() {
    return history;
}


//----------------------------------------------------------------------------
// deposit
void Client::deposit(int accountNum, int ammount) {
    accounts[accountNum].deposit(ammount);
}

//----------------------------------------------------------------------------
// withdraw
void Client::withdraw(int accountNum, int ammount) {
    accounts[accountNum].withdraw(ammount);
}

//----------------------------------------------------------------------------
// opperator<<
ostream& operator<<(ostream& output, const Client& toPrint) {
    output << toPrint.accountNumber << "  " << toPrint.firstName << " "
    << toPrint.lastName << endl << "Initial Balances:";
    
    for (int i = 0; i < 10; i++) {
        output << setw(6) << toPrint.accounts[i];
    }
    output << endl <<  "Final Balances:  ";
    for (int i = 0; i < 10; i++) {
        output << setw(6) << toPrint.accounts[i].getEndBalance();
    }
    
    output << endl << endl;
    return output;
}

