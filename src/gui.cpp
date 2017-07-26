#include "gui.h"

//Constructor
gui::gui() {
	//Configure window
	sf::VideoMode vm(W, H);
	window.create(vm, "My interface");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	//Set font
	//Set the police
	if (!font.loadFromFile(path_to_police)) {
		throw std::logic_error("Unable to open police");
	}

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

	//Add initial void forces
	forces.push_back(Point(0, 9.81));
	forces.push_back(Point(0, 0));
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
		user_input UI("Enter radius as int", &font);
		radius = UI.getIntInput();
		while (radius < 0) {
			user_input UI("Enter radius as int AS AN INT PLEASE !", &font);
			radius = UI.getIntInput();
		}
		addForm(posX, posY, radius);
	}
	if (B2.isClicked(posX, posY)) { B2.click(); }
	if (B3.isClicked(posX, posY)) { B3.click(); }

	return justClick;
}

//Block and unblock the buttons
void gui::playpauseButtons(bool justClick, int ref) {
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
	//If text buttons clicked and simulation paused
	else if (ref != 0 && !playB.isClicked()) {
		updateForceEntry(ref);
	}
}

//Display everything
void gui::display() {
	//Clear to gray
	window.clear(sf::Color(145, 145, 145, 255));
	//Draw simulation window
	window.draw(sim);
	//Draw gvalue
	window.draw(G_Force.getRectangle());
	window.draw(G_Force.getText());
	window.draw(G_Force.getLegend());
	//Draw g angle
	window.draw(G_Dir.getRectangle());
	window.draw(G_Dir.getText());
	window.draw(G_Dir.getLegend());
	//Draw wind force
	window.draw(Wind_Force.getRectangle());
	window.draw(Wind_Force.getText());
	window.draw(Wind_Force.getLegend());
	//Draw Wind angle
	window.draw(Wind_Dir.getRectangle());
	window.draw(Wind_Dir.getText());
	window.draw(Wind_Dir.getLegend());
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
		Point center = it->getPosition() + it ->getCenter();
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
	//Reference for click in force entries
	int ref = 0;
	//Initialize clock
	sf::Clock clock;
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
				ref = checkForceEntry(mousePosition);
 			}
			//If the event type is a closure, close
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Unblock or block buttons
		playpauseButtons(justClicked, ref);
		ref = 0;
		//Get elapsed time
		time = clock.getElapsedTime();
		clock.restart();
		//Update positions of collection of circles
		if (playB.isClicked()) {
			update();
		}
		//Display
		display();
	}
}

//Update positions
void gui::update(){
	for (auto it = this->collection.begin(); it != this->collection.end(); ++it){
		Point SumF = Point(forces.at(0).X + forces.at(1).X, forces.at(0).Y + forces.at(1).Y);
		std::cout << forces.at(1).X << " " << forces.at(1).X << std::endl;
		it->update(time.asSeconds(), SumF);
	}
}

//Add a form to the vector
void gui::addForm(int x, int y, int r) {
	collection.push_back(Circle(Point(x, y), r));
}

//Check if there is a force entry change
int gui::checkForceEntry(sf::Vector2i MousePos) {
	if (G_Force.getRectangle().getGlobalBounds().contains(MousePos.x, MousePos.y)) {
		return 1;
	}
	if (G_Dir.getRectangle().getGlobalBounds().contains(MousePos.x, MousePos.y)) {
		return 2;
	}
	if (Wind_Force.getRectangle().getGlobalBounds().contains(MousePos.x, MousePos.y)) {
		return 3;
	}
	if (Wind_Dir.getRectangle().getGlobalBounds().contains(MousePos.x, MousePos.y)) {
		return 4;
	}
	return 0;
}

//Update the force entry
void gui::updateForceEntry(int index) {
	if (index != 0) {
		//Get text to display and reference to the force_entry class button corresponding
		std::string ind;
		force_entry* ref;
		switch (index) {
		case 1:
			ind = "g-force";
			ref = &G_Force;
			break;
		case 2:
			ind = "g-direction. The reference is vertical upright, in a trigonometric way.";
			ref = &G_Dir;
			break;
		case 3:
			ind = "wind force in N/m^2.";
			ref = &Wind_Force;
			break;
		case 4:
			ind = "wind direction. The reference is vertical upright, in a trigonometric way.";
			ref = &Wind_Dir;
			break;
		}
		//Take new value
		std::string message = "Enter new " + ind;
		user_input UI(message, &font);
		float X = UI.getFloatInput();
		while (X < 0) {
			message += " AS A FLOAT PLEASE !";
			user_input UI(message, &font);
			X = UI.getFloatInput();
		}
		//If even, it's an angle
		if (index % 2 == 0) {
			int Val = int(X) % 360;
			ref->setText(std::to_string(Val) + " °");
			//If g angle
			if (index == 2) {
				float NormG = forces.at(0).normL2();
				forces.at(0).X = NormG * cos(Val);
				forces.at(0).Y = NormG * sin(Val);
			}
			//Else wind
			if (index == 4) {
				float NormW = forces.at(1).normL2();				
				forces.at(1).X = NormW * cos(Val);
				forces.at(1).Y = NormW * sin(Val);
			}
		}
		//Else it's a float (set precision of 2 numbers)
		else {
			std::ostringstream out;
			out << std::setprecision(2) << X;
			std::string Val = out.str();
			ref->setText(Val + "N/m^2");
			//If g angle
			if (index == 1) {
				float cosG = forces.at(0).Y == 0 ? 0 : forces.at(0).X / forces.at(0).Y;
				float sinG = forces.at(0).X == 0 ? 0 : forces.at(0).Y / forces.at(0).X;
				forces.at(0).X = X * cosG;
				forces.at(0).Y = X * sinG;
			}
			//Else wind
			if (index == 3) {
				float cosG = forces.at(1).Y == 0 ? 0 : forces.at(1).X / forces.at(1).Y;
				float sinG = forces.at(1).X == 0 ? 0 : forces.at(1).Y / forces.at(1).X;
				if (cosG == 0 && sinG == 0) {
					cosG = 1;
				}
				forces.at(1).X = X * cosG;
				forces.at(1).Y = X * sinG;
			}
		}
	}
}