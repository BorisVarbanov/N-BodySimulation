#include "Body.h"
#include "Vector3D.h"
#include "Utilities.h"
#include "Globals.h"

using namespace constants;
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>


Body::Body(){
	_mass = 0;
	_position = Vector3D(0, 0, 0);
	_velocity = Vector3D(0, 0, 0);
	_energy = 0;
} //Default Constructor

Body::Body(Vector3D pos, Vector3D velocity, double mass){
	_mass = mass;
	_position = pos;
	_velocity = velocity;
	_energy = mass*velocity.get_norm()*velocity.get_norm() / 2;
} //Data Construtor


Body::Body(const Body& planet){
	operator=(planet);
} //Copy constructor

Body::~Body(){
} //Deconstructor

const Body& Body::operator=(const Body& planet) {
	if (this != &planet) {
		_mass = planet.get_mass();
		_position = planet.get_position();
		_velocity = planet.get_velocity();
	}
	return *this;
}	//copy operator

void Body::set_position(Vector3D new_position){
	_position = new_position;
} //Sets the position vector of the body

void Body::set_velocity(Vector3D new_velocity){
	_velocity = new_velocity;
} //Sets the velocty vector of the body

void Body::set_energy(double new_energy){
	_energy = new_energy;
} //Sets the energy of the body

void Body::advance_position(Vector3D new_position){
	_position += new_position;
} //Advances the velocty vector of the body

void Body::advance_velocity(Vector3D new_velocity){
	_velocity += new_velocity;
} //Advances the velocty vector of the body

Vector3D Body::eval_force(Body planet) const {
	return (_position - planet.get_position())*(G*_mass*planet.get_mass() / pow(get_distance(planet), 3));
} //Evaluates the force between the body and a different body

double Body::eval_energy(Body planet) const{
	return (G*_mass*planet.get_mass() / get_distance(planet));
} //Evaluates the energy due to the gravitational potentail field

Vector3D Body::get_force(Body planet) const{
	return eval_force(planet);
} //Returns the force vector between the body and a different body

double Body::get_energy(Body planet) const{
	return eval_energy(planet);
} //returns the potential energy due to the gravitational force

Vector3D Body::get_position() const{
	return _position;
} //Returns the position vector of the body

Vector3D Body::get_velocity() const{
	return _velocity;
} //Returns the velocity vector of the body

double Body::get_mass() const{
	return _mass;
} //Returns the mass of the body

double Body::get_distance(Body planet) const{
	return abs((_position - planet.get_position()).get_norm());
} //Returns the absolute distance between the body and a different body

double Body::get_speed() const{
	return abs(_velocity.get_norm());
} //Returns the speed of the object

void Body::load(const std::string& strData){
	std::istringstream iss(strData);	//open the string in a stringstream
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(iss, token, ';')){
		tokens.push_back(token);
	}//splits the total string into substring tokens, using the ';' delimiter
	if (tokens.size() < 12) {
		throw std::runtime_error(std::string("Invalid body data: ") + strData);
	}

	if (!Utilities::String::parseDouble(tokens[1], _mass) || (_mass <= 0.0)){
		throw std::runtime_error(std::string("Invalid body mass: ") + strData);
	}

	if (!_position.load(tokens[2], tokens[3], tokens[4])) {
		throw std::runtime_error(std::string("Invalid body position: ") + strData);
	}

	if (!_velocity.load(tokens[5], tokens[6], tokens[7])) {
		throw std::runtime_error(std::string("Invalid body velocity: ") + strData);
	}
} //load function that loads the contents of a string into the Body

std::string Body::to_string() const{
	std::stringstream vectorData;
	vectorData << _position.to_string() << ";" << _energy;
	return vectorData.str();
}//Method that converts the data stored in the body type into a string
