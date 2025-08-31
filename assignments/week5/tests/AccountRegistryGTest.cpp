#include <gtest/gtest.h>

#include "entities/AccountRegistry.h"
#include "entities/Account.h"

class GivenTestingAccountRegistry : public ::testing::Test {
protected:
    AccountRegistry* registry;

    const uint32_t TEST_ACCOUNT_NUMBER = 11111;
    const uint32_t TEST_ACCOUNT_HOLDER_ID = 12345;
    const double TEST_INITIAL_DEPOSIT = 1000;
    const size_t REGISTRY_CAPACITY = 5;
    
    void SetUp() override {
        registry = new AccountRegistry(REGISTRY_CAPACITY);
    }
    
    void TearDown() override {
        delete registry;
    }
};

TEST_F(GivenTestingAccountRegistry, whenAccountIsAdded_thenRegistrySizeIncreases) {
    Account* account = new Account(TEST_ACCOUNT_NUMBER, TEST_ACCOUNT_HOLDER_ID, TEST_INITIAL_DEPOSIT);
    registry->add(account);
    
    EXPECT_EQ(registry->getSize(), 1);
    EXPECT_EQ(registry->getAccount(TEST_ACCOUNT_NUMBER)->getAccountNumber(), account->getAccountNumber());
}

TEST_F(GivenTestingAccountRegistry, whenAccountIsRemoved_thenRegistrySizeDecreases) {
    Account* account = new Account(TEST_ACCOUNT_NUMBER, TEST_ACCOUNT_HOLDER_ID, TEST_INITIAL_DEPOSIT);
    registry->add(account);
    
    bool removed = registry->remove(TEST_ACCOUNT_NUMBER);
    
    EXPECT_TRUE(removed);
    EXPECT_EQ(registry->getSize(), 0);
} 