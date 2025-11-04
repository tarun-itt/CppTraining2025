#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <chrono>
#include "Directory.h"
#include "File.h"

class GivenTestingDirectory : public ::testing::Test {
protected:
    void SetUp() override {
        directory = std::make_shared<Directory>("testdir");
    }

    std::shared_ptr<Directory> directory;
};

TEST_F(GivenTestingDirectory, WhenCreatedWithName_ThenNameIsSet) {
    EXPECT_EQ(directory->getName(), "testdir");
    EXPECT_TRUE(directory->isDirectory());
}

TEST_F(GivenTestingDirectory, WhenGetComponentType_ThenReturnsDirectory) {
    EXPECT_EQ(directory->getComponentType(), FileSystemComponentType::Directory);
}

TEST_F(GivenTestingDirectory, WhenChildDirectoryAdded_ThenHasChild) {
    auto child = std::make_shared<Directory>("subdir");
    directory->addChild(child);
    EXPECT_TRUE(directory->hasChild("subdir"));
}

TEST_F(GivenTestingDirectory, WhenChildFileAdded_ThenHasChild) {
    auto file = std::make_shared<File>("test.txt");
    directory->addChild(file);
    EXPECT_TRUE(directory->hasChild("test.txt"));
}

TEST_F(GivenTestingDirectory, WhenGetExistingChild_ThenReturnsChild) {
    auto child = std::make_shared<Directory>("subdir");
    directory->addChild(child);
    auto retrieved = directory->getChild("subdir");
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getName(), "subdir");
}

TEST_F(GivenTestingDirectory, WhenGetNonExistingChild_ThenReturnsNull) {
    auto retrieved = directory->getChild("nonexistent");
    EXPECT_EQ(retrieved, nullptr);
}

TEST_F(GivenTestingDirectory, WhenChildRemoved_ThenNoLongerHasChild) {
    auto child = std::make_shared<Directory>("subdir");
    directory->addChild(child);
    EXPECT_TRUE(directory->removeChild("subdir"));
    EXPECT_FALSE(directory->hasChild("subdir"));
}

TEST_F(GivenTestingDirectory, WhenRemoveNonExistingChild_ThenReturnsFalse) {
    EXPECT_FALSE(directory->removeChild("nonexistent"));
}

TEST_F(GivenTestingDirectory, WhenChildrenAdded_ThenListReturnsAll) {
    directory->addChild(std::make_shared<Directory>("dir1"));
    directory->addChild(std::make_shared<File>("file1.txt"));
    directory->addChild(std::make_shared<Directory>("dir2"));
    
    auto& children = directory->getChildren();
    EXPECT_EQ(children.size(), 3);
}

TEST_F(GivenTestingDirectory, WhenEmpty_ThenChildrenListIsEmpty) {
    auto& children = directory->getChildren();
    EXPECT_TRUE(children.empty());
}

TEST_F(GivenTestingDirectory, WhenFindByName_ThenReturnsMatches) {
    auto file1 = std::make_shared<File>("test.txt");
    auto file2 = std::make_shared<File>("other.txt");
    auto subdir = std::make_shared<Directory>("subdir");
    auto file3 = std::make_shared<File>("test.txt");
    
    directory->addChild(file1);
    directory->addChild(file2);
    directory->addChild(subdir);
    subdir->addChild(file3);
    
    auto results = directory->findByName("test.txt");
    EXPECT_EQ(results.size(), 2);
}

TEST_F(GivenTestingDirectory, WhenEmptyDirectory_ThenSizeIsZero) {
    EXPECT_EQ(directory->getSize(), 0);
}

TEST_F(GivenTestingDirectory, WhenFilesAdded_ThenSizeIsCorrect) {
    auto file1 = std::make_shared<File>("file1.txt", "Hello");
    auto file2 = std::make_shared<File>("file2.txt", "World");
    directory->addChild(file1);
    directory->addChild(file2);
    EXPECT_EQ(directory->getSize(), 10);
}

TEST_F(GivenTestingDirectory, WhenModificationTimeUpdated_ThenTimeIncreases) {
    std::time_t before = directory->getModificationTime();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    directory->updateModificationTime();
    std::time_t after = directory->getModificationTime();
    EXPECT_GT(after, before);
}

TEST_F(GivenTestingDirectory, WhenFindBySize_ThenReturnsMatchingFiles) {
    auto file1 = std::make_shared<File>("file1.txt", "Short");
    auto file2 = std::make_shared<File>("file2.txt", "This is a longer content");
    directory->addChild(file1);
    directory->addChild(file2);
    
    auto results = directory->findBySize(10, 100);
    EXPECT_EQ(results.size(), 1);
}

TEST_F(GivenTestingDirectory, WhenNestedFindByName_ThenReturnsAllMatches) {
    auto subdir1 = std::make_shared<Directory>("subdir1");
    auto subdir2 = std::make_shared<Directory>("subdir2");
    auto file1 = std::make_shared<File>("target.txt");
    auto file2 = std::make_shared<File>("target.txt");
    
    directory->addChild(subdir1);
    directory->addChild(subdir2);
    subdir1->addChild(file1);
    subdir2->addChild(file2);
    
    auto results = directory->findByName("target.txt");
    EXPECT_EQ(results.size(), 2);
}