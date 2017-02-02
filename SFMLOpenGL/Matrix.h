#pragma once
#include "Vector.h"
#include <cmath>
#include <string>

class Matrix
{
protected:
	double m_a11;
	double m_a12;
	double m_a13;
	double m_a21;
	double m_a22;
	double m_a23;
	double m_a31;
	double m_a32;
	double m_a33;
	double pi;
public:
	Matrix(double m_a11 = 0, double m_a12 = 0, double m_a13 = 0,
		   double m_a21 = 0, double m_a22 = 0, double m_a23 = 0,
		   double m_a31 = 0, double m_a32 = 0, double m_a33 = 0);
	Matrix(Vector row1, Vector row2, Vector row3);
	double a11(); double a12(); double a13();
	double a21(); double a22(); double a23();
	double a31(); double a32(); double a33();
	Matrix transpose(Matrix m1);
	double determinant(Matrix m1);
	Vector row(int i);
	Vector column(int i);
	Matrix inverse(Matrix m1);
	Matrix rotation(float angle);
	Matrix translate(float dx, float dy);
	Matrix scale(float dx, float dy);
	Matrix rotationX(float angle);
	Matrix rotationY(float angle);
	Matrix rotationZ(float angle);
	Matrix scale3D(float dx);
};

Vector operator*(Matrix m1, Vector v1);
Matrix operator*(double scale, Matrix m1);
Matrix operator*(Matrix m1, Matrix m2);
Matrix operator+(Matrix m1, Matrix m2);
Matrix operator-(Matrix m1, Matrix m2);
Matrix operator-(Matrix m1);
