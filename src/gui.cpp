#include "gui.h"

//Constructor
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

	//Set initially false shapes to display
	collection.push_back(Circle(Point(100, 150), 20));
	collection.push_back(Circle(Point(800, 450), 50));
	collection.push_back(Circle(Point(650, 800), 20));
	collection.push_back(Circle(Point(50, 500), 15));

	//Set colors
	colorcollection.push_back(sf::Color::Blue);
	colorcollection.push_back(sf::Color::Magenta);
	colorcollection.push_back(sf::Color::Red);
	colorcollection.push_back(sf::Color::Green);
	colorcollection.push_back(sf::Color::Yellow);
	colorcollection.push_back(sf::Color::Cyan);
	colorcollection.push_back(sf::Color::Black);
	colorcollection.push_back(sf::Color::Black + sf::Color::White);
	colorcollection.push_back(sf::Color::Yellow + sf::Color::Red);
	colorcollection.push_back(sf::Color::Blue + sf::Color::Red);
}

//Resize by updating the coefficient relative to the window
void gui::resize() {
	coeffX = float(W) / float(window.getSize().x);
	coeffY = float(H) / float(window.getSize().y);
}

//get mouse position
sf::Vector2i gui::getMouse() {
	//Get local position of mouse
	sf::Vector2i position = sf::Mouse::getPosition(window);

	//update position of mouse
	int posX = round(coeffX * position.x);
	int posY = round(coeffY * position.y);
	return sf::Vector2i(posX, posY);
}

//Check if any button is activated by given mouse position
bool gui::checkButtons(sf::Vector2i mousePosition) {
	int posX = mousePosition.x;
	int posY = mousePosition.y;
	bool justClick = false;
	//Check all buttons and click accordingly
	if (playB.isClicked(posX, posY)) { playB.click(); justClick = true; }
	if (B1.isClicked(posX, posY)) { 
		B1.click();
		int posX;
		int posY;
		int radius;
		bool CenterNotDefined = true;
		std::cout << "Click on position of the center of the new circle" << std::endl;
		while (CenterNotDefined) {
			if (mouse.isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePosition = getMouse();
				if (sim.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
					CenterNotDefined = false;
					posX = (mousePosition.x - sim.getPosition().x) * W_world / (sim.getSize().x * coeffX);
					posY = (mousePosition.y - sim.getPosition().y) * H_world / (sim.getSize().y * coeffY);
				}
			}
		}
		std::cout << "Enter Radius" << std::endl;
		std::cin >> radius;
		addForm(posX, posY, radius);
	}
	if (B2.isClicked(posX, posY)) { B2.click(); }
	if (B3.isClicked(posX, posY)) { B3.click(); }

	return justClick;
}

//Block and unblock the buttons
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

//Display everything
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
	int k = 0;
	for (std::vector<Circle>::iterator it = collection.begin(); it != collection.end(); ++it) {
		Point center = it->getCenter();
		int radius = it->getRadius();
		sf::Color c = colorcollection.at(k%10);
		sf::CircleShape Circle(radius * sim.getSize().x * coeffX / W_world);
		int cx = sim.getPosition().x + center.X * sim.getSize().x * coeffX / W_world;
		int cy = sim.getPosition().y + center.Y * sim.getSize().y * coeffY / H_world;
		Circle.setPosition(cx, cy);
		Circle.setFillColor(c);
		window.draw(Circle);
		k++;
	}
	//Display
	window.display();
}

//Control master loop
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

void gui::update(){}

void gui::addForm(int x, int y, int r) {
	collection.push_back(Circle(Point(x, y), r));
}
