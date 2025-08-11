#include "../../inc/entities/Account.hpp"

Account::Account(uint32_t accountNumber, uint32_t accountHolderId, double depositAmount): accountNumber(accountNumber), accountHolderId(accountHolderId), transactions(TransactionLedger()) {
    addTransaction(TransactionType::DEPOSIT, depositAmount);
}

bool Account::addTransaction(TransactionType type, double amount) {
    if (type == TransactionType::WITHDRAW) {
        balance -= amount;
    } else {
        balance += amount;
    }
    
    transactions.add(new Transaction(type, amount, balance));

    return true;
}

double Account::getBalance() const {
    return balance;
}

uint32_t Account::getAccountHolderId() const {
    return accountHolderId;
}

uint32_t Account::getAccountNumber() const {
    return accountNumber;
}

TransactionLedger Account::getMiniStatement() {
    int startIndex = transactions.getSize() < 10 ? 0 : transactions.getSize()-10; 
    return transactions.getSubArray(transactions,startIndex, 10);
}

TransactionLedger Account::getRangeStatement(std::string startDate, std::string endDate) {
    int startIndex = -1;
    int endIndex = -1;
    
    for (int transactionIndex = 0; transactionIndex < transactions.getSize(); transactionIndex++) {
        std::string timestamp = transactions[transactionIndex]->getTimestamp();
        
        if (startIndex == -1 && timestamp >= startDate && timestamp <= endDate) {   
            startIndex = transactionIndex;
        }
        
        if (timestamp >= startDate && timestamp <= endDate) {
            endIndex = transactionIndex;
        }
    }
    
    int count = endIndex - startIndex + 1;
    
    return !(startIndex != -1 && endIndex != -1) ? transactions.getSubArray(transactions, startIndex, count): TransactionLedger(0);
}
