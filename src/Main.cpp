#include "Utilities.h"
#include "Universe.h"
#include "Globals.h"
#include <iostream>


void main(int argc, char* argv[]){

	if (argc != 6){
		std::cout << message::helpMessage << std::endl;
		return;
	}//checks if all 5 arguements have been given

	char *input_file = argv[1];
	char *output_file = argv[2];

	double step;
	if (!Utilities::String::parseDouble(argv[3], step)) {
		std::cout << "Invalid time step paramter" << std::endl;
		return;
	}

	double time;
	if (!Utilities::String::parseDouble(argv[4], time)) {
		std::cout << "Invalid total time paramter" << std::endl;
		return;
	}

	int method;
	if (!Utilities::String::parseInteger(argv[5], method)) {
		std::cout << "Inavalid method paramter" << std::endl;
		return;
	}

	try {
		Universe instance(input_file, output_file, step, time, method); //initializes the instance of our universe
		instance.initIntegrator(); //loads the bodies into the universe and sets the integrator

		std::cout << "Integration started..." << std::endl;
		instance.startIntegration(); //begins the integration methods and saves the positions
		std::cout << "Integration complete." << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

/*
PH3170 N-Body Simulation Project
Boris Varbanov
*/