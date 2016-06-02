#include "Vector3D.h"
#include "Utilities.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>


// Constructors and Destructors

Vector3D::Vector3D() {
	_x = _y = _z = 0;
}	//Defaults Constructor

Vector3D::Vector3D(double x, double y, double z) {
	_x = x; _y = y; _z = z;
}	//Coordinate Constructor


Vector3D::Vector3D(const Vector3D& vector) {
	operator=(vector);
}	//Copy Constructor

Vector3D::~Vector3D() {
}	//Deconstructor

// Accessors

double Vector3D::get_x() const {
	return _x;
} //returns the x component of the vector

double Vector3D::get_y() const {
	return _y;
} //returns the y component of the vector

double Vector3D::get_z() const {
	return _z;
} //returns the z component of the vector

double Vector3D::get_norm() const {
	return eval_norm(_x, _y, _z);
} //returns the magnitude of a vector


// Operators

const Vector3D& Vector3D::operator=(const Vector3D& vector) {
	if (this != &vector) {
		_x = vector._x;
		_y = vector._y;
		_z = vector._z;
	}
	return *this;
}	//copy operator

Vector3D Vector3D::operator+(double value) const {
	return Vector3D(_x + value, _y + value, _z + value);
}	//addition operator

Vector3D Vector3D::operator-(double value) const {
	return Vector3D(_x - value, _y - value, _z - value);
}	//Subtraction operator

Vector3D Vector3D::operator+(const Vector3D &vector) const {
	return Vector3D(_x + vector._x, _y + vector._y, _z + vector._z);
}	//addition operator

Vector3D Vector3D::operator-(const Vector3D &vector) const {
	return Vector3D(_x - vector._x, _y - vector._y, _z - vector._z);
}	//Subtraction operator

const Vector3D& Vector3D::operator+=(double value) {
	_x += value;
	_y += value;
	_z += value;
	return *this;
}	//Addition overwrite operator

const Vector3D& Vector3D::operator-=(double value) {
	_x -= value;
	_y -= value;
	_z -= value;
	return *this;
}	//Subtraction overwrite operator

const Vector3D& Vector3D::operator+=(const Vector3D &vector) {
	_x += vector._x;
	_y += vector._y;
	_z += vector._z;
	return *this;
}	//Addition overwrite operator

const Vector3D& Vector3D::operator-=(const Vector3D &vector) {
	_x -= vector._x;
	_y -= vector._y;
	_z -= vector._z;
	return *this;
}	//Subtraction overwrite operator

Vector3D Vector3D::operator*(double value) const {
	return Vector3D(_x * value, _y * value, _z*value);
}	//Multiplication by a scalar value

Vector3D Vector3D::operator/(double value) const {
	if (value != 0.0) {
		return Vector3D(_x / value, _y / value, _z / value);
	}
	else {
		std::cout << "Divistion by zero error" << std::endl;
		return Vector3D();
	}
}	//Division by scalar value

const Vector3D& Vector3D::operator *=(double value) {
	_x *= value;
	_y *= value;
	_z *= value;
	return *this;
}	//Scalar multiplication overwrite operator

const Vector3D& Vector3D::operator /=(double value) {
	if (value != 0.0) {
		_x /= value;
		_y /= value;
		_z /= value;
	}
	else {
		std::cout << "Divistion by zero error" << std::endl;
	}
	return *this;
}	//Scalar division overwrite operator

double Vector3D::dot(const Vector3D &vector) const {
	double result = 0;
	result += _x * vector._x;
	result += _y * vector._y;
	result += _z * vector._z;
	return result;
}	//Dot product of two vectors

Vector3D Vector3D::cross(const Vector3D &vector) const {
	return Vector3D(_y*vector._z - _z*vector._y, _z*vector._x - _x*vector._z, _x*vector._y - _y*vector._x);
}	//Cross product


// Logging


void Vector3D::print() const {
	std::cout << "The Cartesian coordinates of the vector are: x= " << _x << " and y= " << _y << " and z= " << _z << std::endl;
}	//prints the components of the vector

double Vector3D::eval_norm(double x, double y, double z) {
	return sqrt(x * x + y * y + z * z);
}	//evaluates the norm of the vector


std::string Vector3D::to_string() const{
	std::stringstream vectorData;
	vectorData << _x << ";" << _y << ";" << _z;
	return vectorData.str();
}	//converts the contents of the vector to a string

bool Vector3D::load(const std::string& strX, const std::string& strY, const std::string& strZ){
	return Utilities::String::parseDouble(strX, _x) && Utilities::String::parseDouble(strY, _y) && Utilities::String::parseDouble(strZ, _z);
	return true;
}	//loads the contents of a vector from 3 different strings;