#include <fstream>
#include "Bank.h"

double Bank::lowestTransactionAmount = 0;

Bank::Bank(const std::string &filename) {
    initialize(filename);
}

std::vector<Account *> &Bank::getAccounts() {
    return accounts;
}

std::string Bank::toString() const {
    std::string totalString;
    for (auto account: accounts) {
        totalString.append(account->toString()).append("\n");
    }
    return totalString;
}

Bank::~Bank() {
    for (auto account: accounts) {
        delete account;
    }
}


void Bank::initialize(const std::string &filename) {
    std::ifstream fileStream(filename);

    int id;
    double balance;

    fileStream >> id >> balance;
    while (!fileStream.eof()) {
        accounts.push_back(new Account(id, balance));
        fileStream >> id >> balance;
    }
}

Account &Bank::pickRandomAccount() {
    uint64_t numberOfAccounts = getNumberOfAccounts();
    uint64_t randomAccountIndex = randomNumber(numberOfAccounts - 1);
    return *(accounts[randomAccountIndex]);
}

uint64_t Bank::getNumberOfAccounts() const {
    return accounts.size();
}

uint64_t Bank::randomNumber(uint64_t upperLimit) {
    return rand() % (upperLimit + 1);
}