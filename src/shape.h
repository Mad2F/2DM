#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"

class Shape {
public:

	Shape() {}
	virtual ~Shape() {}

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
#endif
