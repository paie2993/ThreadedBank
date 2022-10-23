#pragma once

#include <cstdint>
#include "../account/Account.h"

class Account;

class Operation {

private:
    static uint64_t lastSerial;

    uint64_t serial;
    Account &sender;
    Account &receiver;
    double amount;

public:
    Operation(Account &sender, Account &receiver, double amount);

    const uint64_t getSerial() const;

    Account &getSender();

    Account &getReceiver();

    double getAmount() const;

    std::string toString() const;

    bool operator==(const Operation &other) const;

private:
    static uint64_t generateSerial();
};