#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Tile
{
public:
	Tile(sf::Vector2f pos, sf::Font * font);

	~Tile();

	void update();

	void render(sf::RenderWindow * window);

	void setCost(int cost);

	bool m_obstacle = false;

	bool m_start = false;
	bool m_end = false;
	bool m_path = false;

	int m_cost = 0;
	int m_integration = 0;
	sf::RectangleShape m_tile;

	sf::RectangleShape m_line;

	void setLine(float rot);
	
	int m_width = 30;
	int m_height = 30;

	std::pair<int, int> m_pathNode;

	bool m_toggleCost = true;
	bool m_toggleVector = true;

	bool m_marked = false;

private:
	
	sf::Text m_text;
	
	
};

#endif //!GRID_H


