#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>

enum class TransactionType{
    WITHDRAW,
    DEPOSIT
};

class Transaction {
    public:
        Transaction(TransactionType type, double amount, double balanceAfterTransaction);
        TransactionType getType() const;
        std::string getTimestamp() const;
        double getAmount() const;
        double getBalanceAfterTransaction() const;

    private:
        const TransactionType type;
        const std::string timestamp;
        const double amount;
        const double balanceAfterTransaction;

        static std::string generateTimestamp();
};

#endif