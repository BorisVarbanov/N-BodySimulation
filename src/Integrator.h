#ifndef Integrator_HEADER
#define Integrator_HEADER

#include "BodySystem.h"

class Integrator{
public:
	//Constructors
	Integrator() {};							//Default Constructor
	~Integrator() {};							//Deconstructor

	//Mutators
public:
	virtual void update(double dt) = 0; //pure virtual function that updates the position and velocities of the planets each interval of time
	//Output/Input
public:
	void save(std::ofstream &file); //function that saves the contents of the body vector onto a file
	void load(std::ifstream &file); //function that loads the contents of the file into the body vector

	//Data
protected:
	BodySystem _universe;
};

class EulerIntegrator : public Integrator{ //A System that evolves according to approximation Euler's method
public:
	EulerIntegrator() : Integrator() {};
	void update(double dt);
};

class LeapfrogIntegrator : public Integrator{ //A system that evolves according to the approximation Leapfrog method
public:
	LeapfrogIntegrator() : Integrator() {};
	void update(double dt);
};

class RungeKuttaIntegrator : public Integrator{ //A system that evolves according to the 4th order Runge-Kutta approximation method.
public:
	RungeKuttaIntegrator() : Integrator() {};
	void update(double dt);
};

namespace Integrators {
	enum { EulerMethod = 1, LeapfrogMethod = 2, RungeKuttaMethod = 3 };
};	//namespace containing the possible methods of integration that the function allows

#endif