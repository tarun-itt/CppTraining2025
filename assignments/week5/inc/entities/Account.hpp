#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <cstdint>
#include <string>

#include "Transaction.hpp"
#include "TransactionLedger.hpp"

class Account {
    public:
        Account(uint32_t accountNumber, uint32_t accountHolderId, double balance);
        bool addTransaction(TransactionType type, double amount);
        double getBalance() const;
        uint32_t getAccountHolderId() const;
        uint32_t getAccountNumber() const;
        TransactionLedger getMiniStatement();
        TransactionLedger getStatementInDateRange(std::string startDate, std::string endDate);

    private:
        uint32_t accountNumber;
        uint32_t accountHolderId;
        double balance;
        TransactionLedger transactions;
};

#endif