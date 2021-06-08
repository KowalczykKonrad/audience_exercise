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
}

#endif

