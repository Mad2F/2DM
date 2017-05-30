#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include <vector>
#include <algorithm>


//Declarations of all classes that will be used.
class Shape;
class Segment;
class Circle;
class Bord;

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


	//Ideas for Shapes and Movements : we need at each run to update the position and speed of the object
	virtual void update(Point) {};

	Point getPosition() { return m_position; };
	Point getSpeed() { return m_speed; }
	
protected:
	Point m_speed;
	Point m_position;
	int m_ID; //Should we give them some ID so that we can recognise them in case of problem/bug ?


};


class Circle : public Shape {
public:
	//constructors
	Circle();
	Circle(int);
	Circle(Point, int);
	Circle(Point A, Point B);
	Circle(Segment S);

	//Getters
	Point getCenter() { return m_center; }
	float getRadius() { return m_radius; }

	float distance(Circle*);
	bool collideWith(Circle*);
	bool touch(Circle*);
	Point getNormal(Circle*);
	Point getNormal(Segment*);

	//Update speed according to normal
	void updateSpeed(Point);

protected:
	float m_radius;
	Point m_center;
};

class Segment : public Shape
{

//Note : The class will regroup both Segment and Vectors... See if it has to be changed later.
public:
	Segment();
	Segment(Point A, Point B);

	std::vector<Point> getPoints() { return m_Points;  }

	double length();

	//Assert that the Segment is correctly living (ie has two points)
	bool hasTwoPoints();
	
	//returns True if the point is on the segment
	bool isOnSegment(Point* pPoint);
	//Returns the shortest distance from a given point to the segment
	double distance(Point* pPoint);	
	//Returns a pointer to the intersection with another segment (nullptr if the segments do not intersect)
	Point intersectWith(Segment* pSegment);

	Point projection(Point* pPoint);

	bool collideWith(Circle* pCircle);

	//Get normal vector
	Point getNormal(Shape*) { return getNormal(); };
	Point getNormal();
	//Get tangent Vector
	Point getTangent();

	//Update
	void update(Point N) {};

protected:
	//should contain 2 points
	std::vector<Point> m_Points;
};

class Bord : public Segment
{
	Bord() {};
};


#endif