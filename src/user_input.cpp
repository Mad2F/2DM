#include "user_input.h"

user_input::user_input(std::string message, sf::Font* font) {
	//Configure window
	sf::VideoMode vm(W, H);
	window.create(vm, "User input");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	//Create an empty white rectangle
	sim.setSize(sf::Vector2f(480, 40));
	sim.setFillColor(sf::Color().White);
	sim.setPosition(10, 50);

	//text_out
	text_out.setString(message);
	text_out.setFont(*font);
	text_out.setColor(sf::Color().Black);
	text_out.setCharacterSize(16);
	text_out.setPosition(10, 10);

	//text_in
	text_in.setFont(*font);
	text_in.setColor(sf::Color().Black);
	text_in.setCharacterSize(16);
	text_in.setPosition(15, 60);

	// program runs until the window is closed
	while (window.isOpen())
	{
		//get a boolean if the mouse was just clicked on play button (less calculation)
		bool justClicked = false;

		// check events since last iteration
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the event type is a closure, close
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128 && event.text.unicode != 10 && event.text.unicode != 13) {
					input += static_cast<char>(event.text.unicode);
					text_in.setString(input);
				}
				if (event.text.unicode == 10 || event.text.unicode == 13) {
					window.close();
				}
			}
		}
		//Display
		window.clear(sf::Color(145, 145, 145, 255));
		window.draw(sim);
		window.draw(text_out);
		window.draw(text_in);
		window.display();
	}
}

int user_input::getIntInput() {
	//Check if the string is empty or if the first digit is not a digit
	if (input.empty() || !isdigit(input[0])) return -1;
	//Goes through the string and stops if one character is not a digit
	char * p;
	long int val = strtol(input.c_str(), &p, 10);
	if (*p != 0) return -1;
	return int(val);
}

float user_input::getFloatInput() {
	//Check if the string is empty or if the first digit is not a digit
	if (input.empty() || !isdigit(input[0])) return -1;
	//Goes through the string and stops if one character is not a digit
	char * p;
	long float val = strtod(input.c_str(), &p);
	if (*p != 0) return -1;
	return float(val);
}