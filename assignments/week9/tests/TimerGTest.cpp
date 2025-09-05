#include <gtest/gtest.h>
#include <chrono>
#include "../inc/Timer.h"

class GivenTestingTimer : public ::testing::Test {
protected:
    int oneSecondDuration;
    int zeroDuration;
    
    Timer* timer;

    void SetUp() override {
        oneSecondDuration = 1;
        zeroDuration = 0;
        
        timer = new Timer();
    }

    void TearDown() override {
        delete timer;
    }
};

TEST_F(GivenTestingTimer, WhenSleepCalled_ThenThreadPauses) {
    auto startTime = std::chrono::steady_clock::now();
    
    timer->sleep(oneSecondDuration);
    
    auto endTime = std::chrono::steady_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    EXPECT_GE(timeElapsed.count(), oneSecondDuration * 1000);
    EXPECT_LE(timeElapsed.count(), oneSecondDuration * 1000);
}

TEST_F(GivenTestingTimer, WhenSleepCalledWithZero_ThenThreadContinues) {
    auto startTime = std::chrono::steady_clock::now();
    
    timer->sleep(zeroDuration);
    
    auto endTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    EXPECT_LT(elapsed.count(), 100);
}