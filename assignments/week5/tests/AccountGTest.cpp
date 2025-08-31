#include <gtest/gtest.h>

#include "entities/Account.h"
#include "entities/Transaction.h"

class GivenTestingAccount : public ::testing::Test {
protected:
    Account* account;
    
    const int ACCOUNT_NUMBER = 12345;
    const int ACCOUNT_HOLDER_ID = 67890;
    const double INITIAL_BALANCE = 1000;
    const double DEPOSIT_AMOUNT = 100;
    const double WITHDRAW_AMOUNT = 50;
    const double LARGE_DEPOSIT = 200;
    const double LARGE_WITHDRAW = 75;
    const double OVERDRAFT_AMOUNT = 1500;

    const double NEGATIVE_TRANSACTION_AMOUNT = -25;
    const std::string VALID_START_DATE = "2025-01-01";
    const std::string VALID_END_DATE = "2025-01-01";
    const std::string INVALID_START_DATE = "sjsdls";
    const std::string INVALID_END_DATE = "random";
    
    void SetUp() override {
        account = new Account(ACCOUNT_NUMBER, ACCOUNT_HOLDER_ID, INITIAL_BALANCE);
    }
    
    void TearDown() override {
        delete account;
    }
};

TEST_F(GivenTestingAccount, whenAccountIsCreated_thenItHasCorrectDetails) {
    EXPECT_EQ(account->getAccountNumber(), ACCOUNT_NUMBER);
    EXPECT_EQ(account->getAccountHolderId(), ACCOUNT_HOLDER_ID);
    EXPECT_DOUBLE_EQ(account->getBalance(), INITIAL_BALANCE);
}

TEST_F(GivenTestingAccount, whenNegativeTransactionIsAdded_thenBalanceIncreases) {
    bool result = account->addTransaction(TransactionType::WITHDRAW, NEGATIVE_TRANSACTION_AMOUNT);
    
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(account->getBalance(), INITIAL_BALANCE - NEGATIVE_TRANSACTION_AMOUNT);
}

TEST_F(GivenTestingAccount, whenMultipleTransactionsAreAdded_thenBalanceIsCorrectlyCalculated) {
    account->addTransaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT);
    account->addTransaction(TransactionType::WITHDRAW, WITHDRAW_AMOUNT);
    account->addTransaction(TransactionType::DEPOSIT, LARGE_DEPOSIT);
    account->addTransaction(TransactionType::WITHDRAW, LARGE_WITHDRAW);
    account->addTransaction(TransactionType::DEPOSIT, LARGE_DEPOSIT*2);
    
    double expectedBalance = INITIAL_BALANCE + DEPOSIT_AMOUNT - WITHDRAW_AMOUNT + LARGE_DEPOSIT - LARGE_WITHDRAW + (LARGE_DEPOSIT*2);
    EXPECT_DOUBLE_EQ(account->getBalance(), expectedBalance);
}

TEST_F(GivenTestingAccount, whenMiniStatementIsRequested_thenTransactionsAreInCorrectOrder) {
    account->addTransaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT);
    account->addTransaction(TransactionType::WITHDRAW, WITHDRAW_AMOUNT);
    
    TransactionLedger statement = account->getMiniStatement();
    
    EXPECT_EQ(statement.getSize(), 3);
    
    EXPECT_EQ(statement[0]->getType(), TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(statement[0]->getAmount(), INITIAL_BALANCE);
    
    EXPECT_EQ(statement[1]->getType(), TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(statement[1]->getAmount(), DEPOSIT_AMOUNT);
    
    EXPECT_EQ(statement[2]->getType(), TransactionType::WITHDRAW);
    EXPECT_DOUBLE_EQ(statement[2]->getAmount(), WITHDRAW_AMOUNT);
}

TEST_F(GivenTestingAccount, whenValidDateRangeIsProvided_thenStatementIsEmpty) {
    account->addTransaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT);
    
    TransactionLedger statement = account->getStatementInDateRange(VALID_START_DATE, VALID_END_DATE);
    EXPECT_EQ(statement.getSize(), 0);
}

TEST_F(GivenTestingAccount, whenInvalidDateRangeIsProvided_thenStatementIsEmpty) {
    account->addTransaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT);
    
    TransactionLedger statement = account->getStatementInDateRange(INVALID_START_DATE, INVALID_END_DATE);
    
    EXPECT_EQ(statement.getSize(), 0);
}

TEST_F(GivenTestingAccount, whenWithdrawingMoreThanBalance_thenOverdraftIsAllowed) {
    Account smallAccount(ACCOUNT_NUMBER, ACCOUNT_HOLDER_ID, INITIAL_BALANCE);

    const double LOCAL_OVERDRAFT = INITIAL_BALANCE + 100;
    
    bool result = smallAccount.addTransaction(TransactionType::WITHDRAW, LOCAL_OVERDRAFT);
    
    EXPECT_TRUE(result);
    double actualBalance = smallAccount.getBalance();
    EXPECT_GE(actualBalance, 0);
}