#include <gtest/gtest.h>
#include "entities/Transaction.h"

class GivenTestingTransaction : public ::testing::Test {
protected:
    
    const double DEPOSIT_AMOUNT = 100;
    const double WITHDRAW_AMOUNT = 50;
    const double BALANCE_AFTER_DEPOSIT = 1100;
    const double BALANCE_AFTER_WITHDRAW = 950;
};

TEST_F(GivenTestingTransaction, whenTransactionIsCreatedWithValidData_thenItHasCorrectProperties) {
    Transaction transaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT, BALANCE_AFTER_DEPOSIT);
    
    EXPECT_EQ(transaction.getType(), TransactionType::DEPOSIT);
    EXPECT_EQ(transaction.getAmount(), DEPOSIT_AMOUNT);
    EXPECT_EQ(transaction.getBalanceAfterTransaction(), BALANCE_AFTER_DEPOSIT);
    EXPECT_FALSE(transaction.getTimestamp().empty());
}

TEST_F(GivenTestingTransaction, whenGetTypeIsCalled_thenItReturnsCorrectTransactionType) {
    Transaction deposit(TransactionType::DEPOSIT, DEPOSIT_AMOUNT, BALANCE_AFTER_DEPOSIT);
    Transaction withdraw(TransactionType::WITHDRAW, WITHDRAW_AMOUNT, BALANCE_AFTER_WITHDRAW);
    
    EXPECT_EQ(deposit.getType(), TransactionType::DEPOSIT);
    EXPECT_EQ(withdraw.getType(), TransactionType::WITHDRAW);
}

TEST_F(GivenTestingTransaction, whenGetTimestampIsCalled_thenItReturnsNonEmptyString) {
    Transaction transaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT, BALANCE_AFTER_DEPOSIT);
    
    std::string timestamp = transaction.getTimestamp();
    EXPECT_FALSE(timestamp.empty());
    EXPECT_GT(timestamp.length(), 0);
} 