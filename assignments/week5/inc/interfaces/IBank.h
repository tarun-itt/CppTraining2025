#ifndef IBANK_HPP
#define IBANK_HPP

#include <string>
#include "../../inc/entities/TransactionLedger.hpp"

class IBank {
public:
    virtual ~IBank() = default;
    
    virtual bool validateSessionToken(std::string token) = 0;
    virtual bool processDeposit(uint32_t accountNumber, double amount, std::string token) = 0;
    virtual bool processWithdrawal(uint32_t accountNumber, double amount, std::string token) = 0;
    virtual bool processCloseAccount(uint32_t accountNumber, std::string token) = 0;
    virtual uint32_t processCreateAccount(uint32_t accountHolderId, double initialDeposit, std::string token) = 0;
    virtual double processGetBalance(uint32_t accountNumber, std::string token) = 0;
    virtual TransactionLedger processMiniStatement(uint32_t accountNumber, std::string token) = 0;
    virtual TransactionLedger processStatementInDateRange(uint32_t accountNumber, std::string token, std::string startDate, std::string endDate) = 0;
    
    virtual std::string generateSessionToken() = 0;
    virtual std::string getSessionToken() = 0;
};

#endif 