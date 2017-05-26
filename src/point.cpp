#include "point.h"

//default constructor returns O
Point::Point() :X(0), Y(0) {};

Point::Point(double x, double y) :X(x), Y(y) {};

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

double Point::normL2() {
	return distance(&Point(0, 0));
}

Point Point::operator/(double k) {
	if (k == 0){
		throw std::logic_error("division by 0 not possible");
	}
	return operator*(1 / k);
}