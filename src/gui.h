#ifndef GUI_H
#define GUI_H

#include <sstream>
#include <iomanip>

#include "button.h"
#include "shape.h"
#include "force_entry.h"

class gui {
public:
	//Constructor and destructor initializes everything
	gui();
	~gui() {};
	//Resize by recalculating the coefficients
	void resize();
	//Get Mouse coordinates
	sf::Vector2i getMouse();
	//Check if buttons are activated
	bool checkButtons(sf::Vector2i);
	//Block and unblock buttons
	void playpauseButtons(bool, int);
	//Display buttons and text
	void display();
	//Control loop
	void masterLoop();
	//vector with necessary objects
	std::vector<Circle> collection;
	//vector with necessary forces
	std::vector<Point> forces; 
	//list with colors to paint objects
	std::vector<sf::Color> colorcollection;
	//Size reference of universe
	int W_world = 1000;
	int H_world = 1000;
	//Update position of collection
	void update();
	//Add circle
	void addForm(int x, int y, int r);
	//Check text forces and return corresponding text force index
	int checkForceEntry(sf::Vector2i);
	void updateForceEntry(int);
	//Time rendering
	sf::Time time;

private:
	//Window
	sf::RenderWindow window;
	//default font
	sf::Font font;
	//Size
	int W = 800;
	int H = 600;
	//Create mouse
	sf::Mouse mouse;
	//Create one play button and 3 text buttons
	Button playB = Button(0,0);
	Button B1 = Button(1, 0);
	Button B2 = Button(1, 1);
	Button B3 = Button(1, 2);

	//Rectangle shape
	//Create an empty white rectangle
	sf::RectangleShape sim;

	//Rectangle shape for value of g and of wind
	force_entry G_Force = force_entry(1, &font);
	force_entry G_Dir = force_entry(2, &font);
	force_entry Wind_Force = force_entry(3, &font);
	force_entry Wind_Dir = force_entry(4, &font);

	//get coefficients of height and width if the window is become bigger or smaller
	//Because shapes are referenced only in local frame
	float coeffX = 1;
	float coeffY = 1;
};
#endif // CUSTOMWINDOW_H