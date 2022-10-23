#pragma once

#include <mutex>
#include <vector>
#include <memory>
#include "../operation/Operation.h"

class Operation;

class Account {

private:
    const double initialBalance;

    int id;
    double balance;
    std::mutex mutex;

    std::vector<std::shared_ptr<Operation>> operations;

public:
    Account(int id, double balance);

    Account(const Account &account);

    const double getInitialBalance() const;

    int getId() const;

    double getBalance() const;

    std::mutex &getMutex();

    const std::vector<std::shared_ptr<Operation>> &getOperations() const;

    bool operationExists(const Operation &operation) const;

    void transact(const std::shared_ptr<Operation> &operation);

    std::string toString() const;

    bool operator==(const Account &other) const;

    ~Account();

private:
    void increaseBalance(double amount);

    void decreaseBalance(double amount);

    std::string operationsToString() const;
};