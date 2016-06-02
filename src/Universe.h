#ifndef Universe_HEADER
#define Universe_HEADER

#include "Integrator.h"

class Universe
{
	//Constructors
public:
	Universe();		//Null universe constructor
	Universe(const std::string inputfile, const std::string outputfile, double dt, double t, int integratorType); //Constructor taking in all the needed arguements to initialise the program
	~Universe();	//Destrctor

	//Methods
public:
	void initIntegrator(); //Initializes the integrator based on the stored Integration type
	void startIntegration(); //Begins the integration program

	//Data
protected:
	int	_integrationMethod;		//enum of the integration method used
	//BodySystem	_bodies;	//lits of bodies  ***SIDENOTE - Should I include this, since the bodies are included and operated by in the Integratro?***
	Integrator *_integrator;	//integrator
	double _timeStep;			//the time step of integration dt
	double _totalTime;			//the total time of the ingreal T;
	std::string _inputFilePath;
	std::string _outputFilePath;

};//Class containing the list of bodies and the integerator, representing the whole universe in our cases

#endif
