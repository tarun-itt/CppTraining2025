#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <cstdint>
#include <string>

#include "Transaction.hpp"
#include "TransactionArray.hpp"

class Account {
    public:
        Account(uint32_t accountNumber, uint32_t accountHolderId, double balance);
        bool addTransaction(TransactionType type, double amount);
        double getBalance() const;
        uint32_t getAccountHolderId() const;
        uint32_t getAccountNumber() const;
        TransactionArray getMiniStatement();
        TransactionArray getRangeStatement(std::string startDate, std::string endDate);

    private:
        uint32_t accountNumber;
        uint32_t accountHolderId;
        double balance;
        TransactionArray transactions;
};

#endif