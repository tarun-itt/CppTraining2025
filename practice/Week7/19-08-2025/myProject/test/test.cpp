// test/test_math.cpp
#include <gtest/gtest.h>
#include "mathUtils.h"

TEST(MathTest, AddTest) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
}

TEST(MathTest, MultiplyTest) {
    EXPECT_EQ(mult(3, 4), 12);
    EXPECT_EQ(mult(-2, 3), -6);
    EXPECT_EQ(mult(0, 100), 0);
}

TEST(MathTest, IsPrimeTest) {
    EXPECT_FALSE(isPrime(1));
    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}