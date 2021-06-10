#include "gtest/gtest.h"
#include "../headers/PsvParser.hpp"
#include <fstream>

class PsvParserTest : public ::testing::Test
{
protected:
    std::string filePath;
    std::shared_ptr<PsvParser> parser;
    virtual void SetUp()
    {
        filePath = std::experimental::filesystem::current_path().string() + "/tempTestFile.txt";
        std::ofstream outputFileStream("tempTestFile.txt");
        outputFileStream << "HomeNo|Channel|Starttime|Activity\n";
        outputFileStream << "1234|101|20200101180000|Live\n";
        outputFileStream << "1234|102|20200101183000|Live\n";
        outputFileStream.close();
        parser = std::make_shared<PsvParser>(filePath);
    }

    virtual void TearDown()
    {
        std::experimental::filesystem::remove(filePath);
    }

};

TEST_F(PsvParserTest, Getters) 
{
    ASSERT_EQ(parser->getColumnRecord(), "HomeNo|Channel|Starttime|Activity");
    ASSERT_EQ(parser->getFilePath(), std::experimental::filesystem::current_path().string() + "/tempTestFile.txt");
}

TEST_F(PsvParserTest, ReadFile) 
{
    std::vector<std::string> fileLines = parser->readFile(filePath);
    ASSERT_EQ(fileLines[0], "HomeNo|Channel|Starttime|Activity");
    ASSERT_EQ(fileLines[1], "1234|101|20200101180000|Live");
    ASSERT_EQ(fileLines[2], "1234|102|20200101183000|Live");

    EXPECT_THROW(
    { 
        parser->readFile("FileDoesNotExist.txt");
    }, std::runtime_error);
}

TEST_F(PsvParserTest, ParseFile) 
{
    std::vector<std::vector<std::string>> tokenizedRecords = parser->parse(filePath);

    ASSERT_EQ(tokenizedRecords.size(), 2);

    ASSERT_EQ(tokenizedRecords[0][0], "1234");
    ASSERT_EQ(tokenizedRecords[0][1], "101");
    ASSERT_EQ(tokenizedRecords[0][2], "20200101180000");
    ASSERT_EQ(tokenizedRecords[0][3], "Live");

    ASSERT_EQ(tokenizedRecords[1][0], "1234");
    ASSERT_EQ(tokenizedRecords[1][1], "102");
    ASSERT_EQ(tokenizedRecords[1][2], "20200101183000");
    ASSERT_EQ(tokenizedRecords[1][3], "Live");
}

