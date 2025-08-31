#include <ctime>
#include <cstring>

#include "../../inc/entities/Transaction.h"

Transaction::Transaction(TransactionType type, double amount, double balanceAfterTransaction) 
    : type(type), timestamp(generateTimestamp()), amount(amount), balanceAfterTransaction(balanceAfterTransaction) {
}

TransactionType Transaction::getType() const {
    return type;
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

double Transaction::getAmount() const {
    return amount;
}

double Transaction::getBalanceAfterTransaction() const {
    return balanceAfterTransaction;
}

std::string Transaction::generateTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[32]; 
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}