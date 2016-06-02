#ifndef Utilities_HEADER
#define Utilities_HEADER

#include <string>
#include <fstream>

namespace Utilities {

	namespace String {

		bool	parseDouble(const std::string& str, double& value); //checks if a string can be converted into a double and does the conversion
		bool	parseInteger(const std::string& str, int& value); //checks if a string can be converted into a double and does the conversion
	}//Namespace containing methods associated with string manipulation

	namespace File {
		bool	saveString(std::ofstream &file, const std::string& content); //saves the contents of a strings onto a file
		bool	loadString(std::ifstream &file, std::string& content); //loads the contents of a file onto a string
		bool	checkExistance(const std::string& filePath); //checks if the file exists
		bool	printFile(const std::string& filePath);

	}//Namespace containing file manipulations and operation methods
};

#endif