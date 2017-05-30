#include "World.h"


bool World::isInside(Shape* pShape)
{
	if (pShape)
	{
		Point C = pShape->getPosition();
		return (C.X > 0 && C.X < m_xMax && C.Y > 0 && C.Y < m_yMax);

	}

	return false;

}

void World::deleteOutsideShapes()
{
	for (auto shape = m_shapes.begin(); shape != m_shapes.end(); shape++)
	{
		if (!isInside(*shape))
		{
			delete *shape;
		}
	}
}