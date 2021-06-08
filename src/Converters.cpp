/**
    Converters for whole the project
    @file Converters.cpp
    @author Kowalczyk Konrad
*/

#include "../headers/Converters.hpp"
#include <iomanip>
#include <sstream>

tm Converters::convertStringToTm(std::string& timePoint)
{
    std::string timeWithDashes = "";

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
    char buffer[80];
    struct tm* timeinfo = &timePoint;
    strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);
    return buffer;
}
