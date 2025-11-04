#include <gtest/gtest.h>
#include <memory>
#include "File.h"

class GivenTestingFile : public ::testing::Test {
protected:
    void SetUp() override {
        file = std::make_shared<File>("test.txt");
    }

    std::shared_ptr<File> file;
};

TEST_F(GivenTestingFile, WhenCreatedWithName_ThenNameIsSet) {
    EXPECT_EQ(file->getName(), "test.txt");
    EXPECT_TRUE(file->isFile());
}

TEST_F(GivenTestingFile, WhenGetComponentType_ThenReturnsFile) {
    EXPECT_EQ(file->getComponentType(), FileSystemComponentType::File);
}

TEST_F(GivenTestingFile, WhenCreated_ThenContentIsEmpty) {
    EXPECT_EQ(file->getContent(), "");
}

TEST_F(GivenTestingFile, WhenContentSet_ThenContentIsStored) {
    file->setContent("Hello World");
    EXPECT_EQ(file->getContent(), "Hello World");
}

TEST_F(GivenTestingFile, WhenContentAppended_ThenContentIsAdded) {
    file->setContent("Line 1\n");
    file->appendContent("Line 2\n");
    EXPECT_EQ(file->getContent(), "Line 1\nLine 2\n");
}

TEST_F(GivenTestingFile, WhenFindByContent_ThenFindsMatch) {
    file->setContent("Hello World");
    auto results = file->findByContent("World");
    EXPECT_EQ(results.size(), 1);
}

TEST_F(GivenTestingFile, WhenFindByContent_ThenNoMatch) {
    file->setContent("Hello World");
    auto results = file->findByContent("Goodbye");
    EXPECT_TRUE(results.empty());
}

TEST_F(GivenTestingFile, WhenFindByContentCaseInsensitive_ThenFindsMatch) {
    file->setContent("Hello World");
    auto results = file->findByContent("world");
    EXPECT_EQ(results.size(), 1);
}

TEST_F(GivenTestingFile, WhenMultilineContentSet_ThenContentIsPreserved) {
    std::string multiline = "Line 1\nLine 2\nLine 3";
    file->setContent(multiline);
    EXPECT_EQ(file->getContent(), multiline);
}

TEST_F(GivenTestingFile, WhenContentOverwritten_ThenOldContentIsReplaced) {
    file->setContent("Original");
    file->setContent("Updated");
    EXPECT_EQ(file->getContent(), "Updated");
}

TEST_F(GivenTestingFile, WhenAppendToEmptyFile_ThenContentIsAdded) {
    file->appendContent("First line");
    EXPECT_EQ(file->getContent(), "First line");
}

TEST_F(GivenTestingFile, WhenMultipleAppends_ThenAllContentIsAdded) {
    file->setContent("Line 1\n");
    file->appendContent("Line 2\n");
    file->appendContent("Line 3\n");
    EXPECT_EQ(file->getContent(), "Line 1\nLine 2\nLine 3\n");
}

TEST_F(GivenTestingFile, WhenGetSize_ThenReturnsContentLength) {
    file->setContent("Hello");
    EXPECT_EQ(file->getSize(), 5);
}

TEST_F(GivenTestingFile, WhenFileCreatedWithContent_ThenContentAndSizeAreCorrect) {
    auto newFile = std::make_shared<File>("data.txt", "Initial content");
    EXPECT_EQ(newFile->getContent(), "Initial content");
    EXPECT_EQ(newFile->getSize(), 15);
}
