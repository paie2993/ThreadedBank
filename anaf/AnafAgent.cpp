#include <iostream>
#include <thread>
#include "AnafAgent.h"

const int AnafAgent::leastWaitingTime = 4000;
const int AnafAgent::mostWaitingTime = 6000;

void AnafAgent::checkBankConsistency(Bank &bank) {
    std::vector<Account *> &accounts = bank.getAccounts();
    for (auto account: accounts) {
        if (!checkAccountConsistency(*account)) {
            markInconsistency();
            return;
        }
    }
    markConsistency();
}

bool AnafAgent::checkAccountConsistency(Account &account) {
    account.getMutex().lock();
    bool consistent = checkAccountBalanceConsistency(account);
    consistent = consistent && checkAccountTransactionsConsistency(account);
    account.getMutex().unlock();
    return consistent;
}

bool AnafAgent::checkAccountBalanceConsistency(const Account &account) {
    double initialBalance = account.getInitialBalance();
    for (const auto &operation: account.getOperations()) {
        const int senderId = operation->getSender().getId();
        const int receiverId = operation->getReceiver().getId();
        double amount = operation->getAmount();
        if (senderId == account.getId()) {
            initialBalance = initialBalance - amount;
        } else if (receiverId == account.getId()) {
            initialBalance = initialBalance + amount;
        } else {
            return false;
        }
    }
    if (initialBalance - account.getBalance() > 0.0000001) {
        return false;
    }
    return true;
}

bool AnafAgent::checkAccountTransactionsConsistency(const Account &account) {
    for (const auto &operation: account.getOperations()) {
        Account &sender = operation->getSender();
        Account &receiver = operation->getReceiver();
        if (account == sender) {
            receiver.operationExists(*operation);
        } else if (account == receiver) {
            sender.operationExists(*operation);
        } else {
            return false;
        }
    }
    return true;
}

void AnafAgent::wait(const int leastTime, const int mostTime) {
    int waitingTime = rand() % (mostTime - leastTime) + leastTime;
    std::string logMessage;
    std::cout << logMessage.append("Agent waits ").append(std::to_string(waitingTime)).append(" ms\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
}

void AnafAgent::markConsistency() {
    std::cout << "Bank clear" << "\n";
}

void AnafAgent::markInconsistency() {
    std::cout << "Bad luck" << "\n";
}