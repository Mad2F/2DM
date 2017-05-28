#include "gui.h"

gui::gui() {
	//Configure window
	sf::VideoMode vm(W, H);
	window.create(vm, "My interface");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	//Create an empty white rectangle
	sim.setSize(sf::Vector2f(575, 575));
	sim.setFillColor(sf::Color().White);
	sim.setPosition(10, 10);

	display();
}

void gui::resize() {
	coeffX = float(W) / float(window.getSize().x);
	coeffY = float(H) / float(window.getSize().y);
}

sf::Vector2i gui::getMouse() {
	//Get local position of mouse
	sf::Vector2i position = sf::Mouse::getPosition(window);

	//update position of mouse
	int posX = round(coeffX * position.x);
	int posY = round(coeffY * position.y);
	return sf::Vector2i(posX, posY);
}

bool gui::checkButtons(sf::Vector2i mousePosition) {
	int posX = mousePosition.x;
	int posY = mousePosition.y;
	bool justClick = false;
	//Check all buttons and click accordingly
	if (playB.isClicked(posX, posY)) { playB.click(); justClick = true; }
	if (B1.isClicked(posX, posY)) { B1.click(); }
	if (B2.isClicked(posX, posY)) { B2.click(); }
	if (B3.isClicked(posX, posY)) { B3.click(); }

	return justClick;
}

void gui::playpauseButtons(bool justClick) {
	//If the play button is clicked block the other buttons
	if (justClick) {
		if (justClick && playB.isClicked()) {
			B1.block();
			B2.block();
			B3.block();
		}
		//Else unblock them
		else {
			B1.unblock();
			B2.unblock();
			B3.unblock();
		}
	}
}

void gui::display() {
	//Clear to gray
	window.clear(sf::Color(145, 145, 145, 255));
	//Draw simulation window
	window.draw(sim);
	//Draw sprites and text
	window.draw(playB.getSprite());
	window.draw(B1.getSprite());
	window.draw(B2.getSprite());
	window.draw(B3.getSprite());
	window.draw(playB.getText());
	window.draw(B1.getText());
	window.draw(B2.getText());
	window.draw(B3.getText());
	//Display
	window.display();
}

void gui::masterLoop() {
	// program runs until the window is closed
	while (window.isOpen())
	{
		//get a boolean if the mouse was just clicked on play button (less calculation)
		bool justClicked = false;

		// check events since last iteration
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the window is resized, the coefficient have to be recalculated for correct click detection.
			if (event.type == sf::Event::Resized) {
				resize();
			}
			//If the mouse is clicked, check if the click affects one of the buttons
			if (mouse.isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePosition = getMouse();
				justClicked = checkButtons(mousePosition);
			}
			//If the event type is a closure, close
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Unblock or block buttons
		playpauseButtons(justClicked);
		//Display
		display();
	}
}

