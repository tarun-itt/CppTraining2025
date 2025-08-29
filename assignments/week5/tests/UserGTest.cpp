#include <gtest/gtest.h>

#include "auth/LoginResult.h"
#include "mocks/MockBank.h"
#include "roles/AccountHolder.h"
#include "entities/TransactionLedger.h"

class GivenTestingUser : public ::testing::Test {
protected:
    AccountHolder* user;
    MockBank* mockBank;
    LoginResult loginResult;

    const std::string TEST_EMAIL = "test@example.com";
    const std::string TEST_PASSWORD = "password123";
    const uint32_t TEST_USER_ID = 12345;
    const uint32_t TEST_ACCOUNT_NUMBER = 67890;
    const std::string TEST_SESSION_TOKEN = "test-session-token";
    const std::string TEST_START_DATE = "01-01-2025";
    const std::string TEST_END_DATE = "31-08-2025";
    const double EXPECTED_BALANCE = 1000;

    void SetUp() override {
        user = new AccountHolder(TEST_EMAIL, TEST_PASSWORD, TEST_USER_ID);
        mockBank = new MockBank();
        
        loginResult.bank = mockBank;
        loginResult.user = user;
        loginResult.sessionToken = TEST_SESSION_TOKEN;
    }
    
    void TearDown() override {
        delete user;
        delete mockBank;
    }
};

TEST_F(GivenTestingUser, whenUserIsCreatedWithValidData_thenItHasCorrectProperties) {
    EXPECT_EQ(user->getEmail(), TEST_EMAIL);
    EXPECT_EQ(user->getPassword(), TEST_PASSWORD);
    EXPECT_EQ(user->getUserId(), TEST_USER_ID);
}

TEST_F(GivenTestingUser, whenMiniStatementIsRequested_thenMockBankIsCalledCorrectly) {
    EXPECT_CALL(*mockBank, processMiniStatement(TEST_ACCOUNT_NUMBER, TEST_SESSION_TOKEN))
        .Times(1).WillOnce(::testing::Return(TransactionLedger()));

    TransactionLedger statement = user->requestMiniStatement(loginResult, TEST_ACCOUNT_NUMBER);
}

TEST_F(GivenTestingUser, whenStatementInDateRangeIsRequested_thenMockBankIsCalledCorrectly) {
    EXPECT_CALL(*mockBank, processStatementInDateRange(TEST_ACCOUNT_NUMBER, TEST_SESSION_TOKEN, TEST_START_DATE, TEST_END_DATE))
        .Times(1).WillOnce(::testing::Return(TransactionLedger()));

    TransactionLedger statement = user->requestStatementInDateRange(loginResult, TEST_ACCOUNT_NUMBER, TEST_START_DATE, TEST_END_DATE);
} 

TEST_F(GivenTestingUser, whenBalanceIsRequested_thenMockBankReturnsCorrectBalance) {
    EXPECT_CALL(*mockBank, processGetBalance(TEST_ACCOUNT_NUMBER, TEST_SESSION_TOKEN))
        .Times(1).WillOnce(::testing::Return(EXPECTED_BALANCE));

    double balance = user->requestBalance(loginResult, TEST_ACCOUNT_NUMBER);
    EXPECT_EQ(balance, EXPECTED_BALANCE);
}