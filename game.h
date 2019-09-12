#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "grid.h"
#include "Button.h"

class Game
{
public:
	Game();

	~Game();

	void run();
	void update();
	void render();


	sf::RenderWindow m_window;

	sf::Mouse m_mouse;

private:
	Grid grid;

	sf::Event event;

	int x = 0;
	int y = 0;

	Button* m_buttonClear;
	Button* m_buttonCost;
	Button* m_buttonVector;

	sf::Vector2f mousePos;

	sf::Text lmbText;
	sf::Text rmbText;
	sf::Text mmbText;
};

#endif //!GAME_H
