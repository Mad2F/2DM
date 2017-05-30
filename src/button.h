#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include<cassert>

#include <SFML/Graphics.hpp>

//Paths to external ressources (paths to images of buttons and to font)
const std::string path_to_text_button = "../externalGUI/button.png";
const std::string path_to_pause_button = "../externalGUI/pause.png";
const std::string path_to_play_button = "../externalGUI/play.png";
const std::string path_to_police = "../externalGUI/arial.ttf";

//************CLASS BUTTON customized********************************
//only two types of buttons : play button or text button
//due to application here
//******************************************************************
class Button {
public:
	//Constructor and destructor : type = 0 is a play button, type = 1 is a text button.
	//pos = 0, 1, 2 only : pos = 0 is the first button (add objects), 1 is the second (add punctual forces)
	//2 is the third (add global forces).
	//Everything else raises an exception.
	Button() { Button(0, 0); }
	Button(int type, int pos);
	~Button();
	//Methods to get the sprite
	sf::Sprite getSprite();
	//Method to get the text of the button
	sf::Text getText();
	//Detect if the button is clicked : if the mouse position is IN the button area
	bool isClicked(int posX, int posY);
	//Click : if the button is not blocked, apply the button.
	void click();
	//Block and unblock the button
	void block();
	void unblock();
	//Check if the button is clicked
	bool isClicked();

private:
	//Type of button : play/pause true or text button false
	bool m_type;
	//State On/Off
	bool m_state;
	//Blocked button
	bool m_blocked;
	//Position
	int m_posX;
	int m_posY;
	//Text and position
	std::string m_text_on;
	std::string m_text_off;
	int m_posT_X;
	int m_posT_Y;
	//Sprite
	sf::Sprite sprite;
	sf::Texture texture;
	//Font
	sf::Font font;
	sf::Text text;
};
#endif // BUTTON_H