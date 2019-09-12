#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button 
{
public:
	Button() {}
	Button(std::string *text, sf::Vector2f *position, sf::Font *font);
	~Button();	// Deconstructor for the Button object.

	void update();
									
									
	void render(sf::RenderWindow& window);

	bool isInside(sf::Vector2f mPos);

	sf::Vector2f m_position;	// Stores the postion of the Button.

	sf::RectangleShape m_btnRec; // Rectangle for the button

private:

	sf::Text m_text;	// Stores the text that will be written on the Button.
	sf::Font m_font;	// Stores the font that will be used to draw the Text.

	sf::FloatRect m_textRectangle;	// Rectangle used to set the origin of the text to its centre, this is done to allow for the text to be centred easier.
	
										  // Base contrasts (whites/greys/blacks)
	sf::Color m_grey = sf::Color(160, 160, 160);
	sf::Color m_deepGrey = sf::Color(85, 90, 90);
	sf::Color m_lightGrey = sf::Color(200, 200, 200);

	sf::Color m_white = sf::Color(255, 255, 255);
	sf::Color m_black = sf::Color(0, 0, 0);

	// "Blue" palette
	sf::Color m_lilac = sf::Color(140, 80, 160);
	sf::Color m_blue = sf::Color(65, 70, 200);
	sf::Color m_purple = sf::Color(145, 0, 165);
	sf::Color m_seaBlue = sf::Color(85, 165, 185);

	// "Yellow" palette
	sf::Color m_gold = sf::Color(255, 205, 0);
	sf::Color m_paleBanana = sf::Color(245, 245, 230);
};

#endif // !BUTTON_H

