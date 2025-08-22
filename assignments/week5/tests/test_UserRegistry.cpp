#include <gtest/gtest.h>
#include "../inc/entities/UserRegistry.hpp"
#include "../inc/entities/User.hpp"

class UserRegistryTest : public ::testing::Test {
protected:
    UserRegistry* registry;

    class TestUser : public User {
    public:
        TestUser(const std::string& email, const std::string& password, uint32_t userId): User(email, password, userId) {}
        
        uint32_t getUserId() const override { return userId; }
        double requestBalance(const LoginResult&, uint32_t) override { return 0.0; }
        TransactionLedger requestMiniStatement(const LoginResult&, uint32_t) override { return TransactionLedger(); }
        TransactionLedger requestStatementInDateRange(const LoginResult&, uint32_t, std::string, std::string) override { return TransactionLedger(); }
    };
    
    void SetUp() override {
        registry = new UserRegistry(5);
    }
    
    void TearDown() override {
        delete registry;
    }
};

TEST_F(UserRegistryTest, AddUser) {
    TestUser* user = new TestUser("test@example.com", "password123", 12345);
    registry->add(user);
    
    EXPECT_EQ(registry->getSize(), 1);
    EXPECT_EQ((*registry)[0], user);
}

TEST_F(UserRegistryTest, RemoveUser) {
    TestUser* user = new TestUser("test@example.com", "password123", 12345);
    registry->add(user);
    
    bool removed = registry->remove("test@example.com");
    
    EXPECT_TRUE(removed);
    EXPECT_EQ(registry->getSize(), 0);
} 