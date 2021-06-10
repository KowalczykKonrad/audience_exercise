#include "gtest/gtest.h"
#include "../headers/RecordsManager.hpp"
#include <fstream>

class RecordsManagerTest : public ::testing::Test
{
protected:
    std::shared_ptr<RecordsManager> manager;
    std::string filePath;
    virtual void SetUp()
    {
        filePath = std::experimental::filesystem::current_path().string() + "/tempTestFileManager.txt";
        std::ofstream outputFileStream(filePath);
        outputFileStream << "HomeNo|Channel|Starttime|Activity\n";
        outputFileStream << "1234|101|20200101180000|Live\n";
        outputFileStream << "1233|101|20200101190000|Live\n";
        outputFileStream << "1233|102|20200101183000|Live\n";
        outputFileStream << "1234|102|20200101153000|Live\n";
        outputFileStream << "1234|102|20200102053000|Live\n";
        outputFileStream.close();
        manager = std::make_shared<RecordsManager>(filePath);
        manager->createRecords();
    }

    virtual void TearDown()
    {
        std::experimental::filesystem::remove(filePath);
    }
};

TEST_F(RecordsManagerTest, FindFile)
{
    ASSERT_EQ(manager->findInputFile("tempTestFileManager.txt"), filePath);
}

TEST_F(RecordsManagerTest, GroupRecord)
{
    std::map<std::string, std::map<std::string, std::vector<Record>>> recordsMap = manager->groupRecordsByHome();
    std::vector<Record> firstDayFirstHome = recordsMap["20200101"]["1234"];
    std::vector<Record> firstDaySecondHome = recordsMap["20200101"]["1233"];
    std::vector<Record> secondDayFirstHome = recordsMap["20200102"]["1234"];

    ASSERT_EQ(firstDayFirstHome.size(), 2);
    ASSERT_EQ(firstDaySecondHome.size(), 2);
    ASSERT_EQ(secondDayFirstHome.size(), 1);

    ASSERT_EQ(firstDayFirstHome[0].info(), "1234|102|20200101153000|Live||0\n");
    ASSERT_EQ(firstDayFirstHome[1].info(), "1234|101|20200101180000|Live||0\n");

    ASSERT_EQ(firstDaySecondHome[0].info(), "1233|102|20200101183000|Live||0\n");
    ASSERT_EQ(firstDaySecondHome[1].info(), "1233|101|20200101190000|Live||0\n");

    ASSERT_EQ(secondDayFirstHome[0].info(), "1234|102|20200102053000|Live||0\n");
}
