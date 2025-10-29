#include <gtest/gtest.h>
#include <memory>

#include "Directory.h"
#include "File.h"

class GivenTestingDirectory : public ::testing::Test {
  protected:
    void SetUp() override {
        dir = std::make_shared<Directory>("testdir");
        file1 = std::make_shared<File>("file1.txt", "Content 1");
        file2 = std::make_shared<File>("file2.txt", "Content 2");
        subDir = std::make_shared<Directory>("subdir");
    }

    std::shared_ptr<Directory> dir;
    std::shared_ptr<File> file1;
    std::shared_ptr<File> file2;
    std::shared_ptr<Directory> subDir;
};

TEST_F(GivenTestingDirectory, WhenDirectoryEmpty_ThenSizeIsZero) {
    EXPECT_EQ(dir->getSize(), 0);
}

TEST_F(GivenTestingDirectory, WhenChildAdded_ThenSizeIncreases) {
    dir->addChild(file1);

    EXPECT_EQ(dir->getSize(), file1->getSize());
}

TEST_F(GivenTestingDirectory, WhenMultipleChildrenAdded_ThenSizeIsTotal) {
    dir->addChild(file1);
    dir->addChild(file2);

    EXPECT_EQ(dir->getSize(), file1->getSize() + file2->getSize());
}

TEST_F(GivenTestingDirectory, WhenGetChild_ThenReturnsCorrectChild) {
    dir->addChild(file1);

    auto child = dir->getChild("file1.txt");

    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->getName(), "file1.txt");
}

TEST_F(GivenTestingDirectory, WhenGetChildNonExistent_ThenReturnsNull) {
    auto child = dir->getChild("nonexistent.txt");

    EXPECT_EQ(child, nullptr);
}

TEST_F(GivenTestingDirectory, WhenHasChildExists_ThenReturnsTrue) {
    dir->addChild(file1);

    EXPECT_TRUE(dir->hasChild("file1.txt"));
}

TEST_F(GivenTestingDirectory, WhenHasChildNonExistent_ThenReturnsFalse) {
    EXPECT_FALSE(dir->hasChild("nonexistent.txt"));
}

TEST_F(GivenTestingDirectory, WhenGetChildren_ThenReturnsAllChildren) {
    dir->addChild(file1);
    dir->addChild(file2);
    dir->addChild(std::static_pointer_cast<FileSystemObject>(subDir));

    const auto &children = dir->getChildren();

    EXPECT_EQ(children.size(), 3);
}

TEST_F(GivenTestingDirectory, WhenRemoveChild_ThenChildIsRemoved) {
    dir->addChild(file1);
    dir->addChild(file2);

    EXPECT_TRUE(dir->removeChild("file1.txt"));
    EXPECT_FALSE(dir->hasChild("file1.txt"));
    EXPECT_TRUE(dir->hasChild("file2.txt"));
    EXPECT_EQ(dir->getChildren().size(), 1);
}

TEST_F(GivenTestingDirectory, WhenRemoveNonExistent_ThenReturnsFalse) {
    EXPECT_FALSE(dir->removeChild("nonexistent.txt"));
}

TEST_F(GivenTestingDirectory, WhenDuplicateChildAdded_ThenIsIgnored) {
    dir->addChild(file1);

    auto duplicate = std::make_shared<File>("file1.txt", "Different content");
    dir->addChild(duplicate);

    EXPECT_EQ(dir->getChildren().size(), 1);

    auto child = std::dynamic_pointer_cast<File>(dir->getChild("file1.txt"));
    EXPECT_EQ(child->getContent(), "Content 1");
}

TEST_F(GivenTestingDirectory, WhenFindByName_ThenFindsInSingleLevel) {
    dir->addChild(file1);
    dir->addChild(file2);

    auto results = dir->findByName("file1.txt");

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0]->getName(), "file1.txt");
}

TEST_F(GivenTestingDirectory, WhenFindByNameRecursive_ThenFindsInNestedDirectory) {
    auto deepFile = std::make_shared<File>("target.txt", "Found me");
    subDir->addChild(deepFile);
    dir->addChild(file1);
    dir->addChild(std::static_pointer_cast<FileSystemObject>(subDir));

    auto results = dir->findByName("target.txt");

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0]->getName(), "target.txt");
}

TEST_F(GivenTestingDirectory, WhenFindBySize_ThenFindsMatchingFiles) {
    auto smallFile = std::make_shared<File>("small.txt", "Hi");
    auto largeFile = std::make_shared<File>("large.txt", "This is a much larger file content");

    dir->addChild(smallFile);
    dir->addChild(file1);
    dir->addChild(largeFile);

    auto results = dir->findBySize(5, 15);

    EXPECT_GE(results.size(), 1);
    bool foundFile1 = false;
    for (const auto &result : results) {
        if (result->getName() == "file1.txt") {
            foundFile1 = true;
        }
    }
    EXPECT_TRUE(foundFile1);
}

TEST_F(GivenTestingDirectory, WhenFindByTimestamp_ThenFindsRecentFiles) {
    time_t now = std::time(nullptr);
    time_t start = now - 60;
    time_t end = now + 60;

    dir->addChild(file1);
    dir->addChild(file2);

    auto results = dir->findByTimestamp(start, end);

    EXPECT_EQ(results.size(), 2);
}

TEST_F(GivenTestingDirectory, WhenNestedDirectoryHasFiles_ThenSizeIsCalculatedCorrectly) {
    subDir->addChild(file1);
    dir->addChild(file2);
    dir->addChild(std::static_pointer_cast<FileSystemObject>(subDir));

    size_t expectedSize = file1->getSize() + file2->getSize();
    EXPECT_EQ(dir->getSize(), expectedSize);
}

TEST_F(GivenTestingDirectory, WhenDirectoryCreated_ThenIsDirectory) {
    EXPECT_TRUE(dir->isDirectory());
    EXPECT_FALSE(dir->isFile());
}
