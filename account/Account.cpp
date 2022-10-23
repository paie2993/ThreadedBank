#include <memory>
#include "Account.h"

Account::Account(int id, double balance) : initialBalance(balance), id(id), balance(balance) {
}

Account::Account(const Account &account) : initialBalance(account.initialBalance) {
    id = account.id;
    balance = account.balance;
}

const double Account::getInitialBalance() const {
    return initialBalance;
}

int Account::getId() const {
    return id;
}

double Account::getBalance() const {
    return balance;
}

std::mutex &Account::getMutex() {
    return mutex;
}

const std::vector<std::shared_ptr<Operation>> &Account::getOperations() const {
    return operations;
}

bool Account::operationExists(const Operation &operation) const {
    for (const auto &loggedOperation: operations) {
        if (*loggedOperation == operation) {
            return true;
        }
    }
    return false;
}

void Account::transact(const std::shared_ptr<Operation> &operation) {
    double amount = operation->getAmount();
    if (operation->getSender().getId() == id) {
        decreaseBalance(amount);
    } else if (operation->getReceiver().getId() == id) {
        increaseBalance(amount);
    } else {
        throw std::exception();
    }
    operations.push_back(operation);
}

std::string Account::toString() const {
    std::string totalString;
    totalString.append(std::to_string(id)).append(" ");
    totalString.append(std::to_string(balance));
    totalString.append("\n");
    totalString.append(operationsToString());
    return totalString;
}

bool Account::operator==(const Account &other) const {
    if (id == other.id) {
        return true;
    }
    return false;
}

Account::~Account() = default;

std::string Account::operationsToString() const {
    std::string totalString;
    for (const auto &operation: operations) {
        totalString.append("\t");
        totalString.append(operation->toString());
        totalString.append("\n");
    }
    return totalString;
}

void Account::increaseBalance(double amount) {
    balance = balance + amount;
}

void Account::decreaseBalance(double amount) {
    balance = balance - amount;
}