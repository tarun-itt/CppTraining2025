#ifndef MOCKUSER_HPP
#define MOCKUSER_HPP

#include <gmock/gmock.h>
#include "../../inc/interfaces/IUser.h"

class MockUser : public IUser {
public:
    MOCK_CONST_METHOD(std::string, getEmail, (), (const, override));
    MOCK_CONST_METHOD(std::string, getPassword, (), (const, override));
    MOCK_CONST_METHOD(uint32_t, getUserId, (), (const, override));
    MOCK_METHOD(double, requestBalance, (const LoginResult& loginResult, uint32_t accountNumber), (override));
    MOCK_METHOD(TransactionLedger, requestMiniStatement, (const LoginResult& loginResult, uint32_t accountNumber), (override));
    MOCK_METHOD(TransactionLedger, requestStatementInDateRange, (const LoginResult& loginResult, uint32_t accountNumber, std::string startDate, std::string endDate), (override));
};

#endif 