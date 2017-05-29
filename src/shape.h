#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"
#include <vector>


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

	//should we also have some sort of "Assert function on the Shapes to ensure after each run the coherence of our world ?
	virtual bool own_assert() { return true;  }


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
	int getRadius() { return m_radius; }

	int distance(Circle*);
	bool collideWith(Circle*);
	bool touch(Circle*);
	Point getNormal(Circle*);
	Point getNormal(Segment*);
	//Update speed according to normal
	void update(Point);

protected:
	int m_radius;
	Point m_center;
};

class Segment : public Shape
{

//Note : The class will regroup both Segment and Vectors... See if it has to be changed later.
public:
	Segment();
	Segment(Point A, Point B, bool isvector = false);

	std::vector<Point> getPoints() { return m_Points;  }

	int length();

	//Assert that the Segment is correctly living (ie has two points)
	bool own_assert();
	
	//return true if the point is above the Segment (AB) assuming that the segment is horizontal A left B right
	bool isAbove(Point* pPoint);
	
	//returns True if the point is on the segment
	bool isOnSegment(Point* pPoint);

	//Returns a pointer to the intersection with another segment (nullptr if the segments do not intersect)
	Point* intersectWith(Segment* pSegment);

	//Get normal vector
	Point getNormal(Shape*) { return getNormal(); };
	Point getNormal();

	//Update
	void update(Point N) {};

protected:
	//should contain 2 points
	std::vector<Point> m_Points;
	//False if the Segment is only a Segment, True if the direction has to be taken into account (then from first to second point)
	bool m_isVector;
};

class Bord : public Segment
{
	Bord() {};
};


#endif