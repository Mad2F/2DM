#include "shape.h"

//-----------------------------------------------
//Circle related functions
Circle::Circle() :m_center(Point()), m_radius(1) {}

Circle::Circle(int R) : m_center(Point()), m_radius(R) {}

Circle::Circle(Point C, int R) : m_center(C), m_radius(R) {}

Circle::Circle(Point A, Point B)
{
	Point C = Point(0.5*(A.X + B.X), 0.5*(A.Y + B.Y));
	int R = 0.5*A.distance(&B);
	Circle(C, R);

}


Circle::Circle(Segment S)
{
	std::vector<Point> points = S.getPoints();
	Circle(points[0], points[1]);
}

int Circle::distance(Circle* pCircle)
{
	return m_center.distance(&pCircle->getCenter()) - m_radius - pCircle->getRadius();
}


bool Circle::collideWith(Circle* pCircle)
{
	return distance(pCircle) <= 0;
}

bool Circle::touch(Circle* pCircle)
{
	return distance(pCircle) == 0;
}

Point Circle::getNormal(Circle* pCircle) {
	Point U = getCenter() - pCircle->getCenter();
	return U / U.normL2();
}

Point Circle::getNormal(Segment* pSeg) {
	return pSeg->getNormal();
}

void Circle::update(Point N) {
	m_speed = m_speed - N * 2 * (m_speed*N);
}



//------------------------------------------------
//segment Relasted functions

Segment::Segment(Point A, Point B, bool isVector) : m_isVector(isVector)
{
	m_Points.push_back(A);
	m_Points.push_back(B);
}

bool Segment::own_assert()
{
	return m_Points.size() == 2;
}

int Segment::length()
{
	//Will return -1 if the Segment has less than two points...
	int d = own_assert() ? m_Points[0].distance(&m_Points[1]) : -1;
	return d;
}

bool Segment::isAbove(Point* pPoint)
{
//TODO
	return false;
}

bool Segment::isOnSegment(Point* pPoint)
{
//TODO
	return false;
}

Point* Segment::intersectWith(Segment* pSegment)
{
	//TODO
	return &Point();
}

Point Segment::getNormal() {
	Point U(-(m_Points[0].Y - m_Points[1].Y), m_Points[0].X - m_Points[1].X);
	return U / U.normL2();;
}