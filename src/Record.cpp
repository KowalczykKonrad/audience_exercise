/**
	Representative of the single record from the psv file
	@file Record.cpp
	@author Kowalczyk Konrad
*/

#include "../headers/Converters.hpp"
#include "../headers/Record.hpp"
#include <iostream>
#include <sstream> 

Record::Record(std::string homeId, std::string channel, std::string startTime, std::string activity)
	: mHomeId(homeId),
	  mChannel(channel),
	  mStartTime(startTime),
	  mActivity(activity),
	  mEndTime(),
	  mDuration()
{
}

void Record::setEndTime(const std::string& endTime)
{
	mEndTime = endTime;
}

void Record::setDuration(const int duration)
{
	mDuration = duration;
}

std::string Record::getStartTime() const
{
	return mStartTime;
}

std::string Record::getHomeId() const
{
	return mHomeId;
}

time_t Record::convertStringToTime()
{
	tm  timeStr = Converters::convertStringToTm(mStartTime);
	return mktime(&timeStr);
}

int Record::getDuration() const
{
	return mDuration;
}

std::string Record::info() const
{
	std::stringstream ss;
	ss << mHomeId << "|" << mChannel << "|" << mStartTime << "|" << mActivity << "|" << mEndTime << "|" << mDuration << "\n";
	return ss.str();
}
