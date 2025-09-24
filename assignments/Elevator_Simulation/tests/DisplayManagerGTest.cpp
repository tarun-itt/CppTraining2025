#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../inc/DisplayManager.h"
#include "../inc/Display/IPrintable.h"
#include "mocks/MockBlockingQueue.h"

using ::testing::_;

class GivenDisplayManager : public ::testing::Test {
protected:
    MockBlockingQueue<RenderRequest>* mockQueue;

    void SetUp() override {
        mockQueue = new MockBlockingQueue<RenderRequest>();
        DisplayManager::initialize(mockQueue);
    }

    void TearDown() override {
        DisplayManager::shutdown();
        delete mockQueue;
    }
};

TEST_F(GivenDisplayManager, WhenDisplayCalled_ThenPushesDisplayRequestToQueue) {
    EXPECT_CALL(*mockQueue, push(_)).WillOnce([](const RenderRequest& req) {
        EXPECT_EQ(req.operationType, RenderOperation::Display);
        EXPECT_EQ(req.printableId, "test_id");
    });

    Printable* dummyPrintable = nullptr; 
    DisplayManager::display(dummyPrintable, "test_id");
}

TEST_F(GivenDisplayManager, WhenRemoveCalled_ThenPushesRemoveRequestToQueue) {
    EXPECT_CALL(*mockQueue, push(_)).WillOnce([](const RenderRequest& req) {
        EXPECT_EQ(req.operationType, RenderOperation::Remove);
        EXPECT_EQ(req.printableId, "test_id");
    });
    
    DisplayManager::remove("test_id");
}

TEST_F(GivenDisplayManager, WhenClearCalled_ThenPushesClearRequestToQueue) {
    EXPECT_CALL(*mockQueue, push(_)).WillOnce([](const RenderRequest& req) {
        EXPECT_EQ(req.operationType, RenderOperation::Clear);
    });
    
    DisplayManager::clear();
}