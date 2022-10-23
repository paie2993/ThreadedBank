#pragma once

#include "../bank/Bank.h"

class BankOperator {

private:
    static const int numberOfTransactionsPerDay;
    Bank &bank;

public:
    static const int leastWaitingTime;
    static const int mostWaitingTime;

public:
    BankOperator(Bank &bank);

    void carryOutDuty();

    void carryOutTransaction();

    void wait(int leastTime, int mostTime);

private:
    static double determineFittingAmount(const Account &sender);

    static double pickFittingAmount(double lowerLimit, double upperLimit);

    static void executeTransaction(Account &sender, Account &receiver, double amount);

    static void sendReceive(const std::shared_ptr<Operation> &operation);

    static void receiveSend(const std::shared_ptr<Operation> &operation);

};