#include <iostream>
#include<SFML/Window.hpp>
#include "shape.h"
#include "World.h"
#include "gui.h"


int main(int argc, char** argv) {
	gui GUI;
	GUI.masterLoop();
	return 0;
}