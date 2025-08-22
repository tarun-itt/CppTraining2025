#include <gtest/gtest.h>
#include "../inc/auth/LoginResult.hpp"
#include "mocks/MockBank.hpp"
#include "../inc/roles/AccountHolder.hpp"

class UserTest : public ::testing::Test {
protected:
    AccountHolder user;
    MockBank* mockBank;
    LoginResult loginResult;

    void SetUp() override {

        user = AccountHolder("test@example.com", "password123", 12345);
        mockBank = new MockBank();
        
        loginResult.bank = mockBank;
        loginResult.user = &user;
        loginResult.sessionToken = "test-session-token";
    }
    
    void TearDown() override {
    }
};

TEST_F(UserTest, ConstructorWithValidData) {
    EXPECT_EQ(user.getEmail(), "test@example.com");
    EXPECT_EQ(user.getPassword(), "password123");
    EXPECT_EQ(user.getUserId(), 12345);
}

TEST_F(UserTest, MiniStatement) {
    EXPECT_CALL(*mockBank, processMiniStatement(67890, "test-session-token"))
        .WillOnce(::testing::Return(TransactionLedger())).Times(1);

    TransactionLedger statement = user.requestMiniStatement(loginResult, 67890);
}

TEST_F(UserTest, StatementInDateRange) {
    EXPECT_CALL(*mockBank, processStatementInDateRange(67890, "test-session-token", "01-01-2025", "31-08-2025"))
        .WillOnce(::testing::Return(TransactionLedger())).Times(1);

    TransactionLedger statement = user.requestStatementInDateRange(loginResult, 67890, "01-01-2025", "31-08-2025");
} 

TEST_F(UserTest, CheckBalance) {
    EXPECT_CALL(*mockBank, processGetBalance(67890, "test-session-token"))
        .WillOnce(::testing::Return(1000)).Times(1);

    double balance = user.requestBalance(loginResult, 67890);
    EXPECT_EQ(balance, 1000);
}