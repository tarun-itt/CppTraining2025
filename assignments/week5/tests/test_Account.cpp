#include <gtest/gtest.h>
#include "../inc/entities/Account.hpp"
#include "../inc/entities/Transaction.hpp"

class AccountTest : public ::testing::Test {
protected:
    Account* account;
    
    void SetUp() override {
        account = new Account(12345, 67890, 1000);
    }
    
    void TearDown() override {
        delete account;
    }
};

TEST_F(AccountTest, AccountDetails) {
    EXPECT_EQ(account->getAccountNumber(), 12345);
    EXPECT_EQ(account->getAccountHolderId(), 67890);
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000);
}


TEST_F(AccountTest, NegativeTransaction) {
    bool result = account->addTransaction(TransactionType::WITHDRAW, -25);
    
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(account->getBalance(), 1025);
}

TEST_F(AccountTest, Transactions) {
    account->addTransaction(TransactionType::DEPOSIT, 100);
    account->addTransaction(TransactionType::WITHDRAW, 50);
    account->addTransaction(TransactionType::DEPOSIT, 200);
    account->addTransaction(TransactionType::WITHDRAW, 75);
    account->addTransaction(TransactionType::DEPOSIT, 300);
    
    EXPECT_DOUBLE_EQ(account->getBalance(), 1475);
}

TEST_F(AccountTest, StatementOrder) {
    account->addTransaction(TransactionType::DEPOSIT, 100);
    account->addTransaction(TransactionType::WITHDRAW, 50);
    
    TransactionLedger statement = account->getMiniStatement();
    
    EXPECT_EQ(statement.getSize(), 3);
    
    EXPECT_EQ(statement[0]->getType(), TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(statement[0]->getAmount(), 1000);
    
    EXPECT_EQ(statement[1]->getType(), TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(statement[1]->getAmount(), 100);
    
    EXPECT_EQ(statement[2]->getType(), TransactionType::WITHDRAW);
    EXPECT_DOUBLE_EQ(statement[2]->getAmount(), 50);
}

TEST_F(AccountTest, ValidDateStatement) {
    account->addTransaction(TransactionType::DEPOSIT, 100);

    std::string startDate = "2025-01-01";
    std::string endDate = "2025-01-01";
    
    TransactionLedger statement = account->getStatementInDateRange(startDate, endDate);
    EXPECT_EQ(statement.getSize(), 0);
}

TEST_F(AccountTest, InvalidDateStatement) {
    account->addTransaction(TransactionType::DEPOSIT, 100);
    
    std::string startDate = "sjsdls";
    std::string endDate = "random";
    
    TransactionLedger statement = account->getStatementInDateRange(startDate, endDate);
    
    EXPECT_EQ(statement.getSize(), 0);
}

TEST_F(AccountTest, WithdrawingMoreThanBalance) {
    Account smallAccount(12345, 67890, 100);
    
    bool result = smallAccount.addTransaction(TransactionType::WITHDRAW, 150);
    
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(smallAccount.getBalance(), -50);
}