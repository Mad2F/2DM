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

	//Assertions to ensure that all shapes are contained within the borders of the world
	//TODO
	bool isInside(Shape*) {return true;}
	bool allShapesAreInside();






protected:
	std::vector<Shape*> m_shapes;
	std::vector<Bord*> m_encastred;
	Environment* m_Envir;

};

#endif // !WORLD_H