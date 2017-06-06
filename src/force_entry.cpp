#include "force_entry.h"

//Constructor
force_entry::force_entry(int pos, sf::Font* font) {
	try {
		//General text values
		text.setFont(*font);
		text.setCharacterSize(16);
		text.setColor(sf::Color().Black);
		//General legend values
		legend.setFont(*font);
		legend.setCharacterSize(16);
		legend.setColor(sf::Color().Black);
		//General rectangle values
		rect.setSize(sf::Vector2f(75, 30));
		rect.setFillColor(sf::Color().White);
		//Specific to position
		switch (pos) {
		case 1:
			//rectangle
			rect.setPosition(700, 50);
			//Text in rectangle
			text.setString("9.8 m/s^2");
			text.setPosition(700, 55);
			//Text etiquettes
			legend.setString("g-force");
			legend.setPosition(700, 30);
			break;
		case 2:
			//Rectangle
			rect.setPosition(615, 50);
			//Text in rectangle
			text.setString("00 °");
			text.setPosition(620, 55);
			//Text etiquettes
			legend.setString("g-angle");
			legend.setPosition(620, 30);
			break;
		case 3:
			//Rectangle
			rect.setPosition(700, 120);
			//Text in rectangle
			text.setString("0 N/m^2");
			text.setPosition(705, 125);
			//Text etiquettes
			legend.setString("wind-force");
			legend.setPosition(700, 95);
			break;
		case 4:
			//Rectangle
			rect.setPosition(615, 120);
			//Text in rectangle
			text.setString("00 °");
			text.setPosition(620, 125);
			//Text etiquettes
			legend.setString("wind-angle");
			legend.setPosition(610, 95);
			break;
		default:
			throw std::logic_error("Unknown position");
		}
	}

	//CATCH PROBLEMS TO READ FILES OR UNKNOWN POSITIONS OR BUTTON TYPES
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}
};

//Getters
sf::Text force_entry::getText() { return text; };
sf::RectangleShape force_entry::getRectangle() { return rect; };
sf::Text force_entry::getLegend() { return legend; };