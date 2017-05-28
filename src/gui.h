#ifndef GUI_H
#define GUI_H

#include "button.h"

class gui {
public:
	gui();
	~gui() {};
	void resize();
	sf::Vector2i getMouse();
	bool checkButtons(sf::Vector2i);
	void playpauseButtons(bool);
	void display();
	void masterLoop();

private:
	sf::RenderWindow window;
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