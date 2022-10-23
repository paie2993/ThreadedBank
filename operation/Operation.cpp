#include "Operation.h"

uint64_t Operation::lastSerial = 0;

Operation::Operation(Account &sender, Account &receiver, double amount) :
        sender(sender), receiver(receiver), amount(amount) {
    serial = generateSerial();
}

Account &Operation::getSender() {
    return sender;
}

Account &Operation::getReceiver() {
    return receiver;
}

double Operation::getAmount() const {
    return amount;
}

const uint64_t Operation::getSerial() const {
    return serial;
}

std::string Operation::toString() const {
    std::string totalString;
    totalString.append("[ ");
    totalString.append("From account ");
    totalString.append(std::to_string(sender.getId()));
    totalString.append(", ");
    totalString.append(std::to_string(amount));
    totalString.append(" $ to account ");
    totalString.append(std::to_string(receiver.getId()));
    totalString.append(" ]");
    return totalString;
}

bool Operation::operator==(const Operation &other) const {
    if (serial == other.serial) {
        return true;
    }
    return false;
}

uint64_t Operation::generateSerial() {
    lastSerial = lastSerial + 1;
    return lastSerial;
}
