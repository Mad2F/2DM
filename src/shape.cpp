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

float Circle::distance(Circle* pCircle)
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

void Circle::updateSpeed(Point N) {
	m_speed = m_speed - N * 2 * (m_speed*N);
}

void Circle::update(float t, Point SumForces) {
	m_speed = m_speed + SumForces * t;
	if (m_speed.normL2() > 0.01){
	m_speed = m_speed - m_speed.normalize() * m_speed.normL2() * 0.005;
	}
	m_position = m_position + m_speed * t;
}


//------------------------------------------------
//segment Related functions

Segment::Segment(Point A, Point B)
{
	m_Points.push_back(A);
	m_Points.push_back(B);
}

bool Segment::hasTwoPoints()
{
	return m_Points.size() == 2;
}

double Segment::length()
{
	//Will return -1 if the Segment has less than two points...
	int d = hasTwoPoints() ? m_Points[0].distance(&m_Points[1]) : -1;
	return d;
}


bool Segment::collideWith(Circle* pCircle)
{
	if (pCircle)
	{
		Point C = pCircle->getCenter();
		double R = pCircle->getRadius();
		return distance(&C) < R;
	}
	return false;
}



Point Segment::intersectWith(Segment* pSegment)
{
	//Suppose that the first Segment is AB, the second CD, we look for the intersection E such as 
	//E = A + alpha (B-A) = C + beta (D-C)
	//All lines ^(B-A) gives A^(B-A) = C^(B-A) + beta (D-C)^(B-A) and gives beta
	Point
		A = m_Points[0],
		BminA = m_Points[1]-A,
		C = pSegment->getPoints()[0],
		DminC = pSegment->getPoints()[1]-C;
	
	double beta_num = ((A - C).determinant(&BminA));
	double beta_den = (DminC.determinant(&BminA));

	if (beta_den != 0)
	{
		double beta = beta_num / beta_den;
		if (beta >= 0 && beta <= 1)
			return (C + DminC*beta);
	}

	return DUMMY;
}

Point Segment::getNormal() {
	Point U(-(m_Points[0].Y - m_Points[1].Y), m_Points[0].X - m_Points[1].X);
	return U / U.normL2();;
}

Point Segment::getTangent()
{
	Point T = hasTwoPoints() ? m_Points[1] - m_Points[0] : Point() ;
	return (T == Point() ? Point() : T / T.normL2());
}

Point Segment::projection(Point* pPoint)
{
	//If we want to calculate the projection D of C on AB
	//We write the following equations :
	// AB.CD = 0 and D = A + alpha * (B-A)
	//If alpha is in [0;1] then D is indeed on the segment, else it falls outside on the line.
	if (length() > 0)
	{
		Point T = m_Points[1] - m_Points[0];
		double L = length()*length();
		double alpha = (T.X*(pPoint->X - m_Points[0].X) + T.Y*(pPoint->Y - m_Points[0].Y)) / L;
		if (alpha >= 0 && alpha <= 1)
			return m_Points[0] + T*alpha;
	}
	return DUMMY;
}

bool Segment::isOnSegment(Point* pPoint)
{
	//The point is on the segment if and only if
	//its projection on the segment is itself
	return *pPoint == projection(pPoint);
}

double Segment::distance(Point* pPoint)
{
	//Either the distance between the point and its projection on the segment if it exists
	//Or the distance to the closest point of the segment if it doesn't
	Point P = projection(pPoint);
	if (P == DUMMY)
		return std::min(pPoint->distance(&m_Points[0]), pPoint->distance(&m_Points[0]));
	else
		return pPoint->distance(&P);
}