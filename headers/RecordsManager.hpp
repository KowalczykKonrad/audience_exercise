/**
	Main class to manage records, output and files
	@file RecordsManager.hpp
	@author Kowalczyk Konrad
*/

#ifndef RECORDSMANAGER_HPP
#define RECORDSMANAGER_HPP

#include "PsvParser.hpp"
#include "Record.hpp"
#include <map>
#include <memory>

class RecordsManager
{
public:
	/*
		Default constructor
		@param inputFileName psv file name
	*/
	RecordsManager(std::string inputFileName);
	~RecordsManager() = default;

	/*
		Create record objects from parsed file
	*/
	void createRecords();

	/*
		Getter for uncalculated records
		@return vector with uncalculated records
	*/
	std::vector<Record> getRecords() const;

	/*
		Calculate end time and duration based on grouped records.
		Loop through the vectors which are divided by day and home id and calculate
		the differance between adjacent records from the same home from same date.
		It gives duration and end time date
	*/
	void calculateEndTime();

	/*
		Write output file with result
		@param outputFile name of the output file
	*/
	void writeFile(const std::string& outputFile = "expected-sessions.psv") const;

	/*
		Look for the given input file name in filesystem
		@return path whole path leading to the file
	*/
	std::experimental::filesystem::path findInputFile(const std::string& inputFileName = "input-statements.psv");
	
	/*
		Sort records in ascending order
	*/
	void sortRecords();

	/*
		Group records first by same date and then by same home id
		@return map where the key is short date like "20200101" and the value is another map.
		This time the key is home id and the value is vector with sorted records.
	*/
	std::map<std::string, std::map<std::string, std::vector<Record>>> groupRecordsByHome() const;

private:

    std::string mInputFileName;                          // psv file name
	std::vector<Record> mUncalculatedRecords;            // uncalculated records read from the file
	std::shared_ptr<PsvParser> mParser;                  // pointer to psv parser
	std::vector<Record> mCalculatedRecords;              // calculated records with end time and duration
};

#endif
