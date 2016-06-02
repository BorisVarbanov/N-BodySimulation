#ifndef BodySystem_HEADER
#define BodySystem_HEADER

#include "Body.h"
#include <vector>

/*
Class containing all the initialised body objects and operates on them.
*/
class BodySystem : public std::vector<Body>{

	//Loader extensions
public:
	void load(const const std::string& strData);
	//loads the contents of a file into a BodySystem object

	//Input/Output methods
public:
	std::string to_string() const; //converts the data stored in the bodySystem to a string
};//class inherits from std::vectors and extends it with two functions. It basicly acts as a vector in most cases.

#endif	