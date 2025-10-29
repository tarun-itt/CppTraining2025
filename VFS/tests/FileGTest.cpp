#include <gtest/gtest.h>
#include <memory>

#include "File.h"

class GivenTestingFile : public ::testing::Test {
protected:
    void SetUp() override {
        emptyFile = std::make_shared<File>("empty.txt");
        contentFile = std::make_shared<File>("content.txt", "Hello World");
    }

    std::shared_ptr<File> emptyFile;
    std::shared_ptr<File> contentFile;
};

TEST_F(GivenTestingFile, WhenFileIsEmpty_ThenSizeIsZero) {
    EXPECT_EQ(emptyFile->getSize(), 0);
}

TEST_F(GivenTestingFile, WhenFileHasContent_ThenSizeIsCorrect) {
    EXPECT_EQ(contentFile->getSize(), 11);
}

TEST_F(GivenTestingFile, WhenGetContent_ThenReturnsCorrectContent) {
    EXPECT_EQ(contentFile->getContent(), "Hello World");
    EXPECT_EQ(emptyFile->getContent(), "");
}

TEST_F(GivenTestingFile, WhenSetContent_ThenContentIsUpdated) {
    emptyFile->setContent("New Content");
    
    EXPECT_EQ(emptyFile->getContent(), "New Content");
    EXPECT_EQ(emptyFile->getSize(), 11);
}

TEST_F(GivenTestingFile, WhenAppendContent_ThenContentIsAdded) {
    contentFile->appendContent(" More Text");
    
    EXPECT_EQ(contentFile->getContent(), "Hello World More Text");
    EXPECT_EQ(contentFile->getSize(), 21);
}

TEST_F(GivenTestingFile, WhenFileCloned_ThenCreatesIndependentCopy) {
    auto cloned = contentFile->clone();
    auto clonedFile = std::dynamic_pointer_cast<File>(cloned);
    
    ASSERT_NE(clonedFile, nullptr);
    EXPECT_EQ(clonedFile->getName(), "content.txt");
    EXPECT_EQ(clonedFile->getContent(), "Hello World");
    
    contentFile->setContent("Modified");
    
    EXPECT_EQ(clonedFile->getContent(), "Hello World");
}

TEST_F(GivenTestingFile, WhenSearchLines_ThenFindsMatchingLines) {
    auto multiLineFile = std::make_shared<File>("test.txt", "Line 1: Hello\nLine 2: World\nLine 3: Hello Again");
    
    auto results = multiLineFile->searchLines("Hello");
    
    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], "Line 1: Hello");
    EXPECT_EQ(results[1], "Line 3: Hello Again");
}

TEST_F(GivenTestingFile, WhenSearchLinesNoMatch_ThenReturnsEmpty) {
    auto results = contentFile->searchLines("NotFound");
    
    EXPECT_TRUE(results.empty());
}

TEST_F(GivenTestingFile, WhenFindByContent_ThenFindsMatchingFile) {
    auto results = contentFile->findByContent("World");
    
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0]->getName(), "content.txt");
}

TEST_F(GivenTestingFile, WhenFindByContentNoMatch_ThenReturnsEmpty) {
    auto results = contentFile->findByContent("NotFound");
    
    EXPECT_TRUE(results.empty());
}

TEST_F(GivenTestingFile, WhenFileCreated_ThenIsFile) {
    EXPECT_TRUE(contentFile->isFile());
    EXPECT_FALSE(contentFile->isDirectory());
}
