#include "point.h"

//default constructor returns O
Point::Point() :X(0), Y(0) {};

Point::Point(int x, int y) :X(x), Y(y) {};

int Point::distance(Point* pPoint)
{
	int dX = X - pPoint->X;
	int dY = Y - pPoint->Y;
	return std::sqrt(dX*dX + dY*dY);
}


