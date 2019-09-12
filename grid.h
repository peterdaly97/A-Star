#ifndef GRID_H
#define GRID_H

#include "SFML/Graphics.hpp"
#include "tile.h"
#include <vector>
#include <limits>

class Grid
{
public:
	Grid();

	~Grid();

	void update();
	void render(sf::RenderWindow * window);

	void selectLeft(sf::Vector2f pos);
	void selectRight(sf::Vector2f pos);
	void selectMiddle(sf::Vector2f pos);

	void setUpHeatMap();
	void heatMap(Tile * tile, int x, int y, int cost);
	void heatLoop();
	void setUpNode(int x, int y, int xAdd, int yAdd, int cost, float angle);

	void makePath();

	void toggleCost();
	void toggleVector();
	void clearGrid();

	bool m_startCalc = false;
	sf::Font m_font;

private:
	int m_width = 50;
	int m_height = 50;
	Tile *m_grid[50][50];

	sf::Keyboard m_keys;
	int m_lastKey = 0;

	int xSelected = 0;
	int ySelected = 0;

	bool m_lastPress = false;

	bool m_start = false;
	bool m_end = false;

	bool m_toggleCost = true;
	bool m_toggleVector = true;

	std::vector<Tile *> pq;
	std::vector<std::pair<std::vector<Tile *>, int>> qq;
};

#endif //!GRID_H

