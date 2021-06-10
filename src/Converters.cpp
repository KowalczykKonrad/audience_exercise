/**
    Converters for whole the project
    @file Converters.cpp
    @author Kowalczyk Konrad
*/

#include "../headers/Converters.hpp"
#include <ctype.h>
#include <iomanip>
#include <sstream>

tm Converters::convertStringToTm(std::string& timePoint)
{
    std::string timeWithDashes = "";
    checkStringDate(timePoint);

    for (auto it = timePoint.cbegin(); it != timePoint.cend(); ++it)
    {
        auto index = std::distance(timePoint.cbegin(), it);
        bool isEven = index % 2 == 0;
        bool indexAfterYear = index != 2;
        if (isEven && indexAfterYear)
        {
            timeWithDashes += "-";
        }
        timeWithDashes += *it;
    }
    timeWithDashes.erase(0, 1); //just to remove '-' at the beginning of string
    std::istringstream date_s(timeWithDashes);
    struct tm date_c;
    date_s >> std::get_time(&date_c, "%Y-%m-%d-%H-%M-%S");
    return date_c;
}

std::string Converters::convertTmToString(tm& timePoint)
{
    checkTmDate(timePoint);
    char buffer[80];
    struct tm* timeinfo = &timePoint;
    strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);
    return buffer;
}

time_t Converters::convertStringToTime(std::string& timePoint)
{
	tm  timeStr = Converters::convertStringToTm(timePoint);
	return mktime(&timeStr);
}

void Converters::checkStringDate(const std::string& timePoint)
{
    const int longDateTimeSize = 14;
    const int shortDateTimeSize = 8;

    if(timePoint.size() != longDateTimeSize && timePoint.size() != shortDateTimeSize)
    {
        throw std::invalid_argument("Time string should be in format YYYYMMDDHHMMSS or YYYYMMDD");
    }

    for(auto& letter : timePoint)
    {
        if(isalpha(letter))
        {
            throw std::invalid_argument("Time string should contain only digits");
        }
    }
    //Check months
    int positionPartOfDate = 4;
    std::string partOfDate = timePoint.substr(positionPartOfDate, 2);
    checkPartOfStringDate(partOfDate, 12, 0);

    //Check days
    positionPartOfDate = 6;
    partOfDate = timePoint.substr(positionPartOfDate, 2);
    checkPartOfStringDate(partOfDate, 31, 1);

    if(timePoint.size() == longDateTimeSize)
    {
        //Check hours
        positionPartOfDate = 8;
        partOfDate = timePoint.substr(positionPartOfDate, 2);
        checkPartOfStringDate(partOfDate, 23, 0);

        //Check minutes
        positionPartOfDate = 10;
        partOfDate = timePoint.substr(positionPartOfDate, 2);
        checkPartOfStringDate(partOfDate, 59, 0);

        //Check seconds
        positionPartOfDate = 12;
        partOfDate = timePoint.substr(positionPartOfDate);
        checkPartOfStringDate(partOfDate, 60, 0);
    }
}

void Converters::checkPartOfStringDate(const std::string& partOfDate, const int upperLimit, const int lowerLimit)
{
    if(stoi(partOfDate) < lowerLimit || stoi(partOfDate) > upperLimit)
    {
        throw std::out_of_range("Invalid range of string date member");
    }
}

void Converters::checkTmDate(const tm& timePoint)
{

    if(timePoint.tm_mon < 0 || timePoint.tm_mon > 11)
    {
        throw std::out_of_range("Invalid range for months in tm structure");
    }

    if(timePoint.tm_mday < 1 || timePoint.tm_mday > 31)
    {
        throw std::out_of_range("Invalid range for days in tm structure");
    }

    if(timePoint.tm_hour < 0 || timePoint.tm_hour > 23)
    {
        throw std::out_of_range("Invalid range for hours in tm structure");
    }

    if(timePoint.tm_min < 0 || timePoint.tm_min > 59)
    {
        throw std::out_of_range("Invalid range for minutes in tm structure");
    }

    if(timePoint.tm_sec < 0 || timePoint.tm_sec > 60)
    {
        throw std::out_of_range("Invalid range for seconds in tm structure");
    }
}
