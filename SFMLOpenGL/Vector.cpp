#include "Vector.h"

Vector::Vector(double x,double y,double z)
:	m_x(x),
	m_y(y),
	m_z(z)
{
	m_pi = acos(-1); // this is pi

};

double Vector::x()
{
	return m_x;
}
double Vector::y()
{
	return m_y;
}
double Vector::z()
{
	return m_z;
}

double Vector::length()
{
	m_length = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	return m_length;
}
double Vector::lengthSquared()
{
	m_lengthSquared = (m_x * m_x + m_y * m_y + m_z * m_z);
	return m_lengthSquared;
}
void Vector::normalise()
{
	if (length() > 0.0)
	{
		m_x /= m_length;
		m_y /= m_length;
		m_z /= m_length;
	}
}


Vector operator+(Vector v1, Vector v2)
{// An overloaded operator + to return the sum of 2 vectors
	return Vector(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
Vector operator*(Vector v1, Vector v2)
{// An overloaded operator * to return the scalar product of 2 vectors
	return Vector(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
Vector operator-(Vector v1, Vector v2)
{// An overloaded operator - to return the difference of 2 vectors
	return Vector(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
Vector operator-(Vector v1)
{// An overloaded operator - to return the negation of a single vector
	return Vector(-v1.x(), -v1.y(), -v1.z());
}
bool operator==(Vector v1, Vector v2)
{
	if (v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z())
	{
		return true;
	}
	return false;
}
bool operator!=(Vector v1, Vector v2)
{
	return !(v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z());
}
Vector operator*(int scale, Vector v1)
{// An overloaded operator * to return the product of a int scalar by a vector
	return Vector(v1.x() * scale, v1.y() * scale, v1.z() * scale);
}
Vector operator*(float scale, Vector v1)
{// An overloaded operator * to return the product of a float scalar by a vector
	return Vector(v1.x() * scale, v1.y() * scale, v1.z() * scale);
}
Vector operator*(double scale, Vector v1)
{// An overloaded operator * to return the product of a double scalar by a vector
	return Vector(v1.x() * scale, v1.y() * scale, v1.z() * scale);
}
Vector operator ^(Vector v1, Vector v2)
{// An overloaded operator ^ to return the vector product of 2 vectors
	return Vector(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
}
double Vector::dotProduct(Vector v1)
{
	double dotProduct = (m_x * v1.x()) + (m_y * v1.y()) + (m_z * v1.z());//getting the dot product using the formula
	return dotProduct;//returning the value
}
//Method to find the crossproduct
//Using the forumla y1(z2) - z1(y2),z1(x2) - x1(z2), x1(y2) - y(x2) to find the cross product between 2 vectors
Vector Vector::crossProduct(Vector v1)
{
	return ((m_y * v1.z()) - (m_z * v1.y()), (m_z * v1.x()) - (m_x * v1.z()), (m_x * v1.y()) - (m_y * v1.x()));//returning the new cross pro vector
}
double Vector::angleBetween(Vector v1)
{
	{
		double lengthVec1 = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);//finding the length of vec1
		double lengthVec2 = sqrt(v1.x() * v1.x() + v1.y() * v1.y() + v1.z() * v1.z());//finding the length of vec2
		double dotProduct = (m_x * v1.x()) + (m_y * v1.y()) + (m_z * v1.z());//finding the dot product
		double radians = acos(dotProduct / (lengthVec1 * lengthVec2));//finding the radians
		double degrees = radians * 180 / m_pi;//formula to convert radians to degrees

		return degrees;//returning the double degrees
	}
}
Vector Vector::unit()
{
	double length = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

	m_x = m_x / length;
	m_y = m_y / length;
	m_z = m_z / length;

	return Vector(m_x, m_y, m_z);
}
Vector Vector::parallelComponent(Vector v1)
{

	float dotProduct = (m_x * v1.x()) + (m_y * v1.y()) + (m_z * v1.z());//finding the dot product
	float length = (m_x * m_x + m_y * m_y + m_z * m_z);//finding the length doesnt need math.sqrt because they are cancelled out later

	return Vector((dotProduct / length) * m_x, (dotProduct / length) * m_y, (dotProduct / length) * m_z);//returning the vector 
}
Vector Vector::perpendicularComponent(Vector v1)
{

	float dotProduct = (m_x * v1.x()) + (m_y * v1.y()) + (m_z * v1.z());//finding the dot product
	float length = (m_x * m_x + m_y * m_y + m_z * m_z);//finding the length doesnt need math.sqrt because they are cancelled out later

	return Vector(v1.x() - (dotProduct / length) * m_x, v1.y() - (dotProduct / length) * m_y, v1.z() - (dotProduct / length) * m_z);//returning the Perpendicular vectors to the main class
}
Vector Vector::scale(float scale)
{
	return Vector(m_x * scale, m_y * scale, m_z * scale);
}
void Vector::FlipX()//making the x negative
{
	m_x = -m_x;
}
void Vector::FlipY()//making the y negative
{
	m_y = -m_y;
}
double Vector::distance(Vector v1, Vector v2)
{
	return sqrt((v2.x() - v1.x()) * (v2.x() - v1.x()) + (v2.y() - v1.y()) * (v2.y() - v1.y()) + (v2.z() - v1.z()) * (v2.z() - v1.z()));
}
std::string Vector::toString()
{
	return "(" + std::to_string(m_x) + "," + std::to_string(m_y) + "," + std::to_string(m_z) + ")";
}