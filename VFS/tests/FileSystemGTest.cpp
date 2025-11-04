#include <gtest/gtest.h>
#include <memory>

#include "FileSystem.h"
#include "FileSystemPersistence.h"

class GivenTestingFileSystem : public ::testing::Test {
protected:
    void SetUp() override {
        auto persistence = std::make_unique<FileSystemPersistence>("test_vfs_data.txt");
        fileSystem = std::make_unique<FileSystem>(std::move(persistence));
        fileSystem->initialize();
    }

    void TearDown() override {
        std::remove("test_vfs_data.txt");
    }

    std::unique_ptr<FileSystem> fileSystem;
};

TEST_F(GivenTestingFileSystem, WhenInitialized_ThenRootDirectoryExists) {
    EXPECT_EQ(fileSystem->getCurrentPath(), "/");
    EXPECT_NE(fileSystem->getCurrentDirectory(), nullptr);
}

TEST_F(GivenTestingFileSystem, WhenDirectoryCreatedInRoot_ThenExists) {
    EXPECT_TRUE(fileSystem->createDirectory("testdir"));
    EXPECT_TRUE(fileSystem->exists("testdir"));
}

TEST_F(GivenTestingFileSystem, WhenNestedDirectoryCreated_ThenExists) {
    EXPECT_TRUE(fileSystem->createDirectory("dir1"));
    EXPECT_TRUE(fileSystem->createDirectory("dir1/dir2"));
    EXPECT_TRUE(fileSystem->exists("dir1/dir2"));
}

TEST_F(GivenTestingFileSystem, WhenDuplicateDirectoryCreated_ThenFails) {
    EXPECT_TRUE(fileSystem->createDirectory("testdir"));
    EXPECT_FALSE(fileSystem->createDirectory("testdir"));
}

TEST_F(GivenTestingFileSystem, WhenFileCreatedInRoot_ThenExists) {
    EXPECT_TRUE(fileSystem->createFile("test.txt", "Hello World"));
    EXPECT_TRUE(fileSystem->exists("test.txt"));
}

TEST_F(GivenTestingFileSystem, WhenFileCreatedInDirectory_ThenExists) {
    fileSystem->createDirectory("docs");
    EXPECT_TRUE(fileSystem->createFile("docs/readme.txt", "Content"));
    EXPECT_TRUE(fileSystem->exists("docs/readme.txt"));
}

TEST_F(GivenTestingFileSystem, WhenFileRead_ThenContentReturned) {
    fileSystem->createFile("test.txt", "Hello World");
    std::string content = fileSystem->readFile("test.txt");
    EXPECT_EQ(content, "Hello World");
}

TEST_F(GivenTestingFileSystem, WhenFileWritten_ThenContentUpdated) {
    fileSystem->createFile("test.txt", "Original");
    EXPECT_TRUE(fileSystem->writeFile("test.txt", "Updated"));
    EXPECT_EQ(fileSystem->readFile("test.txt"), "Updated");
}

TEST_F(GivenTestingFileSystem, WhenContentAppendedToFile_ThenContentAdded) {
    fileSystem->createFile("test.txt", "Line1\n");
    EXPECT_TRUE(fileSystem->appendToFile("test.txt", "Line2\n"));
    EXPECT_EQ(fileSystem->readFile("test.txt"), "Line1\nLine2\n");
}

TEST_F(GivenTestingFileSystem, WhenChangeDirectoryWithAbsolutePath_ThenCurrentPathUpdated) {
    fileSystem->createDirectory("dir1");
    fileSystem->createDirectory("dir1/dir2");
    EXPECT_TRUE(fileSystem->changeDir("/dir1/dir2"));
    EXPECT_EQ(fileSystem->getCurrentPath(), "/dir1/dir2");
}

TEST_F(GivenTestingFileSystem, WhenChangeDirectoryWithRelativePath_ThenCurrentPathUpdated) {
    fileSystem->createDirectory("dir1");
    fileSystem->changeDir("dir1");
    EXPECT_EQ(fileSystem->getCurrentPath(), "/dir1");
}

TEST_F(GivenTestingFileSystem, WhenChangeDirectoryToParent_ThenNavigatesUp) {
    fileSystem->createDirectory("dir1");
    fileSystem->createDirectory("dir1/dir2");
    fileSystem->changeDir("/dir1/dir2");
    EXPECT_TRUE(fileSystem->changeDir(".."));
    EXPECT_EQ(fileSystem->getCurrentPath(), "/dir1");
}

TEST_F(GivenTestingFileSystem, WhenChangeDirectoryToParentFromRoot_ThenStaysAtRoot) {
    EXPECT_TRUE(fileSystem->changeDir(".."));
    EXPECT_EQ(fileSystem->getCurrentPath(), "/");
}

TEST_F(GivenTestingFileSystem, WhenChangeDirectoryWithRelativeParentPath_ThenNavigatesCorrectly) {
    fileSystem->createDirectory("dir1");
    fileSystem->createDirectory("dir2");
    fileSystem->changeDir("dir1");
    EXPECT_TRUE(fileSystem->changeDir("../dir2"));
    EXPECT_EQ(fileSystem->getCurrentPath(), "/dir2");
}

TEST_F(GivenTestingFileSystem, WhenListCurrentDirectory_ThenAllChildrenReturned) {
    fileSystem->createDirectory("dir1");
    fileSystem->createFile("file1.txt", "content");
    auto items = fileSystem->listCurrentDirectory();
    EXPECT_EQ(items.size(), 2);
}

TEST_F(GivenTestingFileSystem, WhenFileRemoved_ThenNoLongerExists) {
    fileSystem->createFile("test.txt", "content");
    EXPECT_TRUE(fileSystem->removeFile("test.txt"));
    EXPECT_FALSE(fileSystem->exists("test.txt"));
}

TEST_F(GivenTestingFileSystem, WhenEmptyDirectoryRemoved_ThenNoLongerExists) {
    fileSystem->createDirectory("dir1");
    EXPECT_TRUE(fileSystem->removeDir("dir1"));
    EXPECT_FALSE(fileSystem->exists("dir1"));
}

TEST_F(GivenTestingFileSystem, WhenMultilineFileCreated_ThenContentPreserved) {
    std::string multiline = "Line 1\nLine 2\nLine 3";
    fileSystem->createFile("multi.txt", multiline);
    EXPECT_EQ(fileSystem->readFile("multi.txt"), multiline);
}

TEST_F(GivenTestingFileSystem, WhenGetObjectForFile_ThenCorrectFileReturned) {
    fileSystem->createFile("test.txt", "data");
    auto obj = fileSystem->getFileSystemComponent("test.txt");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "test.txt");
    EXPECT_TRUE(obj->isFile());
}

TEST_F(GivenTestingFileSystem, WhenGetObjectForDirectory_ThenCorrectDirectoryReturned) {
    fileSystem->createDirectory("testdir");
    auto obj = fileSystem->getFileSystemComponent("testdir");
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "testdir");
    EXPECT_TRUE(obj->isDirectory());
}

TEST_F(GivenTestingFileSystem, WhenGetFile_ThenFilePointerReturned) {
    fileSystem->createFile("test.txt", "content");
    auto file = fileSystem->getFile("test.txt");
    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->getContent(), "content");
}

TEST_F(GivenTestingFileSystem, WhenGetDirectory_ThenDirectoryPointerReturned) {
    fileSystem->createDirectory("testdir");
    auto dir = fileSystem->getDirectory("testdir");
    ASSERT_NE(dir, nullptr);
    EXPECT_EQ(dir->getName(), "testdir");
}
