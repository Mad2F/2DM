#include "point.h"
//default constructor returns O
Point::Point() :X(0), Y(0) {};

Point::Point(double x, double y) :X(x), Y(y) {};




//-----------------------------------
//Operator Overloads
double Point::distance(Point* pPoint)
{
	double dX = X - pPoint->X;
	double dY = Y - pPoint->Y;
	return std::sqrt(dX*dX + dY*dY);
}

double Point::distance()
{
	return distance(&Point());
}

Point Point::operator-(Point p) {
	return Point(X - p.X, Y - p.Y);
}

Point Point::operator+(Point p) {
	return Point(X + p.X, Y + p.Y);
}

Point Point::operator*(double k) {
	return Point(k*X, k*Y);
}

double Point::operator*(Point p) {
	return (X*p.X + Y*p.Y);
}

bool Point::operator==(Point p)
{
	return (X == p.X && Y == p.Y);
}

double Point::normL2() {
	return distance(&Point(0, 0));
}

Point Point::operator/(double k) {
	if (k == 0){
		throw std::logic_error("division by 0 not possible");
	}
	return operator*(1 / k);
}

Point Point::normalize()
{
	return *this / normL2();
}

double Point::determinant(Point* pPoint)
{
	// Return Point ^ pPoint*
	return (X*pPoint->Y - Y*pPoint->X);
}