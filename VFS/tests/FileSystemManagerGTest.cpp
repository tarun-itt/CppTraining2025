#include <gtest/gtest.h>
#include <memory>

#include "FileSystemManager.h"

class SimpleMockPersistence : public IPersistenceStrategy {
  public:
    void saveFileSystem(const std::shared_ptr<FileSystemObject> &root) override { saveCalled = true; }

    std::shared_ptr<FileSystemObject> loadFileSystem() override { return nullptr; }

    bool exists() const override { return false; }

    bool saveCalled = false;
};

class GivenTestingFileSystemManager : public ::testing::Test {
  protected:
    void SetUp() override {
        std::unique_ptr<IPersistenceStrategy> persistence(new SimpleMockPersistence());
        fsManager.reset(new FileSystemManager(std::move(persistence)));
    }

    std::unique_ptr<FileSystemManager> fsManager;
};

TEST_F(GivenTestingFileSystemManager, WhenInitialized_ThenRootDirectoryExists) {
    EXPECT_EQ(fsManager->getCurrentPath(), "/");
    EXPECT_NE(fsManager->getCurrentDirectory(), nullptr);
}

TEST_F(GivenTestingFileSystemManager, WhenDirectoryCreatedInRoot_ThenExists) {
    EXPECT_TRUE(fsManager->createDirectory("testdir"));
    EXPECT_TRUE(fsManager->exists("testdir"));
}

TEST_F(GivenTestingFileSystemManager, WhenNestedDirectoryCreated_ThenExists) {
    EXPECT_TRUE(fsManager->createDirectory("dir1"));
    EXPECT_TRUE(fsManager->createDirectory("dir1/dir2"));
    EXPECT_TRUE(fsManager->exists("dir1/dir2"));
}

TEST_F(GivenTestingFileSystemManager, WhenDuplicateDirectoryCreated_ThenFails) {
    EXPECT_TRUE(fsManager->createDirectory("testdir"));
    EXPECT_FALSE(fsManager->createDirectory("testdir"));
}

TEST_F(GivenTestingFileSystemManager, WhenFileCreatedInRoot_ThenExists) {
    EXPECT_TRUE(fsManager->createFile("test.txt", "Hello"));
    EXPECT_TRUE(fsManager->exists("test.txt"));
}

TEST_F(GivenTestingFileSystemManager, WhenFileCreatedWithContent_ThenContentIsStored) {
    EXPECT_TRUE(fsManager->createFile("file.txt", "Test Content"));

    std::string content = fsManager->readFile("file.txt");
    EXPECT_EQ(content, "Test Content");
}

TEST_F(GivenTestingFileSystemManager, WhenDuplicateFileCreated_ThenFails) {
    EXPECT_TRUE(fsManager->createFile("test.txt"));
    EXPECT_FALSE(fsManager->createFile("test.txt"));
}

TEST_F(GivenTestingFileSystemManager, WhenFileRead_ThenReturnsContent) {
    fsManager->createFile("data.txt", "File Data");

    EXPECT_EQ(fsManager->readFile("data.txt"), "File Data");
}

TEST_F(GivenTestingFileSystemManager, WhenNonExistentFileRead_ThenReturnsEmpty) {
    EXPECT_EQ(fsManager->readFile("nonexistent.txt"), "");
}

TEST_F(GivenTestingFileSystemManager, WhenFileWritten_ThenContentIsUpdated) {
    fsManager->createFile("file.txt", "Original");

    EXPECT_TRUE(fsManager->writeFile("file.txt", "Updated"));
    EXPECT_EQ(fsManager->readFile("file.txt"), "Updated");
}

TEST_F(GivenTestingFileSystemManager, WhenContentAppended_ThenIsAddedToFile) {
    fsManager->createFile("log.txt", "Line 1\n");

    EXPECT_TRUE(fsManager->appendToFile("log.txt", "Line 2\n"));
    EXPECT_EQ(fsManager->readFile("log.txt"), "Line 1\nLine 2\n");
}

TEST_F(GivenTestingFileSystemManager, WhenFileRemoved_ThenNoLongerExists) {
    fsManager->createFile("temp.txt");

    EXPECT_TRUE(fsManager->remove("temp.txt"));
    EXPECT_FALSE(fsManager->exists("temp.txt"));
}

TEST_F(GivenTestingFileSystemManager, WhenEmptyDirectoryRemoved_ThenNoLongerExists) {
    fsManager->createDirectory("emptydir");

    EXPECT_TRUE(fsManager->remove("emptydir"));
    EXPECT_FALSE(fsManager->exists("emptydir"));
}

TEST_F(GivenTestingFileSystemManager, WhenNonExistentRemoved_ThenFails) {
    EXPECT_FALSE(fsManager->remove("nonexistent"));
}

TEST_F(GivenTestingFileSystemManager, WhenChangeDirectoryToExisting_ThenCurrentPathUpdates) {
    fsManager->createDirectory("subdir");

    EXPECT_TRUE(fsManager->changeDirectory("subdir"));
    EXPECT_EQ(fsManager->getCurrentPath(), "/subdir");
}

TEST_F(GivenTestingFileSystemManager, WhenChangeDirectoryToParent_ThenNavigatesUp) {
    fsManager->createDirectory("dir1");
    fsManager->changeDirectory("dir1");

    EXPECT_TRUE(fsManager->changeDirectory(".."));
    EXPECT_EQ(fsManager->getCurrentPath(), "/");
}

TEST_F(GivenTestingFileSystemManager, WhenChangeDirectoryToNonExistent_ThenFails) {
    EXPECT_FALSE(fsManager->changeDirectory("nonexistent"));
}

TEST_F(GivenTestingFileSystemManager, WhenChangeDirectoryToFile_ThenFails) {
    fsManager->createFile("file.txt");

    EXPECT_FALSE(fsManager->changeDirectory("file.txt"));
}

TEST_F(GivenTestingFileSystemManager, WhenListCurrentDirectory_ThenReturnsAllChildren) {
    fsManager->createFile("file1.txt");
    fsManager->createFile("file2.txt");
    fsManager->createDirectory("dir1");

    auto children = fsManager->listCurrentDirectory();

    EXPECT_EQ(children.size(), 3);
}

TEST_F(GivenTestingFileSystemManager, WhenGetObject_ThenReturnsCorrectObject) {
    fsManager->createFile("test.txt", "data");

    auto obj = fsManager->getObject("test.txt");

    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->getName(), "test.txt");
    EXPECT_TRUE(obj->isFile());
}

TEST_F(GivenTestingFileSystemManager, WhenGetFile_ThenReturnsFileObject) {
    fsManager->createFile("doc.txt", "document");

    auto file = fsManager->getFile("doc.txt");

    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->getContent(), "document");
}

TEST_F(GivenTestingFileSystemManager, WhenGetDirectory_ThenReturnsDirectoryObject) {
    fsManager->createDirectory("folder");

    auto dir = fsManager->getDirectory("folder");

    ASSERT_NE(dir, nullptr);
    EXPECT_TRUE(dir->isDirectory());
}

TEST_F(GivenTestingFileSystemManager, WhenFindByName_ThenFindsAllMatches) {
    fsManager->createFile("target.txt");
    fsManager->createDirectory("dir1");
    fsManager->createFile("dir1/target.txt");

    auto results = fsManager->findByName("target.txt");

    EXPECT_EQ(results.size(), 2);
}

TEST_F(GivenTestingFileSystemManager, WhenFindBySize_ThenFindsMatchingObjects) {
    fsManager->createFile("small.txt", "Hi");
    fsManager->createFile("medium.txt", "Hello World");
    fsManager->createFile("large.txt", "This is a very long content string");

    auto results = fsManager->findBySize(5, 15);

    EXPECT_GE(results.size(), 1);
}

TEST_F(GivenTestingFileSystemManager, WhenFindByContent_ThenFindsMatchingFiles) {
    fsManager->createFile("file1.txt", "Hello World");
    fsManager->createFile("file2.txt", "Goodbye World");
    fsManager->createFile("file3.txt", "Something else");

    auto results = fsManager->findByContent("World");

    EXPECT_EQ(results.size(), 2);
}

TEST_F(GivenTestingFileSystemManager, WhenAbsolutePathUsed_ThenNavigatesCorrectly) {
    fsManager->createDirectory("dir1");
    fsManager->createDirectory("dir2");
    fsManager->createFile("dir2/file.txt", "data");
    fsManager->changeDirectory("dir1");

    EXPECT_TRUE(fsManager->exists("/dir2/file.txt"));
    EXPECT_EQ(fsManager->readFile("/dir2/file.txt"), "data");
}

TEST_F(GivenTestingFileSystemManager, WhenComplexStructureCreated_ThenNavigationWorks) {
    fsManager->createDirectory("home");
    fsManager->createDirectory("home/user");
    fsManager->createDirectory("home/user/documents");
    fsManager->createFile("home/user/documents/readme.txt", "Read this");

    EXPECT_TRUE(fsManager->exists("home/user/documents/readme.txt"));
    EXPECT_EQ(fsManager->readFile("home/user/documents/readme.txt"), "Read this");

    fsManager->changeDirectory("home/user");
    EXPECT_EQ(fsManager->getCurrentPath(), "/home/user");
    EXPECT_TRUE(fsManager->exists("documents/readme.txt"));
}

TEST_F(GivenTestingFileSystemManager, WhenRelativePathUsed_ThenResolvedFromCurrentDirectory) {
    fsManager->createDirectory("dir1");
    fsManager->changeDirectory("dir1");
    fsManager->createFile("file.txt", "content");

    EXPECT_TRUE(fsManager->exists("file.txt"));
    EXPECT_EQ(fsManager->readFile("file.txt"), "content");
}
