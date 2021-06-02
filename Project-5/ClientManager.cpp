#include "ClientManager.hpp"
#include <iostream>
#include <fstream>

//----------------------------------------------------------------------------
// constructor
ClientManager::ClientManager() { }

//----------------------------------------------------------------------------
// destructor
ClientManager::~ClientManager() { }

//----------------------------------------------------------------------------
// buildTree
// builds the tree of clients, reads in from lab5data.txt
void ClientManager::buildTree() {
    ifstream infile("lab5data.txt");  // client data .txt file
    if (!infile)  {                   // check for successful open
       cout << "File could not be opened." << endl; // error message
    }
    
    // loop through file until eof()
    for (;;) {
        Client* toInsert = new Client(infile); // create client object

        if (infile.eof()) {           // check eof
            delete toInsert;          // delete client object
            break;
        }
        
        bool success = clientTree.insert(toInsert); // insert client to tree
        
        // check if insert was successful
        if (!success) {
            delete toInsert;          // delete client object if !success
        }
        toInsert = nullptr;
        delete toInsert;
    }
}

//----------------------------------------------------------------------------
// buildQueueTransactions
// builds the queue to hold transactions from lab5commmand.txt
void ClientManager::buildQueueTransactions() {
    ifstream infile("lab5command.txt"); // transaction .txt file
    if(!infile) {                       // check for successful open
        cout << "File could not be opened." << endl;
    }
    for (;;) {
        Transaction* toInsert = new Transaction(infile);
        
        if (infile.eof()) {           // check eof
            delete toInsert;          // delete transaction object
            toInsert = nullptr;
            break;
        }
        
        bool success = toInsert->checkValidTransactionType();
        
        // check if transaction is of valid type 'D' 'W' 'M' or 'H'
        if (!success) {
            delete toInsert;          // delete Treansaction if !success
        }
        clientTransactions.push(toInsert); // insert transaction to queue
        
        toInsert = nullptr;
        delete toInsert;
    }
}

//----------------------------------------------------------------------------
// displayQueueTransactions
// Note: This is just for testing to see if queue has all the valid
// transactions
void ClientManager::displayQueueTransactions() {
    while(!clientTransactions.empty()) {
        cout << *clientTransactions.front(); // print Transaction
        clientTransactions.pop();            // pop Transaction from queue
    }
}

//----------------------------------------------------------------------------
// displayReport
// calls the display funtion on the BSTree in BSTree class
void ClientManager::displayReport() const {
        cout << endl << "REPORT" << endl << endl;
        clientTree.display();  // BSTree display member function call
}

//----------------------------------------------------------------------------
// deposit
void ClientManager::deposit(Transaction* deposit) {
    Client* tempClient = new Client();  // temporary client
    bool success;
    
    int clientNumber = deposit->getFromClient(); // gets the Client AcctNum
    
    Client toRetrieve(clientNumber); // creates temporary Client
    
    success = clientTree.retrieve(toRetrieve, tempClient);
    
    if (success) {   // client was found
        tempClient->history.push_back(deposit);
        
        int accountNum = deposit->getToAccount() % 10;
        tempClient->deposit(accountNum, deposit->getFunds());
    } else {         // client not found
        cout << "Unknown client ID " << deposit->getFromClient() <<
        " requested" << endl;
    }
    
    tempClient = nullptr;
    delete tempClient;
}

//----------------------------------------------------------------------------
// withdraw
void ClientManager::withdraw(Transaction* withdraw) {
    Client* tempClient = new Client();  // temporary client
    bool success;
    
    int clientNumber = withdraw->getFromClient(); // gets the Client AcctNum
    
    Client toRetrieve(clientNumber); // creates temporary Client
    
    success = clientTree.retrieve(toRetrieve, tempClient);
    
    if (success) {  // client was found
        tempClient->history.push_back(withdraw); // add to history
        
        int accountNum = withdraw->getToAccount() % 10;
        tempClient->withdraw(accountNum, withdraw->getFunds());
    } else {        // client was not found
        cout << "Withdraw not performed on " << withdraw->getToAccount() <<
        " for client " << withdraw->getFromClient() << endl << endl;
    }
    tempClient = nullptr;
    delete tempClient;
}

//----------------------------------------------------------------------------
// withdraw, calls deposit and withdraw
void ClientManager::move(Transaction* move) {
    Client* temp1 = new Client(); // from client
    Client* temp2 = new Client(); // to client
    bool success;
    
    int fromClientNum = move->getFromClient();
    int toClientNum = move->gerToClient();
    
    Client toRetrieve1(fromClientNum); // temporary client
    Client toRetrieve2(toClientNum);   // temporary client
    
    // searches for fromClient
    success = clientTree.retrieve(toRetrieve1, temp1);
    
    if (success) { // from client was found
        
        // searches for toClient
        success = clientTree.retrieve(toRetrieve2, temp2);
        
        if (success) {
            int fromAccountNum = move->getFromAccount() % 10;
            int toAccountNum = move->getToAccount() % 10;
            
            temp1->history.push_back(move);  // add to history
            //temp2->history.push_back(move); // add to history
            
            // withdraws from fromClient
            temp1->withdraw(fromAccountNum, move->getFunds());
            // deposits to toClient
            temp2->deposit(toAccountNum, move->getFunds());
        } else {
            cout << "Unknown client ID " << move->getFromClient() <<
            " or " << move->gerToClient() << " requested" << endl;
        }
    } else {
        cout << "Unknown client ID " << move->getFromClient() << " or " <<
        move->gerToClient() << " requested" << endl;
    }
    temp1 = temp2 = nullptr;
    delete temp1;
    delete temp2;
}

//----------------------------------------------------------------------------
// history
void ClientManager::history(Transaction* history) {
    Client* temp = new Client(); // temporary client
    bool success;
    
    // client number
    int fromClientNum = history->getFromClient();
    
    Client toRetrieve(fromClientNum); // creates temporary client
    
    success = clientTree.retrieve(toRetrieve, temp);
    
    if (success) {
        temp->history.push_back(history);
        vector<Transaction*> clientHistory = temp->getHistory();
        
        cout << endl;
        cout << "History of transactions for client " << temp->getFirstName()
        << " " << temp->getLastName() << ", client ID = " <<
        temp->getAccountNumber() << endl;
        cout << "Type      Amount  Detail" << endl;
        cout << "--------- ------- --------------------------------------"
        << endl;
        
        for (int i = 0; i < clientHistory.size(); i++) {
            cout << *clientHistory.at(i);
        }
        cout << endl;
    } else {
        cout << "Unknown client ID " << history->getFromClient() <<
        " requested" << endl;
    }
    
    temp = nullptr;
    delete temp;
}

//----------------------------------------------------------------------------
// runBusiness
void ClientManager::runBuisiness() {
    
    // loops until queue is empty
    while (!clientTransactions.empty()) {
        Transaction* transactionToProcess; // transaction to be processed
        transactionToProcess = clientTransactions.front(); //gets Transaction
        clientTransactions.pop(); // dequeue
        
        switch (transactionToProcess->getTransactionType()) {
            case 'D':
                deposit(transactionToProcess);
                break;
            case 'W':
                withdraw(transactionToProcess);
                break;
            case 'M':
                move(transactionToProcess);
                break;
            case 'H':
                history(transactionToProcess);
                break;
            // invalid transaction type, handled in checkValidTransation type
            default:
                break;
        }
        transactionToProcess = nullptr;
        delete transactionToProcess;
    }
}
