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
	virtual int distance(Shape *)		{ return -1; };
	virtual bool collideWith(Shape *)	{ return false; };
	virtual bool touch(Shape *)			{ return false; };
};

class Circle : public Shape {
public:
	//constructors
	Circle();
	Circle(int);
	Circle(Point, int);

	Point getCenter() { return m_center; }
	int getRadius() { return m_radius; }

	int distance(Circle*);

	bool collideWith(Circle*);
	bool touch(Circle*);

protected:
	int m_radius;
	Point m_center;
};


class Bord : public Shape
{
	Bord() {};
};


#endif