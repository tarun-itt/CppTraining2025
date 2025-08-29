#include <gtest/gtest.h>

#include "entities/UserRegistry.h"
#include "mocks/MockUser.h"

class GivenTestingUserRegistry : public ::testing::Test {
protected:
    UserRegistry* registry;
    MockUser* user;

    const std::string TEST_EMAIL = "test@example.com";
    const std::string TEST_PASSWORD = "password123";
    const uint32_t TEST_USER_ID = 12345;
    const size_t REGISTRY_CAPACITY = 5;
    
    void SetUp() override {
        registry = new UserRegistry(REGISTRY_CAPACITY);
        user = new MockUser();
    }
    
    void TearDown() override {
        delete registry;
    }
};

TEST_F(GivenTestingUserRegistry, whenUserIsAdded_thenRegistrySizeIncreases) {
    registry->add(user);
    
    EXPECT_EQ(registry->getSize(), 1);
    EXPECT_EQ((*registry)[0], user);
}

TEST_F(GivenTestingUserRegistry, whenUserIsRemoved_thenRegistrySizeDecreases) {
   
    registry->add(user);
    
    bool removed = registry->remove(TEST_EMAIL);
    
    EXPECT_TRUE(removed);
    EXPECT_EQ(registry->getSize(), 0);
} 