/**
	Converters for whole the project
	@file Converters.hpp
	@author Kowalczyk Konrad
*/

#ifndef CONVERTERS_HPP
#define CONVERTERS_HPP

#include <string>

namespace Converters
{
	/*
		Convert string into tm object
		@param timePoint the string to convert
		@return converted tm object
	*/
	tm convertStringToTm(std::string& timePoint);

	/*
		Convert tm object into string
		@param timePoint the tm object to convert
		@return converted string
	*/
	std::string convertTmToString(tm& timePoint);

	/*
		Convert string to time_t type
        @param timePoint time string to convert into time_t object
		@return converted time_t object
	*/
	time_t convertStringToTime(std::string& timePoint);

	/*
		Check if format and values inside string date are correct
		@param timePoint the string to check
	*/
   void checkStringDate(const std::string& timePoint);

	/*
		Helper function for better readability which checks single part of date like e.q seconds or minutes
		@param partOfDate part of date like seconds or minutes to check
		@param upperLimit upper range of checked part of date
		@param lowerLimit lower range of checked part of date
	*/
   void checkPartOfStringDate(const std::string& partOfDate, const int upperLimit, const int lowerLimit);

	/*
		Check if format and values inside tm structure are correct
		@param timePoint the tm structure to check
	*/
   void checkTmDate(const tm& timePoint);
}

#endif

