#ifndef GUI_H
#define GUI_H

#include "button.h"
#include "shape.h"

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
	void playpauseButtons(bool);
	//Display buttons and text
	void display();
	//Control loop
	void masterLoop();
	//vector with necessary objects
	std::vector<Circle> collection;
	//list with colors to paint objects
	std::vector<sf::Color> colorcollection;
	//Size reference of universe
	int W_world = 1000;
	int H_world = 1000;
	//Update position of collection
	void update();
	//Add circle
	void addForm(int x, int y, int r);

private:
	//Window
	sf::RenderWindow window;
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

	//get coefficients of height and width if the window is become bigger or smaller
	//Because shapes are referenced only in local frame
	float coeffX = 1;
	float coeffY = 1;
};
#endif // CUSTOMWINDOW_H