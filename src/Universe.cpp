#include "Universe.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

//A Program written by Orhi

Universe::Universe(){
	_integrator = NULL;
	_timeStep = 0;
	_totalTime = 0;
}//Default constructor

Universe::Universe(const std::string inputfile, const std::string outputfile, double dt, double t, int integrator){
	_integrationMethod = integrator;
	_timeStep = dt;
	_totalTime = t;
	_inputFilePath = inputfile;
	_outputFilePath = outputfile;
	_integrator = NULL;

}//Universe Constructor taking in all the needed arguements

Universe::~Universe(){
	if (_integrator != NULL){
		delete _integrator;
	}
}//Destructor deleteing the pointer if it is assigned to something

void Universe::initIntegrator(){

	// check time step and total time
	if (_timeStep <= 0) {
		throw std::runtime_error("Invalid time step paramter");
	}
	if (_totalTime <= 0) {
		throw std::runtime_error("Invalid total time paramter");
	}
	if (_totalTime < _timeStep) {
		throw std::runtime_error("Invalid step & total time values, step must be smaller than the total time value");
	}

	Integrator *integ = NULL;	//temporary pointer to the integrator

	switch (_integrationMethod) {
		case Integrators::EulerMethod:		integ = new EulerIntegrator(); break;
		case Integrators::LeapfrogMethod:	integ = new LeapfrogIntegrator(); break;
		case Integrators::RungeKuttaMethod:	integ = new RungeKuttaIntegrator(); break;
		default:							std::cout << "This isn't a valid integration Method" << std::endl; break;
	}//switch-case statement to choose the type of integrator.

	if (integ == NULL) {
		throw std::runtime_error("Invalid integrator paramter");
	}


	if (_integrator != NULL){
		delete _integrator; //if the integrator isn't empty, delete it and assign pointer to null
	}

	_integrator = integ; //overwrities the integrator

	std::ifstream file; //declares the file stream
	file.open(_inputFilePath);	//open the file in output mode
	_integrator->load(file);
}

void Universe::startIntegration(){
	double t = 0; //total elapsed time, used in the while loop
	std::ofstream file; //declares the file stream
	file.open(_outputFilePath, std::ofstream::out);	//open the file in output mode

	do{
		_integrator->update(_timeStep); //updates the position of the planets according to the chosen integration method
		_integrator->save(file);
		t += _timeStep;
	} while (t <= _totalTime); //updates the universe every timestep until it reaches the total time and then saves the coordinates of the planets to a file
	file.close(); //closes the file
}
