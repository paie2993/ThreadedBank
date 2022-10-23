#include <random>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>
#include "BankOperator.h"

const int BankOperator::numberOfTransactionsPerDay = 2;
const int BankOperator::mostWaitingTime = 8000;
const int BankOperator::leastWaitingTime = 1000;

BankOperator::BankOperator(Bank &bank) : bank(bank) {
}

void BankOperator::carryOutDuty() {
    for (int i = 0; i < numberOfTransactionsPerDay; i++) {
        carryOutTransaction();
    }
}

void BankOperator::carryOutTransaction() {
    Account &sender = bank.pickRandomAccount();
    Account &receiver = bank.pickRandomAccount();
    double amount = determineFittingAmount(sender);
    executeTransaction(sender, receiver, amount);
}

double BankOperator::determineFittingAmount(const Account &sender) {
    return pickFittingAmount(Bank::lowestTransactionAmount, sender.getBalance());
}

double BankOperator::pickFittingAmount(double lowerLimit, double upperLimit) {
    std::uniform_real_distribution<double> uniform(lowerLimit, upperLimit);
    std::default_random_engine engine;
    return uniform(engine);
}

void BankOperator::executeTransaction(Account &sender, Account &receiver, double amount) {
    int senderId = sender.getId();
    int receiverId = receiver.getId();

    if (senderId == receiverId) {
        return;
    }

    std::shared_ptr<Operation> operation = std::make_shared<Operation>(sender, receiver, amount);

    if (senderId < receiverId) {
        sendReceive(operation);
    } else {
        receiveSend(operation);
    }

    std::cout << "Executed: " << operation->toString() << "\n";
}

void BankOperator::sendReceive(const std::shared_ptr<Operation> &operation) {
    Account &sender = operation->getSender();
    Account &receiver = operation->getReceiver();

    sender.getMutex().lock();
    sender.transact(operation);

    receiver.getMutex().lock();
    sender.getMutex().unlock();

    receiver.transact(operation);
    receiver.getMutex().unlock();
}

void BankOperator::receiveSend(const std::shared_ptr<Operation> &operation) {
    Account &sender = operation->getSender();
    Account &receiver = operation->getReceiver();

    receiver.getMutex().lock();
    receiver.transact(operation);

    sender.getMutex().lock();
    receiver.getMutex().unlock();

    sender.transact(operation);
    sender.getMutex().unlock();
}

void BankOperator::wait(const int leastTime, const int mostTime) {
    int waitingTime = rand() % (mostTime - leastTime) + leastTime;
    std::string logMessage;
    std::cout << logMessage.append("Operator waits ").append(std::to_string(waitingTime)).append(" ms\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
}