#include "Integrator.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>


void Integrator::save(std::ofstream &file){
	if (!Utilities::File::saveString(file, _universe.to_string())){
		throw std::runtime_error("Failed to save output file data");
	}
}//Method that saves the contents of the contained data onto a file

void Integrator::load(std::ifstream &file){
	std::string strData;
	if (!Utilities::File::loadString(file, strData)){
		throw std::runtime_error("Failed to load input file data");
	}
	_universe.load(strData);

}//Method that saves the contents of the contained data onto a file

void EulerIntegrator::update(double dt){
	for (unsigned int i = 0; i < _universe.size(); i++){
		Vector3D total_force; //The total force vector acting on the body
		double total_energy = 0;

		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _universe[i].get_force(_universe[j]);
			}

		}	//calculates the total force acting on the body

		
		_universe[i].advance_position(_universe[i].get_velocity() * dt); //Advances the position of the body
		_universe[i].advance_velocity((total_force / _universe[i].get_mass()) * dt);	//Advances the velocity of the body

		total_energy += _universe[i].get_mass()*_universe[i].get_speed()*_universe[i].get_speed() / 2;
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_energy += _universe[i].get_energy(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		_universe[i].set_energy(total_energy);

	}
} //Updates the position and velocity of each body in the system according to Euler's method. The total force acting on each object is calculated and from it the acceleration is derived. The position and velocity and updated accordingly.

void LeapfrogIntegrator::update(double dt){
	for (unsigned int i = 0; i < _universe.size(); i++){
		Vector3D total_force;	//The total force vector acting on the body at the initial point
		double total_energy = 0;

		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _universe[i].get_force(_universe[j]);
			}

		}	//calculates the total force acting on the body


		_universe[i].advance_position(_universe[i].get_velocity() * dt + (total_force / _universe[i].get_mass()) * (dt*dt / 2)); //advances the position of the object to the new point

		Vector3D total_force_advanced;	//The total force vector acting on the body at the advanced point
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force_advanced += _universe[i].get_force(_universe[j]);
			}

		}	//calculates the total force acting on the body at the new point

		_universe[i].advance_velocity(((total_force / _universe[i].get_mass()) + (total_force_advanced / _universe[i].get_mass())) * (dt / 2)); //advances the velocity of the object to the new point

		total_energy += _universe[i].get_mass()*_universe[i].get_speed()*_universe[i].get_speed() / 2;
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_energy += _universe[i].get_energy(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		_universe[i].set_energy(total_energy);
	}
} //Updates the position and velocity of each body in the system according to Leapfrog method.

void RungeKuttaIntegrator::update(double dt){
	for (unsigned int i = 0; i < _universe.size(); i++){
		std::vector<Vector3D> k;	//RK4 k values
		std::vector<Vector3D> l;	//RK4 k' values
		Body _temp = _universe[i];	//temporary body used for calculating the force(acceleration) each cycle of the RK4 Method
		Vector3D total_force;
		double total_energy = 0;

		//cycle 1

		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _temp.get_force(_universe[j]);
			}
		}	//calculates the total force acting on the body
		k.push_back(_temp.get_velocity());	//defines k1 as the initial velocity of the body
		l.push_back(total_force / _temp.get_mass());	//defines k1' as the initial acceleration on the body
		_temp.set_position(_universe[i].get_position() + (k[0] * (dt / 2)));	//sets the position to the second point
		_temp.set_velocity(_universe[i].get_velocity() + (l[0] * (dt / 2)));	//sets the velocity to the second point

		//cycle 2
		total_force = Vector3D(0, 0, 0);	//resets the force vector
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _temp.get_force(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		k.push_back(_temp.get_velocity()); //defines k2 as the new velocity of the body at the second point
		l.push_back(total_force / _temp.get_mass()); //defines k2' as the acceleration on the body at the second point
		_temp.set_position(_universe[i].get_position() + (k[1] * (dt / 2)));	//sets the position to the third point
		_temp.set_velocity(_universe[i].get_velocity() + (l[1] * (dt / 2)));	//sets the velocity to the third point

		//cycle 3
		total_force = Vector3D(0, 0, 0);	//resets the force vector
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _temp.get_force(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		k.push_back(_temp.get_velocity());	//defines k3 as the new velocity of the body at the third point
		l.push_back(total_force / _temp.get_mass());	//defines k3' as the acceleration on the body at the third point
		_temp.set_position(_universe[i].get_position() + (k[2] * dt));	//sets the position to the fourth point
		_temp.set_velocity(_universe[i].get_velocity() + (l[2] * dt));	//sets the velocity to the fourth point

		//cycle 3
		total_force = Vector3D(0, 0, 0);	//resets the force vector
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_force += _temp.get_force(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		k.push_back(_temp.get_velocity());	//defines k4 as the new velocity of the body at the third point
		l.push_back(total_force / _temp.get_mass());	//defines k4' as the acceleration on the body at the third point

		_universe[i].advance_position((k[0] + (k[1] * 2) + (k[2] * 2) + k[3]) * (dt / 6));	//Advances the position of the actual body
		_universe[i].advance_velocity((l[0] + (l[1] * 2) + (l[2] * 2) + l[3]) * (dt / 6));	//Advances the velocity of the actual body	

		total_energy += _universe[i].get_mass()*_universe[i].get_speed()*_universe[i].get_speed() / 2;
		for (unsigned int j = 0; j < _universe.size(); j++){
			if (j != i){
				total_energy += _universe[i].get_energy(_universe[j]);
			}

		}	//calculates the total force acting on the moved object
		_universe[i].set_energy(total_energy);
	}


} ////Updates the position and velocity of each body in the system according to the 4th order Runge-Kutta method.