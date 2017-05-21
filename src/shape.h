#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"

class Shape {
public:

	Shape() {}
	virtual ~Shape() {}

//-----------------------------------------
//Virtual generic functions
	
	//display the shape on screen
	virtual void display() {};
	//returns true if the shape collides with another given shape
	//TODO
	virtual bool collideWith(Shape *) { return false; };

};

class Circle : public Shape {
public:
	//constructors
	Circle();
	Circle(int);
	Circle(Point, int);
		
protected:
	int m_radius;
	Point m_center;
};


class Bord : public Shape
{
	Bord() {};
};


#endif