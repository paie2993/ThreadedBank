#pragma once

#include "../bank/Bank.h"

class AnafAgent {

public:
    static const int leastWaitingTime;
    static const int mostWaitingTime;

public:
    static void checkBankConsistency(Bank &bank);

    void wait(int leastTime, int mostTime);

private:
    static bool checkAccountConsistency(Account &account);

    static bool checkAccountBalanceConsistency(const Account &account);

    static bool checkAccountTransactionsConsistency(const Account &account);


    static void markConsistency();

    static void markInconsistency();
};