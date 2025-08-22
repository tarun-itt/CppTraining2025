#include <gtest/gtest.h>
#include "../inc/entities/AccountRegistry.hpp"
#include "../inc/entities/Account.hpp"

class AccountRegistryTest : public ::testing::Test {
protected:
    AccountRegistry* registry;

    class TestAccount : public Account {
    public:
        TestAccount(uint32_t accountNumber, uint32_t accountHolderId, double initialDeposit)
            : Account(accountNumber, accountHolderId, initialDeposit) {}
    };
    
    void SetUp() override {
        registry = new AccountRegistry(5);
    }
    
    void TearDown() override {
        delete registry;
    }
};

TEST_F(AccountRegistryTest, AddAccount) {
    TestAccount* account = new TestAccount(11111, 12345, 1000);
    registry->add(account);
    
    EXPECT_EQ(registry->getSize(), 1);
    EXPECT_EQ((*registry)[0], account);
}

TEST_F(AccountRegistryTest, RemoveAccount) {
    TestAccount* account = new TestAccount(11111, 12345, 1000);
    registry->add(account);
    
    bool removed = registry->remove(11111);
    
    EXPECT_TRUE(removed);
    EXPECT_EQ(registry->getSize(), 0);
} 