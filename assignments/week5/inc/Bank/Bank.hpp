#ifndef BANK_HPP
#define BANK_HPP

#include <string>

#include "../entities/Account.hpp"
#include "../entities/AccountRegistry.hpp"

class Bank {
public:
    static Bank* getInstance();
    bool validateSessionToken(std::string token);
    bool processDeposit(uint32_t accountNumber, double amount, std::string token);
    bool processWithdrawal(uint32_t accountNumber, double amount, std::string token);
    bool processCloseAccount(uint32_t accountNumber, std::string token);
    uint32_t processCreateAccount(uint32_t accountHolderId, double initialDeposit, std::string token);
    double processGetBalance(uint32_t accountNumber, std::string token);
    TransactionLedger processMiniStatement(uint32_t accountNumber, std::string token);
    TransactionLedger processStatementInDateRange(uint32_t accountNumber, std::string token, std::string startDate, std::string endDate);

    friend class AuthController;

private:
    Bank();
    ~Bank();
    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    
    static Bank* instance;
    AccountRegistry accounts;
    std::string activeSessionToken;
    
    std::string generateSessionToken();
    std::string getSessionToken();
    Account* findAccount(uint32_t accountNumber);
    uint32_t generateAccountNumber();
};

#endif