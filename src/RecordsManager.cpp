/**
    Main class to manage records, output and files
    @file RecordsManager.cpp
    @author Kowalczyk Konrad
*/

#include "../headers/Converters.hpp"
#include "../headers/RecordsManager.hpp"
#include <algorithm>
#include <ctime>
#include <time.h>
#include <fstream>  

RecordsManager::RecordsManager(std::string inputFileName)
	: mInputFileName(inputFileName),
      mUncalculatedRecords(),
      mCalculatedRecords()
{
    try
    {
        mParser = std::make_shared<PsvParser>(findInputFile(mInputFileName));
    }
    catch (const std::runtime_error& e)
    {
        exit(EXIT_FAILURE);
    }
    catch (const std::exception& e)
    {
        exit(EXIT_FAILURE);
    }
}

std::experimental::filesystem::path RecordsManager::findInputFile(const std::string& inputFileName)
{
    std::string currentPath = std::experimental::filesystem::current_path().parent_path().string();
    std::experimental::filesystem::path inputFilePath;
    for (const auto& entry : std::experimental::filesystem::recursive_directory_iterator(currentPath))
    {
        if (entry.path().string().find(inputFileName) != std::string::npos)
        {
            inputFilePath = entry.path();
            break;
        }
    }

    if (inputFilePath.empty())
    {
        std::string exceptionMsg = "Can't find file: " + inputFileName;
        throw std::runtime_error(exceptionMsg.c_str());
    }
    return inputFilePath;
}

void RecordsManager::createRecords()
{
    std::vector<std::vector<std::string>> records = mParser->parse(mParser->getFilePath());
    for (auto& record : records)
    {
        mUncalculatedRecords.push_back(Record(record[0], record[1], record[2], record[3]));
    }
    sortRecords();
}

void RecordsManager::sortRecords()
{
    std::sort(mUncalculatedRecords.begin(), mUncalculatedRecords.end(), [](const auto& lhs, const auto& rhs)
        {
            return lhs.getStartTime() < rhs.getStartTime();
        });
}

std::vector<Record> RecordsManager::getRecords() const
{
    return mUncalculatedRecords;
}

std::map<std::string, std::map<std::string, std::vector<Record>>> RecordsManager::groupRecordsByHome() const
{
    std::map<std::string, std::map<std::string, std::vector<Record>>> recordsForHomeDay;

    for (const auto& record : mUncalculatedRecords)
    {
        std::string shortDate = record.getStartTime().substr(0, 8);
        if (recordsForHomeDay.find(shortDate) != recordsForHomeDay.end())
        {
            if (recordsForHomeDay[shortDate].find(record.getHomeId()) != recordsForHomeDay[shortDate].end())
            {
                recordsForHomeDay[shortDate][record.getHomeId()].push_back(record);
            }
            else
            {
                recordsForHomeDay[shortDate][record.getHomeId()] = std::vector<Record>{ record };
            }
        }
        else
        {
            recordsForHomeDay[shortDate] = 
                std::map<std::string, std::vector<Record>>{ {record.getHomeId(), std::vector<Record>{record}} };
        }
    }

    return recordsForHomeDay;
}

void RecordsManager::calculateEndTime()
{
    struct tm endOfDay
    {
        59, //seconds
        59, //minutes
        23, //hours
        0,  //days
        0,  //months
        0   //years
    };

    std::map<std::string, std::map<std::string, std::vector<Record>>> groupedRecords = groupRecordsByHome();


    try
    {
        ////Group records by day and home
        for (auto& dayMap : groupedRecords)
        {
            std::string keyDay = dayMap.first;
            tm storeOnlyDate = Converters::convertStringToTm(keyDay);
            endOfDay.tm_year = storeOnlyDate.tm_year;
            endOfDay.tm_mon = storeOnlyDate.tm_mon;
            endOfDay.tm_mday = storeOnlyDate.tm_mday;
            for (auto& homeMap : dayMap.second)
            {
                for (int i = 0; i < homeMap.second.size(); ++i)
                {
                    std::string tempTime = homeMap.second[i].getStartTime();
                    time_t previousTime = Converters::convertStringToTime(tempTime);
                    time_t currentTime;
                    if (i == homeMap.second.size() - 1)
                    {
                        //Add 1 because without it duration loses 1 seconds eq 39599
                        currentTime = mktime(&endOfDay) + 1;
                    }
                    else
                    {
                        std::string tempTime = homeMap.second[i+1].getStartTime();
                        currentTime = Converters::convertStringToTime(tempTime);
                    }

                    double epochTime = difftime(currentTime, previousTime);
                    homeMap.second[i].setDuration(int(epochTime));

                    time_t endDate = previousTime + homeMap.second[i].getDuration() - 1;
                    struct tm timeinfo;
                    localtime_r(&endDate, &timeinfo);
                    homeMap.second[i].setEndTime(Converters::convertTmToString(timeinfo));
                    mCalculatedRecords.push_back(homeMap.second[i]);
                }
            }
        }
    }
    catch (const std::invalid_argument& e)
    {
        exit(EXIT_FAILURE);
    }
    catch (const std::out_of_range& e)
    {
        exit(EXIT_FAILURE);
    }
    catch (const std::exception& e)
    {
        exit(EXIT_FAILURE);
    }
}

void RecordsManager::writeFile(const std::string& outputFile) const
{
    std::experimental::filesystem::path outputFilePath = mParser->getFilePath().parent_path();
    outputFilePath /= outputFile;
    
    if (std::experimental::filesystem::exists(outputFilePath.parent_path()))
    {
        std::ofstream outputFileStream(outputFilePath);

        outputFileStream << mParser->getColumnRecord() << "|" << "EndTime" << "|" << "Duration\n";

        for (const auto& record : mCalculatedRecords)
        {
            outputFileStream << record.info();
        }
        outputFileStream.close();
    }
    else
    {
        std::experimental::filesystem::create_directories(outputFilePath.parent_path());
    }
}
