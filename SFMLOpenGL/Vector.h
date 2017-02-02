#pragma once
#include <iostream>
#include <cmath>
#include <string>

class Vector
{
protected:
	double m_x;
	double m_y;
	double m_z;
	double m_length;
	double m_lengthSquared;
	double m_pi;
public:
	Vector(double m_x = 0, double m_y = 0, double m_z = 0);

	double x();
	double y();
	double z();

	double length();
	double lengthSquared();
	void normalise();
	double dotProduct(Vector v1);
	Vector crossProduct(Vector v1);
	double angleBetween(Vector v1);
	Vector unit();
	Vector parallelComponent(Vector v1);
	Vector perpendicularComponent(Vector v1);
	Vector scale(float scale);
	void FlipX();
	void FlipY();
	static double distance(Vector v1, Vector v2);
	std::string toString();
};
//operators
Vector operator+(Vector v1, Vector v2); // sum of two vectors
Vector operator*(Vector v1, Vector v2); // product of two vectors
Vector operator*(int scale, Vector v1); // int scalar * by vector
Vector operator*(float scale, Vector v1); // float scalar * by vector
Vector operator*(double scale, Vector v1); // double scalar * by vector
Vector operator-(Vector v1, Vector v2); // subtract of one vector from another
Vector operator-(Vector v1); // negate
Vector operator^(Vector v1, Vector v2);

bool operator==(Vector v1, Vector v2); // check if they are equal
bool operator!=(Vector v1, Vector v2); // check if they aren't equal
