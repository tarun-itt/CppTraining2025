#ifndef MOCKBANK_HPP
#define MOCKBANK_HPP

#include <gmock/gmock.h>

#include "interfaces/IBank.h"
#include "entities/TransactionLedger.h"

class MockBank : public IBank {
public:

    MOCK_METHOD(bool, validateSessionToken, (std::string token), (override));
    MOCK_METHOD(bool, processDeposit, (uint32_t accountNumber, double amount, std::string token), (override));
    MOCK_METHOD(bool, processWithdrawal, (uint32_t accountNumber, double amount, std::string token), (override));
    MOCK_METHOD(bool, processCloseAccount, (uint32_t accountNumber, std::string token), (override));
    MOCK_METHOD(uint32_t, processCreateAccount, (uint32_t accountHolderId, double initialDeposit, std::string token), (override));
    MOCK_METHOD(double, processGetBalance, (uint32_t accountNumber, std::string token), (override));
    MOCK_METHOD(TransactionLedger, processMiniStatement, (uint32_t accountNumber, std::string token), (override));
    MOCK_METHOD(TransactionLedger, processStatementInDateRange, (uint32_t accountNumber, std::string token, std::string startDate, std::string endDate), (override));
    MOCK_METHOD(std::string, generateSessionToken, (), (override));
    MOCK_METHOD(std::string, getSessionToken, (), (override));
};

#endif 