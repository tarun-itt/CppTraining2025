#include <gtest/gtest.h>
#include "entities/TransactionLedger.h"
#include "entities/Transaction.h"

class GivenTestingTransactionLedger : public ::testing::Test {
protected:
    Transaction* firstTransaction;
    Transaction* secondTransaction;
    
    const double DEPOSIT_AMOUNT = 100;
    const double WITHDRAW_AMOUNT = 50;
    const double BALANCE_AFTER_DEPOSIT = 1100;
    const double BALANCE_AFTER_WITHDRAW = 1050;
    
    void SetUp() override {
        firstTransaction = new Transaction(TransactionType::DEPOSIT, DEPOSIT_AMOUNT, BALANCE_AFTER_DEPOSIT);
        secondTransaction = new Transaction(TransactionType::WITHDRAW, WITHDRAW_AMOUNT, BALANCE_AFTER_WITHDRAW);
    }

    void TearDown() override {
        delete firstTransaction;
        delete secondTransaction;
    }
};

TEST_F(GivenTestingTransactionLedger, whenTransactionIsAdded_thenLedgerSizeIncreases) {
    TransactionLedger ledger;
    
    EXPECT_EQ(ledger.getSize(), 0);
    ledger.add(firstTransaction);

    EXPECT_EQ(ledger.getSize(), 1);
    EXPECT_EQ(ledger[0]->getType(), firstTransaction->getType());
    EXPECT_EQ(ledger[0]->getAmount(), firstTransaction->getAmount());
}

TEST_F(GivenTestingTransactionLedger, whenGetSubArrayIsCalled_thenSubArrayIsReturned) {
    TransactionLedger ledger;
    ledger.add(firstTransaction);
    ledger.add(secondTransaction);
    
    TransactionLedger subArray = ledger.getSubArray(ledger, 0, 1);
    
    EXPECT_EQ(subArray.getSize(), 1);
    EXPECT_EQ(subArray[0]->getType(), firstTransaction->getType());
    EXPECT_EQ(subArray[1]->getType(), secondTransaction->getType());
} 