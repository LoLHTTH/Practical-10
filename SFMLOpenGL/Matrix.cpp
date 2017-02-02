#include "Matrix.h"

Matrix::Matrix(double a11, double a12, double a13,
			   double a21, double a22, double a23,
			   double a31, double a32, double a33) :
	m_a11(a11), m_a12(a12), m_a13(a13),
	m_a21(a21), m_a22(a22), m_a23(a23),
	m_a31(a31), m_a32(a32), m_a33(a33)
{
	pi = cos(-1);
}
Matrix::Matrix(Vector row1, Vector row2, Vector row3) :
	m_a11(row1.x()), m_a12(row1.y()), m_a13(row1.z()),
	m_a21(row2.x()), m_a22(row2.y()), m_a23(row2.z()),
	m_a31(row3.x()), m_a32(row3.y()), m_a33(row3.z())
{
	pi = cos(-1);
}
double Matrix::a11()
{
	return m_a11;
}
double Matrix::a12()
{
	return m_a12;
}
double Matrix::a13()
{
	return m_a13;
}
double Matrix::a21()
{
	return m_a21;
}
double Matrix::a22()
{
	return m_a22;
}
double Matrix::a23()
{
	return m_a23;
}
double Matrix::a31()
{
	return m_a31;
}
double Matrix::a32()
{
	return m_a32;
}
double Matrix::a33()
{
	return m_a33;
}

double Matrix::determinant(Matrix m1)
{
	return m1.a11() * m1.a22() * m1.a33() - m1.a11() * m1.a32() * m1.a23() 
		 + m1.a21() * m1.a32() * m1.a13() - m1.a31() * m1.a22() * m1.a13() 
		 + m1.a31() * m1.a12() * m1.a23() - m1.a21() * m1.a12() * m1.a33();
}
Vector operator*(Matrix m1, Vector v1)
{// An overloaded operator * to return the  product of the matrix by a vector
	return Vector
	   ((m1.a11() * v1.x()) + (m1.a12() * v1.y()) + (m1.a13() * v1.z()),
		(m1.a21() * v1.x()) + (m1.a22() * v1.y()) + (m1.a23() * v1.z()),
		(m1.a31() * v1.x()) + (m1.a32() * v1.y()) + (m1.a33() * v1.z()));
}
Matrix operator*(double scale, Matrix m1)
{// An overloaded operator * to return the  product of the matrix by a scalar
	return Matrix(m1.a11() * scale, m1.a12() * scale, m1.a13() * scale,
				  m1.a21() * scale, m1.a22() * scale, m1.a23() * scale,
				  m1.a31() * scale, m1.a32() * scale, m1.a33() * scale);
}
Matrix Matrix::transpose(Matrix m1)
{// a method to transpose a given matrix
	return Matrix(m1.a11(), m1.a21(), m1.a31(),
				  m1.a12(), m1.a22(), m1.a32(),
				  m1.a13(), m1.a23(), m1.a33());
}
Vector Matrix::row(int i)
{// a method to return as Row as vector3 0 == first row, default == last row
	switch (i)
	{
	case 0:
		return Vector(m_a11, m_a12, m_a13);
	case 1:
		return Vector(m_a21, m_a22, m_a23);
	case 2:
	default:
		return Vector(m_a31, m_a32, m_a33);
	}
}
Matrix operator+(Matrix m1, Matrix m2)
{// An overloaded operator + to return the  sum of two matrix 
	return Matrix(m1.a11() + m2.a11(), m1.a12() + m2.a12(), m1.a13() + m2.a13(),
				  m1.a21() + m2.a21(), m1.a22() + m2.a22(), m1.a23() + m2.a23(),
				  m1.a31() + m2.a31(), m1.a32() + m2.a32(), m1.a33() + m2.a33());
}
Matrix operator*(Matrix m1, Matrix m2)
{// An overloaded operator * to return the  product of two matrix

	return Matrix(m1.a11() * m2.a11() + m1.a12() * m2.a21() + m1.a13() * m2.a31(),
				  m1.a11() * m2.a12() + m1.a12() * m2.a22() + m1.a13() * m2.a32(),
				  m1.a11() * m2.a13() + m1.a12() * m2.a23() + m1.a13() * m2.a33(),

				  m1.a21() * m2.a11() + m1.a22() * m2.a21() + m1.a23() * m2.a31(),
				  m1.a21() * m2.a12() + m1.a22() * m2.a22() + m1.a23() * m2.a32(),
				  m1.a21() * m2.a13() + m1.a22() * m2.a23() + m1.a23() * m2.a33(),

				  m1.a31() * m2.a11() + m1.a32() * m2.a21() + m1.a33() * m2.a31(),
				  m1.a31() * m2.a12() + m1.a32() * m2.a22() + m1.a33() * m2.a32(),
				  m1.a31() * m2.a13() + m1.a32() * m2.a23() + m1.a33() * m2.a33());
}
Matrix operator-(Matrix m1, Matrix m2)
{// An overloaded operator - to return the  difference of two matrix

	return Matrix(m1.a11() - m2.a11(), m1.a12() - m2.a12(), m1.a13() - m2.a13(),
				  m1.a21() - m2.a21(), m1.a22() - m2.a22(), m1.a23() - m2.a23(),
				  m1.a31() - m2.a31(), m1.a32() - m2.a32(), m1.a33() - m2.a33());
}
Matrix operator-(Matrix m1)
{// An overloaded operator - to return the  difference of two matrix

	return Matrix(-m1.a11(), -m1.a12(), -m1.a13(),
				  -m1.a21(), -m1.a22(), -m1.a23(),
				  -m1.a31(), -m1.a32(), -m1.a33());
}
Vector Matrix::column(int i)
{// a method to return as column as vector3 0 == first column, default == last column
	switch (i)
	{
	case 0:
		return Vector(m_a11, m_a21, m_a31);
	case 1:
		return Vector(m_a12, m_a22, m_a32);
	case 2:
	default:
		return Vector(m_a13, m_a23, m_a33);
	}
}
Matrix Matrix::inverse(Matrix m1)
{// method to return the inverse of a matrix if exists else zero vector
	double det = determinant(m1);
	if (det == 0)
		return Matrix();
	else
	{
		double scale = 1 / det;

		return Matrix(scale * (m1.a22() * m1.a33() - m1.a23() * m1.a32()), scale * (m1.a13() * m1.a32() - m1.a12() * m1.a33()), scale * (m1.a12() * m1.a23() - m1.a13() * m1.a22()),
					  scale * (m1.a23() * m1.a31() - m1.a21() * m1.a33()), scale * (m1.a11() * m1.a33() - m1.a13() * m1.a31()), scale * (m1.a13() * m1.a21() - m1.a11() * m1.a23()),
					  scale * (m1.a21() * m1.a32() - m1.a22() * m1.a31()), scale * (m1.a12() * m1.a31() - m1.a11() * m1.a32()), scale * (m1.a11() * m1.a22() - m1.a12() * m1.a21()));
	}
}
Matrix Matrix::rotation(float angle)
{
	double radians = pi / 180 * angle;
	m_a11 = cos(radians);
	m_a12 = sin(radians);
	m_a13 = 0;
	m_a21 = -sin(radians);
	m_a22 = cos(radians);
	m_a23 = 0;
	m_a31 = 0;
	m_a32 = 0;
	m_a33 = 1;

	return Matrix(m_a11,m_a12,m_a13,
				  m_a21,m_a22,m_a23,
				  m_a31,m_a32,m_a33);
}
Matrix Matrix::translate(float dx, float dy)
{
	m_a11 = 1;
	m_a12 = 0;
	m_a13 = dx;
	m_a21 = 0;
	m_a22 = 1;
	m_a23 = dy;
	m_a31 = 0;
	m_a32 = 0;
	m_a33 = 1;

	return Matrix(m_a11, m_a12, m_a13,
				  m_a21, m_a22, m_a23,
				  m_a31, m_a32, m_a33);
}
Matrix Matrix::scale(float dx, float dy)
{
	m_a11 = (double)dx / 100;
	m_a12 = 0;
	m_a13 = 0;
	m_a21 = 0;
	m_a22 = (double)dy / 100;
	m_a23 = 0;
	m_a31 = 0;
	m_a32 = 0;
	m_a33 = 1;

	return Matrix(m_a11, m_a12, m_a13,
		m_a21, m_a22, m_a23,
		m_a31, m_a32, m_a33);
}
Matrix Matrix::rotationX(float _angle)
{
	double radians = pi / 180 * _angle;
	m_a11 = 1;
	m_a12 = 0;
	m_a13 = 0;
	m_a21 = 0;
	m_a22 = cos(radians);
	m_a23 = -sin(radians);
	m_a31 = 0;
	m_a32 = sin(radians);
	m_a33 = cos(radians);

	return Matrix(m_a11, m_a12, m_a13,
				  m_a21, m_a22, m_a23,
				  m_a31, m_a32, m_a33);
}
Matrix Matrix::rotationY(float _angle)
{
	double radians = pi / 180 * _angle;

	m_a11 = cos(radians);
	m_a12 = 0;
	m_a13 = sin(radians);
	m_a21 = 0;
	m_a22 = 1;
	m_a23 = 0;
	m_a31 = -sin(radians);
	m_a32 = 0;
	m_a33 = cos(radians);

	return Matrix(m_a11, m_a12, m_a13,
				  m_a21, m_a22, m_a23,
				  m_a31, m_a32, m_a33);
}
Matrix Matrix::rotationZ(float _angle)
{
	double radians = pi / 180 * _angle;

	m_a11 = cos(radians);
	m_a12 = -sin(radians);
	m_a13 = 0;
	m_a21 = sin(radians);
	m_a22 = cos(radians);
	m_a23 = 0;
	m_a31 = 0;
	m_a32 = 0;
	m_a33 = 1;

	return Matrix(m_a11, m_a12, m_a13,
				  m_a21, m_a22, m_a23,
				  m_a31, m_a32, m_a33);
}

Matrix Matrix::scale3D(float dx)
{
	m_a11 = (double)dx / 100;
	m_a12 = 0;
	m_a13 = 0;
	m_a21 = 0;
	m_a22 = (double)dx / 100;
	m_a23 = 0;
	m_a31 = 0;
	m_a32 = 0;
	m_a33 = (double)dx / 100;

	return Matrix(m_a11, m_a12, m_a13,
				  m_a21, m_a22, m_a23,
				  m_a31, m_a32, m_a33);
}