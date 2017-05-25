#include "shape.h"


//Circle related functions
Circle::Circle() :m_center(Point()), m_radius(1) {}

Circle::Circle(int R) : m_center(Point()), m_radius(R) {}

Circle::Circle(Point C, int R) : m_center(C), m_radius(R) {}

int Circle::distance(Circle* pCircle)
{
	return m_center.distance(&pCircle->getCenter()) - m_radius;
}


bool Circle::collideWith(Circle* pCircle)
{
	return distance(pCircle) <= 0;
}

bool Circle::touch(Circle* pCircle)
{
	return distance(pCircle) == 0;
}