#include <gtest/gtest.h>
#include "../inc/entities/TransactionLedger.hpp"
#include "../inc/entities/Transaction.hpp"

class TransactionLedgerTest : public ::testing::Test {
protected:
    Transaction* transaction1;
    Transaction* transaction2;  
    void SetUp() override {
        transaction1 = new Transaction(TransactionType::DEPOSIT, 100, 1100);
        transaction2 = new Transaction(TransactionType::WITHDRAW, 50, 1050);
    }

    void TearDown() override {
        delete transaction1;
        delete transaction2;
    }
};

TEST_F(TransactionLedgerTest, AddTransaction) {
    TransactionLedger ledger;
    
    EXPECT_EQ(ledger.getSize(), 0);

    ledger.add(transaction1);
    EXPECT_EQ(ledger.getSize(), 1);
    EXPECT_EQ(ledger[0]->getType(), transaction1->getType());
    EXPECT_EQ(ledger[0]->getAmount(), transaction1->getAmount());
}

TEST_F(TransactionLedgerTest, GetSubArray) {
    TransactionLedger ledger;
    ledger.add(transaction1);
    ledger.add(transaction2);
    
    TransactionLedger subArray = ledger.getSubArray(ledger, 0, 1);
    
    EXPECT_EQ(subArray.getSize(), 2);
    EXPECT_EQ(subArray[0]->getType(), transaction1->getType());
    EXPECT_EQ(subArray[1]->getType(), transaction2->getType());
} 