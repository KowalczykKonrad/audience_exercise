/**
	Representative of the single record from the psv file
	@file Record.hpp
	@author Kowalczyk Konrad
*/

#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>

class Record
{
public:
	/*
		Constructor for Record
		@param homeId represents column HomeNo from the file
		@param channel represents column Channel from the file
		@param startTime represents column Starttime from the file
		@param activity represents column Activity from the file
		@param endTime represents column EndTime from the file
		@param duration represents column Duration from the file
	*/
	Record(std::string homeId, std::string channel, std::string startTime, std::string activity, std::string endTime = "", int duration = 0);
	~Record() = default;

	/*
		Setter for endTime which is calculated later than creation of the object
		@param endTime new value to be set
	*/
	void setEndTime(const std::string& endTime);

	/*
		Setter for duration which is calculated later than creation of the object
		@param duration new value to be set
	*/
	void setDuration(const int duration);

	/*
		Getter for startTime
		@return mStartTime
	*/
	std::string getStartTime() const;

	/*
		Getter for homeId
		@return mHomeId
	*/
	std::string getHomeId() const;

	/*
		Getter for duration
		@return mDuration
	*/
	int getDuration() const;

	/*
		Information about the values of class members
		@return string prepared to be entered into the file
	*/
	std::string info() const;

private:
	std::string mHomeId;                  // member represents column HomeNo
	std::string mChannel;                 // member represents column Channel
	std::string mStartTime;               // member represents column Starttime
	std::string mActivity;                // member represents column Activity
	std::string mEndTime;                 // member represents column EndTime
	int mDuration;                        // member represents column Duration
};

#endif
