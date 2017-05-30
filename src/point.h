#ifndef POINT_H
#define POINT_H

#include <cmath>
#include<stdexcept>

class Point {
public:
	double X;
	double Y;

	//Constructors
	Point();
	Point(double , double);
	~Point() {}
	
	Point normalize();
	double normL2();

	double distance();
	double distance(Point*);
	Point operator-(Point);
	Point operator+(Point);
	Point operator*(double);
	double operator*(Point);
	Point operator/(double);
	bool operator==(Point);

#define DUMMY Point(-1,-1)

};

#endif
