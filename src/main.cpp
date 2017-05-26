#include <iostream>
#include<SFML/Window.hpp>
#include "shape.h"
#include "World.h"
#include "button.h"

const int W = 800;
const int H = 600;

int main(int argc, char** argv) {
	//Create window
	sf::RenderWindow window(sf::VideoMode(W, H), "My window");
	//Create mouse
	sf::Mouse mouse;
	//Configure window
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	//Create one play button and 3 text buttons
	Button b = Button(0, 0);
	Button b1 = Button(1, 0);
	Button b2 = Button(1, 1);
	Button b3 = Button(1, 2);

	//Create an empty white rectangle
	sf::RectangleShape sim(sf::Vector2f(575, 575));
	sim.setFillColor(sf::Color().White);
	sim.setPosition(10, 10);

	//get coefficients of height and width if the window is become bigger or smaller
	//Because shapes are referenced only in local frame
	float coeffX = 1;
	float coeffY = 1;
	
	// program runs until the window is closed
	while (window.isOpen())
	{
		//get a boolean if the mouse was just clicked on play button (less calculation)
		bool justClick = false;

		// check events since last iteration
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the window is resized, the coefficient have to be recalculated for correct click detection.
			if (event.type == sf::Event::Resized) {
				coeffX = float(W) / float(window.getSize().x);
				coeffY = float(H) / float(window.getSize().y);
			}
			//If the mouse is clicked, check if the click affects one of the buttons
			if (mouse.isButtonPressed(sf::Mouse::Left)) {
				//Get local position of mouse
				sf::Vector2i position = sf::Mouse::getPosition(window);

				//update position of mouse
				int posX = round(coeffX * position.x);
				int posY = round(coeffY * position.y);
				//Check all buttons and click accordingly
				if (b.isClicked(posX, posY)) { b.click(); justClick = true; }
				if (b1.isClicked(posX, posY)) { b1.click(); }
				if (b2.isClicked(posX, posY)) { b2.click(); }
				if (b3.isClicked(posX, posY)) { b3.click(); }
			}
			//If the event type is a closure, close
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//If the play button is clicked block the other buttons
		if (justClick) {
			if (justClick && b.isClicked()) {
				b1.block();
				b2.block();
				b3.block();
			}
			//Else unblock them
			else {
				b1.unblock();
				b2.unblock();
				b3.unblock();
			}
		}

		//Clear to gray
		window.clear(sf::Color(145,145,145,255));
		//Draw simulation window
		window.draw(sim);
		//Draw sprites and text
		window.draw(b.getSprite());
		window.draw(b1.getSprite());
		window.draw(b2.getSprite());
		window.draw(b3.getSprite());
		window.draw(b.getText());
		window.draw(b1.getText());
		window.draw(b2.getText());
		window.draw(b3.getText());
		//Display
		window.display();
	}
	return 0;
}