#include "ClientManager.hpp"

int main() {
    ClientManager lose;
    lose.buildTree();
    lose.buildQueueTransactions();
    //lose.displayQueueTransactions();
    lose.runBuisiness();
    lose.displayReport();
}
