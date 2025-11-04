#include <gtest/gtest.h>
#include "CommandParser.h"

class GivenTestingCommandParser : public ::testing::Test {
protected:
    CommandParser parser;
};

TEST_F(GivenTestingCommandParser, WhenParseSimpleCommand_ThenCommandValid) {
    auto result = parser.parse("pwd");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "pwd");
    EXPECT_EQ(result.args.size(), 0);
}

TEST_F(GivenTestingCommandParser, WhenParseCommandWithArgument_ThenArgsSet) {
    auto result = parser.parse("mkdir testdir");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "mkdir");
    EXPECT_EQ(result.args.size(), 1);
    EXPECT_EQ(result.args[0], "testdir");
}

TEST_F(GivenTestingCommandParser, WhenParseChangeDirectory_ThenPathSet) {
    auto result = parser.parse("cd /path/to/dir");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "cd");
    EXPECT_EQ(result.args[0], "/path/to/dir");
}

TEST_F(GivenTestingCommandParser, WhenParseEchoCommand_ThenTextArgumentsSet) {
    auto result = parser.parse("echo Hello World");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "echo");
    EXPECT_GE(result.args.size(), 1);
}

TEST_F(GivenTestingCommandParser, WhenParseEchoWithAppendRedirection_ThenValid) {
    auto result = parser.parse("echo Hello >> file.txt");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "echo");
}


TEST_F(GivenTestingCommandParser, WhenParseCatCommand_ThenValid) {
    auto result = parser.parse("cat file.txt");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "cat");
}

TEST_F(GivenTestingCommandParser, WhenParseGrepCommand_ThenPatternSet) {
    auto result = parser.parse("grep pattern");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "grep");
    EXPECT_EQ(result.args[0], "pattern");
}

TEST_F(GivenTestingCommandParser, WhenParseFindCommand_ThenNameSet) {
    auto result = parser.parse("find test.txt");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "find");
    EXPECT_EQ(result.args[0], "test.txt");
}

TEST_F(GivenTestingCommandParser, WhenParseTouchCommand_ThenFilenameSet) {
    auto result = parser.parse("touch newfile.txt");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "touch");
    EXPECT_EQ(result.args[0], "newfile.txt");
}

TEST_F(GivenTestingCommandParser, WhenParseRemoveCommand_ThenPathSet) {
    auto result = parser.parse("rm file.txt");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "rm");
    EXPECT_EQ(result.args[0], "file.txt");
}

TEST_F(GivenTestingCommandParser, WhenParseListCommand_ThenValid) {
    auto result = parser.parse("ls");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "ls");
}

TEST_F(GivenTestingCommandParser, WhenParseHelpCommand_ThenValid) {
    auto result = parser.parse("help");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "help");
}

TEST_F(GivenTestingCommandParser, WhenParseExitCommand_ThenValid) {
    auto result = parser.parse("exit");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "exit");
}

TEST_F(GivenTestingCommandParser, WhenParseEmptyCommand_ThenInvalid) {
    auto result = parser.parse("");
    EXPECT_FALSE(result.isValid);
}

TEST_F(GivenTestingCommandParser, WhenParseCommandWithExtraSpaces_ThenParsedCorrectly) {
    auto result = parser.parse("  pwd  ");
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.name, "pwd");
}

TEST_F(GivenTestingCommandParser, WhenParseInvalidCommand_ThenInvalidWithError) {
    auto result = parser.parse("invalidcmd");
    EXPECT_FALSE(result.isValid);
    EXPECT_FALSE(result.errorMessage.empty());
}