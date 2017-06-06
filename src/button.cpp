#include "button.h"

//Constructor :
// - type = 0 means a play button
// - type = 1 means a text button
//		- pos = 0 is the object button
//		- pos = 1 is the force button
//		- pos = 2 is the global force button
Button::Button(int type, int pos) {
	try {
		switch (type) {
		//PLAY BUTTON, initially unblocked and paused
		case 0:
			//Set type
			m_type = true;
			//Set state of button ON/OFF
			m_state = false;
			//Set blocked
			m_blocked = false;
			//Set position of sprite and of text
			m_posX = 640;
			m_posY = 500;
			m_posT_X = m_posX + 5;
			m_posT_Y = 568;
			//Set text
			m_text_off = "Start simulation";
			m_text_on = "Pause simulation";
			//Get image (throw error if unable to load the file)
			if (!texture.loadFromFile(path_to_play_button))
			{
				throw std::logic_error("Unable to open file");
			}
			//Set position, texture and scale of the sprite
			sprite.setPosition(m_posX, m_posY);
			sprite.setTexture(texture);
			sprite.setScale(0.15, 0.15);
			break;
		//TEXT BUTTON
		case 1:
			//Set type
			m_type = false;
			//Set ON/OFF
			m_state = false;
			//Set blocked
			m_blocked = false;
			//Set position of sprite
			m_posX = 600;
			m_posY = 200 + 100 * pos;
			//According to position, set text and position of text
			//Catch unknown position
			switch (pos) {
			case 0:
				m_text_off = "Add objects";
				m_text_on = "Add objects";
				m_posT_X = 650;
				m_posT_Y = 220;
				break;
			case 1:
				m_text_off = "Add forces on one object";
				m_text_on = "Add forces on one object";
				m_posT_X = 620;
				m_posT_Y = 320;
				break;
			case 2:
				m_text_off = "Add forces on all objects";
				m_text_on = "Add forces on all objects";
				m_posT_X = 620;
				m_posT_Y = 420;
				break;
			default:
				throw std::logic_error("Unknown position");
			}
			//Load image for texture with exception if unable to read
			if (!texture.loadFromFile(path_to_text_button))
			{
				throw std::logic_error("Unable to open image file");
			}
			//Set position, texture and scale of sprite
			sprite.setPosition(m_posX, m_posY);
			sprite.setTexture(texture);
			sprite.setScale(0.35, 0.35);
			break;
		//UNKNOWN BUTTON TYPE
		default:
			throw std::logic_error("Unknown button");
			break;
		}; //end of switch

		//Set the police
		if (!font.loadFromFile(path_to_police)) {
			throw std::logic_error("Unable to open police");
		}
		//Set text font, content, character size, color, position.
		text.setFont(font);
		text.setString(m_text_off);
		text.setCharacterSize(12);
		text.setColor(sf::Color().White);
		text.setPosition(m_posT_X, m_posT_Y);
	}

	//CATCH PROBLEMS TO READ FILES OR UNKNOWN POSITIONS OR BUTTON TYPES
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}
}

//Destructor
Button::~Button() {};

//Getter
sf::Sprite Button::getSprite() {
	return sprite;
}
//Getter
sf::Text Button::getText() {
	return text;
}

//Check if the button is clicked byt the given position (if the sprite contains the position)
bool Button::isClicked(int posX, int posY) {
	return sprite.getGlobalBounds().contains(posX, posY);
}

//Click if the button is not blocked (for the moment it changes only italic for text buttons and prints "click")
void Button::click() {
	try {
		//If the button is not blocked
		if (!m_blocked) {
			//Change state ON/OFF
			m_state = !m_state;
			//If on, turn everything (text and texture) to ON
			if (m_state) {
				text.setString(m_text_on);
				if (m_type) {
					if (!texture.loadFromFile(path_to_pause_button))
					{
						throw std::logic_error("Unable to open image file");
					}
				}
			}
			//If off turn everything (text and texture) to OFF
			else {
				text.setString(m_text_off);
				if (m_type) {
					if (!texture.loadFromFile(path_to_play_button))
					{
						throw std::logic_error("Unable to open image file");
					}
				}
			}
		}
	}
	//CATCH Loading problems
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}
}

//Blocks the button and turns font style to italic
void Button::block() {
	m_blocked = true;
	text.setStyle(sf::Text::Italic);
}

//Unblocks the button and turns font style to regular
void Button::unblock() {
	m_blocked = false;
	text.setStyle(sf::Text::Regular);
}

//Check if the button is ON
bool Button::isClicked() {
	return m_state;
}