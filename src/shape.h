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
		int m_radius;
		Point m_center;
};
#endif
