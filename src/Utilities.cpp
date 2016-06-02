#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool Utilities::String::parseDouble(const std::string &str, double &value){
	char len; //characted to compare the lenght of the copied string to the original one
	std::stringstream ss(str); //open the string stream
	ss >> value; //try to copy the contents of the string into the double
	if (ss.fail() || ss.get(len)) {
		std::cout << "The string : " << str << "is not a valid integer" << std::endl;
		return false;
	}//checks if there has been a problem with the copying process or if not all of the string has been copied
	return true;
} //Function to parse a string into a double

bool Utilities::String::parseInteger(const std::string &str, int &value){
	char len; //characted to compare the lenght of the copied string to the original one
	std::stringstream ss(str); //open the string stream
	ss >> value; //try to copy the contents of the string into the integer
	if (ss.fail() || ss.get(len)) {
		std::cout << "The string : " << str << "is not a valid integer" << std::endl;
		return false;
	}//checks if there has been a problem with the copying process or if not all of the string has been copied
	return true;
} //Function to parse a string into a integer


bool Utilities::File::saveString(std::ofstream &file, const std::string &content){
	if (!file.is_open()){
		std::cout << "Error opening the file" << std::endl;
		return false;		//operation failed
	}	//check if the file has opened correctly
	file << content; //wrtie the contents onto the file
	if (file.bad()){
		std::cout << "Error wrtiting onto the file" << std::endl;
		file.close();		//close the file
		return false;	//operation failed
	} //check if the writing stream process has exectued correctly

	return true;	//operation successful
}//function to save the contents of a string onto a chosen file

bool Utilities::File::loadString(std::ifstream &file, std::string& content){
	std::string line; //string that will contain
	std::stringstream fileData; //stringstream that will contain the file Data
	if (!file.is_open()){
		std::cout << "Error opening the file" << std::endl;
		return false;		//operation failed
	}	//check if the file has opened successfully and if it hassn't it gives a warning
	while (std::getline(file, line)){
		fileData << line << "\n";
	}//read the file line by line and for each line pass it to the string stream
	if (file.bad()){
		std::cout << "Error wrtiting onto the file" << std::endl;
		file.close();		//close the file
		return false;	//operation failed
	} //check if the read stream process has exectued correctly
	content = fileData.str(); //copies the string stream content onto the string
	return true;
}

bool Utilities::File::checkExistance(const std::string& filePath){
	std::ifstream file(filePath.c_str()); //creates a stream of the file
	if (file.good()) { //checks if the file actually exists
		file.close();
		return true;
	}
	else {
		file.close();
		return false;
	}
}//Function that checks whether the file exists 

bool Utilities::File::printFile(const std::string& filePath){
	std::ifstream file;
	file.open(filePath);
	std::string line; //string that will contain
	std::stringstream fileData; //stringstream that will contain the file Data
	if (!file.is_open()){
		std::cout << "Error opening the file" << std::endl;
		return false;		//operation failed
	}	//check if the file has opened successfully and if it hassn't it gives a warning
	while (std::getline(file, line)){
		fileData << line << "\n";
	}//read the file line by line and for each line pass it to the string stream
	if (file.bad()){
		std::cout << "Error wrtiting onto the file" << std::endl;
		file.close();		//close the file
		return false;	//operation failed
	} //check if the read stream process has exectued correctly
	std::cout << fileData.str() << std::endl; //copies the string stream content onto the string
	return true;
}