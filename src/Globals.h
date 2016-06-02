#ifndef Globals_HEADER
#define Globals_HEADER

#include <string>

//Physical and mathetmical constants
namespace constants
{
	const double G = -6.67408E-11; //Defines the Gravitational constant
	const double pi = 3.14159265359; // Defines the pi constant
}
namespace message
{
	const std::string helpMessage = "Resolves the problem for the interaction of many bodies.\n\nUsage:\nN-BodySimulation.exe input output step time method\n\t- input: input file;\n\t- output: output file;\n\t- step: time step, in seconds;\n\t- time: total time, in seconds;\n\t- method: the integration method:\n\t\t1 -> Euler's method;\n\t\t2 -> Leapfrog method;\n\t\t3 -> Runge Kutta method.\n\nExample:\n\"c:\\...\\Debug\\N-bodySimulationPorject.exe\" \"c:\\...\\bodies.txt\" \"c:\\...\\OutputData.txt\" 86400 31556952 1\n";
}


#endif