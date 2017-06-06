#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SFML\Graphics.hpp>
#include <iostream>
class user_input {
public:
	user_input(std::string message, sf::Font* font);
	~user_input() {}
	std::string getStringInput() { return input; }
	int getIntInput();
	float getFloatInput();

private:
	//Window
	sf::RenderWindow window;
	//default font
	sf::Font font;
	//Size
	int W = 500;
	int H = 100;

	//Rectangle shape
	//Create an empty white rectangle
	sf::RectangleShape sim;

	//text display
	sf::Text text_out;
	sf::Text text_in;

	//User input
	std::string input = "";
};

#endif //Force_entry.h
