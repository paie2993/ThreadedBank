#pragma once

#include <vector>
#include "../account/Account.h"

class Bank {

private:
    std::vector<Account *> accounts;

public:
    static double lowestTransactionAmount;

public:
    Bank(const std::string &filename);

    std::vector<Account *> &getAccounts();

    Account &pickRandomAccount();

    std::string toString() const;

    ~Bank();

private:
    void initialize(const std::string &filename);

    uint64_t getNumberOfAccounts() const;

    static uint64_t randomNumber(uint64_t upperLimit);
};