#include <gtest/gtest.h>
#include "../inc/entities/Transaction.hpp"


TEST(TransactionTest, ConstructorWithValidData) {
    Transaction transaction(TransactionType::DEPOSIT, 100, 1100);
    
    EXPECT_EQ(transaction.getType(), TransactionType::DEPOSIT);
    EXPECT_EQ(transaction.getAmount(), 100);
    EXPECT_EQ(transaction.getBalanceAfterTransaction(), 1100);
    EXPECT_FALSE(transaction.getTimestamp().empty());
}

TEST(TransactionTest, GetTypeReturnsCorrectValue) {
    Transaction deposit(TransactionType::DEPOSIT, 100, 1100);
    Transaction withdraw(TransactionType::WITHDRAW, 50, 950);
    
    EXPECT_EQ(deposit.getType(), TransactionType::DEPOSIT);
    EXPECT_EQ(withdraw.getType(), TransactionType::WITHDRAW);
}

TEST(TransactionTest, GetTimestampReturnsNonEmptyString) {
    Transaction transaction(TransactionType::DEPOSIT, 100, 1100);
    
    std::string timestamp = transaction.getTimestamp();
    EXPECT_FALSE(timestamp.empty());
    EXPECT_GT(timestamp.length(), 0);
} 