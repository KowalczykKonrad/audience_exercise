/**
	Parser for handling psv file and tokenize the records
	@file PsvParser.hpp
	@author Kowalczyk Konrad
*/

#ifndef PSVPARSER_HPP
#define PSVPARSER_HPP

#include <experimental/filesystem>
#include <vector>
#include <string>

class PsvParser
{
public:
	/*
		Explicit constructor to avoid implicit conversion
		@param filePath path to the psv file
	*/
	explicit PsvParser(std::experimental::filesystem::path filePath);
	~PsvParser() = default;

	/*
		Read psv file
		@param filePath path to the psv file
		@return vector of strings read one by one from the file
	*/
	std::vector<std::string> readFile(const std::experimental::filesystem::path& filePath) const;

	/*
		Parse read lines from file by tokenize them
		@param filePath path to the psv file
		@return vector which contains other vectors with tokenized records
	*/
	std::vector<std::vector<std::string>> parse(const std::experimental::filesystem::path& filePath);

	/*
		Getter for column names
		@return column names
	*/
	std::string getColumnRecord() const;

	/*
		Getter for file path
		@return path to the file
	*/
	std::experimental::filesystem::path getFilePath() const;

private:

	/*
		Store column names for future writting into output file
		@param fileLines read lines from file which contain column names as a first line
	*/
	void storeColumnNames(std::vector<std::string>& fileLines);

	/*
		Tokenize record by using regex pipe
		@param record one single unseparated line from file
	*/
	std::vector<std::string> tokenizeRecord(const std::string& record) const;

	std::experimental::filesystem::path mFilePath;      // path to psv file
	std::string mColumnRecord;                          // contains column names from file
};

#endif
