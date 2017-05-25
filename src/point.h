#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
public:
	int X;
	int Y;

	//Constructors
	Point();
	Point(int , int);
	~Point() {}

	int distance(Point*);

};

#endif
