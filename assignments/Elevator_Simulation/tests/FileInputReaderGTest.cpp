#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "../inc/FileInputReader.h"
#include "mocks/MockBlockingQueue.h"
#include "../inc/ElevatorSystemConfig.h"

using ::testing::_;

class GivenTestingFileInputReader : public ::testing::Test {
protected:
    MockBlockingQueue<InputRequest>* mockQueue;
    FileInputReader* reader;
    const std::string testFilePath = "test_requests.txt";

    void SetUp() override {
        mockQueue = new MockBlockingQueue<InputRequest>();
        ElevatorSystemConfig config;
        reader = new FileInputReader(testFilePath, mockQueue, config);
    }

    void TearDown() override {
        delete reader;
        delete mockQueue;
        std::remove(testFilePath.c_str());
    }

    void writeToFile(const std::string& content) {
        std::ofstream file(testFilePath, std::ios::app);
        if (file.is_open()) {
            file << content << std::endl;
        }
    }
};

TEST_F(GivenTestingFileInputReader, WhenValidLineIsAddedToFileThenRequestIsPushedToQueue) {
    EXPECT_CALL(*mockQueue, push(_)).Times(1);
    
    reader->start();
    writeToFile("f1 f5");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    reader->stop();
}

TEST_F(GivenTestingFileInputReader, WhenInvalidLineIsAddedToFileThenRequestIsNotPushed) {
    EXPECT_CALL(*mockQueue, push(_)).Times(0);

    reader->start();
    writeToFile("invalid line");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    reader->stop();
}

TEST_F(GivenTestingFileInputReader, WhenExitLineIsAddedToFileThenShutdownRequestIsPushed) {
    EXPECT_CALL(*mockQueue, push(_)).WillOnce([](const InputRequest& req) {
        EXPECT_TRUE(req.isShutdown());
    });

    reader->start();
    writeToFile("exit");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    reader->stop();
}