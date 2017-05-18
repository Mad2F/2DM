#include "shape.h"


//Circle related functions
Circle::Circle() :m_center(Point()), m_radius(1) {}

Circle::Circle(int R) : m_center(Point()), m_radius(R) {}

Circle::Circle(Point C, int R) : m_center(C), m_radius(R) {}
