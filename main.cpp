#include <iostream>
#include <thread>
#include "bank/Bank.h"
#include "operator/BankOperator.h"
#include "anaf/AnafAgent.h"

const int OPERATORS_IN_ACTION = 3;
const int MIN_ANAF_AGENT = 2;
const int MAX_ANAF_AGENTS = 5;
const int LAST_AGENT_INDEX = 999;

void putBankOperatorToWork(Bank *bank, const int operatorIndex, const int randomSeed) {
    srand(randomSeed);
    BankOperator bankOperator(*bank);
    bankOperator.wait(BankOperator::leastWaitingTime, BankOperator::mostWaitingTime);
    std::cout << "Bank operator number " << std::to_string(operatorIndex) << " starting work" << "\n";
    bankOperator.carryOutDuty();
    std::cout << "Bank operator number " << std::to_string(operatorIndex) << " finished work" << "\n";
}

void dispatchOperators(Bank *bank, const int noOperatorThreads, const int randomSeed) {
    srand(randomSeed);
    std::vector<std::thread> threads(noOperatorThreads);

    for (int i = 0; i < noOperatorThreads; i++) {
        threads[i] = std::thread(putBankOperatorToWork, bank, i + 1, rand());
    }

    for (int i = 0; i < noOperatorThreads; i++) {
        threads[i].join();
    }
}

void putAnafAgentToWork(Bank *bank, const int agentIndex, const int randomSeed) {
    srand(randomSeed);
    AnafAgent anafAgent;
    anafAgent.wait(AnafAgent::leastWaitingTime, AnafAgent::mostWaitingTime);
    std::cout << "Anaf agent number " << std::to_string(agentIndex) << " starting bank check" << "\n";
    AnafAgent::checkBankConsistency(*bank);
    std::cout << "Anaf agent number " << std::to_string(agentIndex) << " finished bank check" << "\n";
}

void dispatchAnafAgents(Bank *bank, const int noAnafAgents, const int randomSeed) {
    srand(randomSeed);
    std::vector<std::thread> threads(noAnafAgents);

    for (int i = 0; i < noAnafAgents; i++) {
        threads[i] = std::thread(putAnafAgentToWork, bank, i + 1, rand());
    }
    for (int i = 0; i < noAnafAgents; i++) {
        threads[i].join();
    }
}

void startWorkDay(Bank &bank, const int noOperatorThreads, const int noAnafAgents) {
    srand(time(nullptr));

    std::thread operatorsThread(dispatchOperators, &bank, noOperatorThreads, rand());
    std::thread agentsThread(dispatchAnafAgents, &bank, noAnafAgents, rand());

    operatorsThread.join();
    agentsThread.join();

    std::thread lastCheckThread(putAnafAgentToWork, &bank, LAST_AGENT_INDEX, rand());
    lastCheckThread.join();
}

int determineAnafAgents(const int minAnafAgents, const int maxAnafAgents) {
    return rand() % (maxAnafAgents - minAnafAgents) + minAnafAgents;
}

int main() {
    const std::string filename("../res/accounts.txt");

    Bank bank(filename);
    std::cout << bank.toString() << "\n";

    const int noAnafAgents = determineAnafAgents(MIN_ANAF_AGENT, MAX_ANAF_AGENTS);
    startWorkDay(bank, OPERATORS_IN_ACTION, noAnafAgents);

    std::cout << bank.toString() << "\n";

    return 0;
}
