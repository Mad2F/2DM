#include "World.h"


bool World::allShapesAreInside()
{
	bool shapesInside = true;
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		shapesInside &= isInside(*it);
	}

	return shapesInside;

}