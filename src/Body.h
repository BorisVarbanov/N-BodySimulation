#ifndef Body_HEADER
#define Body_HEADER

#include "Vector3D.h"

/*
Class that describes bodies in the system, containing their position and velocities and space as well as their mass.
*/
class Body{

	//Constructors and Destructors
public:
	Body(); //Default Constructors
	Body(Vector3D pos, Vector3D velocity, double mass); //Constructor taking in data
	Body(const Body& planet);	//Copy Constructor
	~Body(); //Default Destructor

	//Mutators
public:
	void set_position(Vector3D new_position); //sets the position of the body
	void set_velocity(Vector3D new_position); //sets the velocity of the body
	void set_energy(double new_energy); //sets the energy of the body
	void advance_position(Vector3D new_position); //increases the position of the body
	void advance_velocity(Vector3D new_position); //increases the velocity of the body

	//Accessors
public:
	Vector3D get_force(Body planet) const; //Returns the force vector acting between the body and a different one
	Vector3D get_position() const; //returns the position of the body
	Vector3D get_velocity() const; //returns the velocity of the body
	double get_mass() const; //returns the mass of the body
	double get_distance(Body planet) const; //returns the absolute distance between the body and a different object
	double get_energy(Body planet) const; //returns the potential energy due to the gravitational potential
	double get_speed() const; //returns the speed of the body
	
	//Operators
public:
	const Body&		operator=(const Body& planet); //Assignment operator

	//Evaluation Functions
public:
	Vector3D eval_force(Body planet) const; //evaluates the force between two different objects
	double eval_energy(Body planet) const; //evaluates the energy due to the gravitational force between two different objects

public:
	void			load(const std::string& strData);	//loads the data that should be contained in the object from a given object
	std::string		to_string() const;	//converts the data stored in the Body object to a string

	//Data
protected:
	double _energy; //total energy of the object
	double _mass; //the mass of the body
	Vector3D _position; //the position vector of the body
	Vector3D _velocity; //the velocity vector of the body
};

#endif