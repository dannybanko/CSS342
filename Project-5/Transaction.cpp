#include "Transaction.hpp"
#include <iomanip>

int const MAX = 51;    // used to read in the rest of data line for
                       // invalid transaction type

//----------------------------------------------------------------------------
// constructor
Transaction::Transaction() {
    transactionType = ' ';
    funds = 0;
    toClient = 0;
    fromClient = 0;
    toAcc = 0;
    fromAcc = 0;
}

//----------------------------------------------------------------------------
// contructor, reads in data from lab5command.txt
Transaction::Transaction(istream& input) {
    input >> transactionType;
    
    // check for eof
    if (input.eof()) {
        return; // break out of function
    }
    
    if (transactionType == 'D') {
        int temp;
        input >> temp;
        fromClient = toClient = temp / 10;
        fromAcc = toAcc = temp;
        input >> funds;
    } else if (transactionType == 'W') {
        int temp;
        input >> temp;
        fromClient = toClient = temp / 10;
        fromAcc = toAcc = temp;
        input >> funds;
    } else if (transactionType == 'M') {
        int temp1;
        input >> temp1;
        fromClient = temp1 / 10;
        fromAcc = temp1;
        input >> funds;
        int temp2;
        input >> temp2;
        toClient = temp2 / 10;
        toAcc = temp2;
    } else if (transactionType == 'H') {
        input >> fromClient;
        toAcc = 0;
        toClient = 0;
        fromAcc = 0;
        funds = 0;
    } else {
        char s[MAX];
        input.getline(s, MAX);
    }
}

//----------------------------------------------------------------------------
// destructor
Transaction::~Transaction() {
}

//----------------------------------------------------------------------------
// getTransactionType
char Transaction::getTransactionType() {
    return transactionType;
}

//----------------------------------------------------------------------------
// getFromClient
int Transaction::getFromClient() {
    return fromClient;
}

//----------------------------------------------------------------------------
// getToClient
int Transaction::gerToClient() {
    return toClient;
}

//----------------------------------------------------------------------------
// getFromAccount
int Transaction::getFromAccount() {
    return fromAcc;
}

//----------------------------------------------------------------------------
// getToAccount
int Transaction::getToAccount() {
    return toAcc;
}

//----------------------------------------------------------------------------
// getFunds
int Transaction::getFunds() {
    return funds;
}

//----------------------------------------------------------------------------
// checkValidTransactionType
// used in ClientManager to see if transaction will be added to queue
bool Transaction::checkValidTransactionType() {
    if (transactionType != 'D' && transactionType != 'W' &&
        transactionType != 'M' && transactionType != 'H') {
        cout << "invalid transaction type " << "'" <<
        transactionType << "'" << " requested" << endl;
        return false;
    } else {
        return true;
    }
}

//----------------------------------------------------------------------------
// operator<<, prints transaction based on transaction type
ostream& operator<<(ostream& output, const Transaction& toPrint) {
    if (toPrint.transactionType == 'D') {
        output << "deposit" << setw(4) << "$" << setw(7) <<
        toPrint.funds << " into " << ACCTNAME[toPrint.toAcc % 10] << endl;
        return output;
    } else if (toPrint.transactionType == 'W') {
        output << "withdraw" << setw(3) << "$" << setw(7) <<
        toPrint.funds << " from " << ACCTNAME[toPrint.toAcc % 10] << endl;
        return output;
    } else if (toPrint.transactionType == 'M') {
        output << "move" << setw(7) << "$" << setw(7) <<
        toPrint.funds << " from " << ACCTNAME[toPrint.fromAcc % 10] << endl
        << setw(22) << " to " << ACCTNAME[toPrint.toAcc % 10] <<
        " for client " << toPrint.toAcc << endl;
        return output;
    } else if (toPrint.transactionType == 'H') {
        output << "history" << endl;
        return output;
    } else {
        return output;
    }
}
