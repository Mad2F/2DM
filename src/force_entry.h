#ifndef FORCE_ENTRY_H
#define FORCE_ENTRY_H

#include <SFML\Graphics.hpp>
#include <cassert>
#include <iostream>
#include "user_input.h"

class force_entry {
public:
	force_entry(int pos, sf::Font* font);
	~force_entry() {};
	sf::Text getText();
	sf::RectangleShape getRectangle();
	sf::Text getLegend();
	void setText(std::string s) { text.setString(s); };

private:
	sf::Text text;
	sf::RectangleShape rect;
	sf::Text legend;
};

#endif //Force_entry.h