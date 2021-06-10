/**
    Parser for handling psv file and tokenize the records
    @file PsvParser.cpp
    @author Kowalczyk Konrad
*/

#include "../headers/PsvParser.hpp"
#include "../headers/Record.hpp"
#include <fstream>
#include <regex>
#include <iostream>

PsvParser::PsvParser(std::experimental::filesystem::path filePath)
      : mFilePath(filePath),
        mColumnRecord("HomeNo|Channel|Starttime|Activity")
{
}

std::vector<std::string> PsvParser::readFile(const std::experimental::filesystem::path& filePath) const
{
    std::ifstream streamFile(filePath, std::ios::in | std::ios::binary);
    if (!streamFile)
    {
        std::string exceptionMsg = "Can't open file: " + filePath.string();
        throw std::runtime_error(exceptionMsg.c_str());
    }

    std::string singleFileLine;
    std::vector<std::string> fileLines;
    while (std::getline(streamFile, singleFileLine))
    {
        fileLines.push_back(singleFileLine);
    }
    streamFile.close();
    return fileLines;
}

void PsvParser::storeColumnNames(std::vector<std::string>& fileLines)
{
    mColumnRecord = fileLines.front();
    fileLines.erase(fileLines.begin());
}

std::vector<std::string> PsvParser::tokenizeRecord(const std::string& record) const
{
    const std::regex pipe("\\|");
    std::vector<std::string> tokenizedRec
    (
        std::sregex_token_iterator(record.begin(), record.end(), pipe, -1),
        std::sregex_token_iterator{}
    );
    return tokenizedRec;

}

std::vector<std::vector<std::string>> PsvParser::parse(const std::experimental::filesystem::path& filePath)
{
    try
    {
        std::vector<std::string> fileLines = readFile(filePath);
        storeColumnNames(fileLines);
        std::vector<std::vector<std::string>> tokenizedRecords;
        for (auto line : fileLines)
        {
            tokenizedRecords.push_back(tokenizeRecord(line));
        }
        return tokenizedRecords;
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

std::string PsvParser::getColumnRecord() const
{
    return mColumnRecord;
}

std::experimental::filesystem::path PsvParser::getFilePath() const
{
    return mFilePath;
}
