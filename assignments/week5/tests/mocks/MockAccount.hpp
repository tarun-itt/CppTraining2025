#ifndef MOCKACCOUNT_HPP
#define MOCKACCOUNT_HPP

#include <gmock/gmock.h>
#include "../../inc/interfaces/IAccount.h"
#include "../../inc/entities/Transaction.hpp"

class MockAccount : public IAccount {
public:
    MOCK_METHOD(bool, addTransaction, (TransactionType type, double amount), (override));
    MOCK_CONST_METHOD(double, getBalance, (), (const, override));
    MOCK_CONST_METHOD(uint32_t, getAccountHolderId, (), (const, override));
    MOCK_CONST_METHOD(uint32_t, getAccountNumber, (), (const, override));
    MOCK_METHOD(TransactionLedger, getMiniStatement, (), (override));
    MOCK_METHOD(TransactionLedger, getStatementInDateRange, (std::string startDate, std::string endDate), (override));
};

#endif 