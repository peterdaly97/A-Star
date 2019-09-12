#include "button.h"

Button::Button(std::string *text, sf::Vector2f *position, sf::Font *font) :

	m_position(*position),	// Sets m_position to the de-referenced value of the position argument.
	m_text(*text, *font, 20)	// Sets m_text to the de-referenced value of the text argument as well as the de-referenced value of the font argument and then sets the size of the text to 28.
{
	m_btnRec.setOutlineColor(m_white);
	m_btnRec.setOutlineThickness(5.0f);
	m_btnRec.setPosition(m_position);
	m_btnRec.setFillColor(sf::Color(25, 25, 25, 255));
	m_btnRec.setSize(sf::Vector2f(150, 50));
	m_btnRec.setOrigin(sf::Vector2f(75, 25));

	m_textRectangle = m_text.getLocalBounds();	// Gets the dimensions of the rectangle that contains the text.
	m_text.setOrigin(m_textRectangle.width / 2.0f, m_textRectangle.height / 2.0f);	// Centres the origin of the text.
	m_text.setPosition(m_position.x, m_position.y - 5);	// Sets the position of the text with its centre now being its origin.

	m_text.setFillColor(m_white);
}

Button::~Button()
{
}


void Button::render(sf::RenderWindow & window)
{
	window.draw(m_btnRec);	// Draws the button rectangle to the screen.
	window.draw(m_text);	// Draws the text on top of the sprite.
}

bool Button::isInside(sf::Vector2f mPos)
{
	if (mPos.x > m_btnRec.getPosition().x - m_btnRec.getOrigin().x &&
		mPos.x < m_btnRec.getPosition().x + m_btnRec.getOrigin().x
		&& mPos.y > m_btnRec.getPosition().y - m_btnRec.getOrigin().y &&
		mPos.y < m_btnRec.getPosition().y + m_btnRec.getOrigin().y)
		return true;
	return false;
}
