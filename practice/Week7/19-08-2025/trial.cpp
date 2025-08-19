#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Simple test
TEST(BasicTest, TruthTest) {
    EXPECT_TRUE(true);
    EXPECT_EQ(1, 1);
}

// Mock example
class MockClass {
public:
    MOCK_METHOD(int, getValue, (), (const));
};

TEST(MockTest, BasicMockTest) {
    MockClass mock;
    EXPECT_CALL(mock, getValue())
        .WillOnce(::testing::Return(42));
    
    EXPECT_EQ(42, mock.getValue());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}