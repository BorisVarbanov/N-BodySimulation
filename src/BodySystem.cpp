#include "BodySystem.h"
#include "Utilities.h"

#include <sstream>
#include <fstream>
#include <iostream>


void BodySystem::load(const std::string& strData){
	Body body;
	std::string strBody; //temp string that will containg the different substrings of the string
	std::istringstream iss(strData); //declares the string stream
	clear(); //clears the stream

	while (std::getline(iss, strBody, '\n')){ //splits the strings into substring based on the '\n' deliminator
		body.load(strBody); //if the load is successful
		push_back(body); //add the Body object to the vector
	}
	if (size() == 0){
		throw std::runtime_error(std::string("Empty bodies list"));
	}
}//function extending the vector class that allows the vector to be loaded from a string

std::string BodySystem::to_string() const{
	std::stringstream systemData; //declare the string stream
	for (unsigned int i = 0; i < size(); i++){ //for every body in the vector
		systemData << at(i).to_string(); //convert the body into a string
		if (i != size() - 1){
			systemData << "\t";
		}
		else{
			systemData << std::endl;
		}//if the body isn't last, insert a '\t', if it is the final one, inserts a new line;
	}
	return systemData.str();
}//function that converts the data contained within the vector to a string

