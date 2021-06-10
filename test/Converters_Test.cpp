#include "gtest/gtest.h"
#include "../headers/Converters.hpp"

TEST(ConvertStringToTm, CheckDateWithLetters)
{
    std::string dateExample = "a20200101b";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 

    dateExample = "abcd";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 

    dateExample = "20200101180000.";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 
}

TEST(ConvertStringToTm, CheckDateFormat)
{
    std::string dateExample = "20200101";
    tm timePoint = Converters::convertStringToTm(dateExample);
    ASSERT_EQ(timePoint.tm_year, 120);
    ASSERT_EQ(timePoint.tm_mon, 0);
    ASSERT_EQ(timePoint.tm_mday, 1);

    dateExample = "20200512130524";
    timePoint = Converters::convertStringToTm(dateExample);
    ASSERT_EQ(timePoint.tm_year, 120);
    ASSERT_EQ(timePoint.tm_mon, 4);
    ASSERT_EQ(timePoint.tm_mday, 12);
    ASSERT_EQ(timePoint.tm_hour, 13);
    ASSERT_EQ(timePoint.tm_min, 05);
    ASSERT_EQ(timePoint.tm_sec, 24);

    dateExample = "2020 01 01 02:05:00";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 

    dateExample = "202001010205";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 

    dateExample = "202001";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 

    dateExample = "2020-01-01-02-05-00";
    EXPECT_THROW(
    { 
        tm timePoint = Converters::convertStringToTm(dateExample);
    }, std::invalid_argument); 
}

TEST(ConvertStringToTm, CheckPartOfDateRange)
{
    std::string lowerRangeDateExample = "20200101000000";
    tm timePoint = Converters::convertStringToTm(lowerRangeDateExample);
    ASSERT_EQ(timePoint.tm_year, 120);
    ASSERT_EQ(timePoint.tm_mon, 0);
    ASSERT_EQ(timePoint.tm_mday, 1);
    ASSERT_EQ(timePoint.tm_hour, 00);
    ASSERT_EQ(timePoint.tm_min, 00);
    ASSERT_EQ(timePoint.tm_sec, 00);

    std::string upperRangeDateExample = "20201231235959";
    timePoint = Converters::convertStringToTm(upperRangeDateExample);
    ASSERT_EQ(timePoint.tm_year, 120);
    ASSERT_EQ(timePoint.tm_mon, 11);
    ASSERT_EQ(timePoint.tm_mday, 31);
    ASSERT_EQ(timePoint.tm_hour, 23);
    ASSERT_EQ(timePoint.tm_min, 59);
    ASSERT_EQ(timePoint.tm_sec, 59);

    //Test invalid month range inside date string
    std::string invalidMonthRange = "20201301151515";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidMonthRange);
    }, std::out_of_range); 

    //Test invalid day lower range inside date string
    std::string invalidDayLowerRange = "20201000151515";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidDayLowerRange);
    }, std::out_of_range); 

    //Test invalid day upper range inside date string
    std::string invalidDayUpperRange = "20201032151515";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidDayUpperRange);
    }, std::out_of_range); 

    //Test invalid hour range inside date string
    std::string invalidHourRange = "20201005241515";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidHourRange);
    }, std::out_of_range); 

    //Test invalid minute range inside date string
    std::string invalidMinuteRange = "20201005156015";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidMinuteRange);
    }, std::out_of_range); 

    //Test invalid second range inside date string
    std::string invalidSecondRange = "20201005151561";
    EXPECT_THROW(
    { 
        timePoint = Converters::convertStringToTm(invalidSecondRange);
    }, std::out_of_range); 
}

TEST(ConvertTmToString, CheckTmStructure)
{
    struct tm timePoint
    {
        59, //seconds
        59, //minutes
        23, //hours
        5,  //days
        10,  //months
        90   //years
    };
    std::string result = Converters::convertTmToString(timePoint);
    ASSERT_EQ(result, "19901105235959");
    
    struct tm wrongTimePoint
    {
        70, //seconds
        80, //minutes
        90, //hours
        120,  //days
        50,  //months
        90   //years
    };
    EXPECT_THROW(
    { 
        result = Converters::convertTmToString(wrongTimePoint);
    }, std::out_of_range); 
}

TEST(ConvertStringToTime, Check)
{
    std::string firstDate = "20201010101010";
    time_t firstTimePoint = Converters::convertStringToTime(firstDate);

    std::string secondDate = "20201010101005";
    time_t secondTimePoint = Converters::convertStringToTime(secondDate);

    ASSERT_EQ(difftime(firstTimePoint, secondTimePoint), 5);
}
