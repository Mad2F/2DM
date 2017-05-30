#ifndef WORLD_H
#define WORLD_H

#include "shape.h"
#include "environment.h"
#include <vector>

class World

{
public:
	World() {};
	
	//Assertions to ensure wolrd is living
	bool hasEnvironment() { return (m_Envir); }
	bool hasBords() { return (m_encastred.empty()); }
	bool isFunctional() { return (hasEnvironment() && hasBords()); }

	//Check if a shape is within the border of the world
	bool isInside(Shape*);

	//Remove the shapes that are outside of the world
	void deleteOutsideShapes();






protected:
	std::vector<Shape*> m_shapes;
	std::vector<Bord*> m_encastred;
	Environment* m_Envir;

	int m_xMax;
	int m_yMax;



};

#endif // !WORLD_H