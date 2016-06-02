#ifndef Vector3D_HEADER
#define Vector3D_HEADER
#include <string>

class Vector3D {
	// Constructors and Destructors
public:
	Vector3D();											// Null vector constructor
	Vector3D(double x, double y, double z);				// Cartesian coordinates constructor
	Vector3D(const Vector3D& vector);						// Copy constructor
	~Vector3D();											// Destructor

	// Accessors
public:
	double			get_x() const;			// Cartesian x coordinate
	double			get_y() const;			// Cartesian y coordinate
	double			get_z() const;			// Cartesian z coordinates
	double			get_norm() const;		// Magnitude of the vector

	// Operators
public:
	// Assignment operator
	const Vector3D&		operator=(const Vector3D& vector);

	// Overload the Addition operator to add a vector and a value to form a vector
	Vector3D			operator+(double value) const;
	Vector3D			operator-(double value) const;

	// Overload the Addition operator to add two vectors to form a third vector
	Vector3D			operator+(const Vector3D &vector) const;
	Vector3D			operator-(const Vector3D &vector) const;

	// Addition of a value to an existing value, changing its value
	const Vector3D&		operator+=(double value);
	const Vector3D&		operator-=(double value);

	// Addition of one vector to an existing vector, changing its value
	const Vector3D&		operator+=(const Vector3D &vector);
	const Vector3D&		operator-=(const Vector3D &vector);

	// Multiplication/Division by a scalar value
	Vector3D			operator*(double value) const;
	Vector3D			operator/(double value) const;

	// Multiplication/Division by a scalar value to an existing vector, changing its value
	const Vector3D&		operator*=(double value);
	const Vector3D&		operator/=(double value);

	// Dot product of two vectors
	double			dot(const Vector3D &vector) const;
	// Cross product of the Vector3D
	Vector3D		cross(const Vector3D &vector) const;

	//Input/Output methods
public:
	bool load(const std::string& strX, const std::string& strY, const std::string& strZ); //loads the coordinates of a vector from given strings
	std::string to_string() const; //converts the coordinates of the vector to a string

	// Logging
public:
	void print() const; //prints the content of the vector

	//internal methods
protected:
	static double eval_norm(double x, double y, double z);	//  magnitude from cartesian coordinates

	// Data
protected:
	double _x, _y, _z;	// Cartesian x,y and z coordinates
};

#endif