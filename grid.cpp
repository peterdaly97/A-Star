#include "grid.h"

Grid::Grid() {
	if (!m_font.loadFromFile("arial.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i] = new Tile(sf::Vector2f(30 * e, 30 * i), &m_font);
		}
	}

}


Grid::~Grid() {}

void Grid::update() {

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i]->update();
		}
	}

	if (m_start && m_end && !m_startCalc) {
		m_startCalc = true;
		setUpHeatMap();
	}
}

void Grid::render(sf::RenderWindow * window) {
	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i]->render(window);
		}
	}
}

void Grid::selectLeft(sf::Vector2f pos) {
	if (!m_start && !m_grid[(int)pos.x][(int)pos.y]->m_end && 
		!m_grid[(int)pos.x][(int)pos.y]->m_obstacle) {
		m_start = true;
		m_grid[(int)pos.x][(int)pos.y]->m_start = true;
	}
		
}

void Grid::selectRight(sf::Vector2f pos) {
	if (!m_end && !m_grid[(int)pos.x][(int)pos.y]->m_start &&
		!m_grid[(int)pos.x][(int)pos.y]->m_obstacle) {
		m_end = true;
		m_grid[(int)pos.x][(int)pos.y]->m_end = true;

	}

}

void Grid::selectMiddle(sf::Vector2f pos) {
	if (!m_grid[(int)pos.x][(int)pos.y]->m_start && 
		!m_grid[(int)pos.x][(int)pos.y]->m_end &&
		!m_grid[(int)pos.x][(int)pos.y]->m_obstacle) {

		m_grid[(int)pos.x][(int)pos.y]->m_obstacle = true;

		if (m_start && m_end) {
			m_startCalc = false;
			for (int i = 0; i < m_height; i++) {
				for (int e = 0; e < m_width; e++) {
					m_grid[e][i]->m_marked = false;
					m_grid[e][i]->m_path = false;
				}
			}

		}
	}

}

void Grid::setUpHeatMap() {
	int startX;
	int startY;
	Tile* startTile = new Tile(sf::Vector2f(0, 0), &m_font);

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			if (m_grid[e][i]->m_start) {
				startTile = m_grid[e][i];
				pq.push_back(startTile);
				startX = e;
				startY = i;
			}
				
		}
	}

	m_grid[startX][startY]->m_cost = 0;
	pq.push_back(startTile);
	int cost = 0;
	qq.push_back(std::pair<std::vector<Tile*>, int>(pq, cost + 1));
	heatLoop();

}

void Grid::heatLoop() {
	for (std::pair<std::vector<Tile*>, int> nextPQ : qq) {
		nextPQ = *qq.begin();
		for (Tile * p : nextPQ.first) {
			heatMap(p, p->m_tile.getPosition().x / 30,
				p->m_tile.getPosition().y / 30, nextPQ.second);
		}
		qq.erase(qq.begin());
	
	}

	if (qq.size() > 0)
		heatLoop();

	makePath();
}

void Grid::setUpNode(int x, int y, int xAdd, int yAdd, int cost, float angle) {
	int newX = x + xAdd;
	int newY = y + yAdd;

	m_grid[newX][newY]->setCost(cost);
	m_grid[newX][newY]->setLine(angle);
	m_grid[newX][newY]->m_marked = true;
	m_grid[newX][newY]->m_pathNode = std::make_pair(x, y);
	pq.push_back(m_grid[newX][newY]);
}

void Grid::heatMap(Tile * tile, int x, int y, int cost) {

	if (x < 49 && !m_grid[x + 1][y]->m_start && !m_grid[x + 1][y]->m_obstacle
		&& !m_grid[x + 1][y]->m_marked) {
		
		setUpNode(x, y, 1, 0, cost, 0.0);
	}
	if (x > 0 && !m_grid[x - 1][y]->m_start && !m_grid[x - 1][y]->m_obstacle
		&& !m_grid[x - 1][y]->m_marked) {

		setUpNode(x, y, -1, 0, cost, 180.0);
	}
	if (y < 49 && !m_grid[x][y + 1]->m_start && !m_grid[x][y + 1]->m_obstacle
		&& !m_grid[x][y + 1]->m_marked) {

		setUpNode(x, y, 0, 1, cost, 90.0);
	}
	if (y > 0 && !m_grid[x][y - 1]->m_start && !m_grid[x][y - 1]->m_obstacle
		&& !m_grid[x][y - 1]->m_marked) {

		setUpNode(x, y, 0, -1, cost, 270.0);
	}	

	if (y > 0 && x > 0 && !m_grid[x - 1][y - 1]->m_start && !m_grid[x - 1][y - 1]->m_obstacle
		&& !m_grid[x - 1][y - 1]->m_marked) {

		setUpNode(x, y, -1, -1, cost, 225.0);
	}
	if (y < 49 && x > 0 && !m_grid[x - 1][y + 1]->m_start && !m_grid[x - 1][y + 1]->m_obstacle
		&& !m_grid[x - 1][y + 1]->m_marked) {

		setUpNode(x, y, -1, 1, cost, 135.0);
	}
	if (y > 0 && x < 49 && !m_grid[x + 1][y - 1]->m_start && !m_grid[x + 1][y - 1]->m_obstacle
		&& !m_grid[x + 1][y - 1]->m_marked) {

		setUpNode(x, y, 1, -1, cost, 315.0);
	}
	if (y < 49 && x < 49 && !m_grid[x + 1][y + 1]->m_start && !m_grid[x + 1][y + 1]->m_obstacle
		&& !m_grid[x + 1][y + 1]->m_marked) {

		setUpNode(x, y, 1, 1, cost, 45.0);
	}

	qq.push_back(std::pair<std::vector<Tile*>, int>(pq, cost + 1));
	pq.clear();
}

void Grid::makePath() {
	int startX;
	int startY;
	Tile* startTile = new Tile(sf::Vector2f(0, 0), &m_font);

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			if (m_grid[e][i]->m_end) {
				startTile = m_grid[e][i];
				startX = e;
				startY = i;
			}

		}
	}

	while (!startTile->m_start && startTile->m_pathNode.first > -1) {
		startTile->m_path = true;
		startTile = m_grid[startTile->m_pathNode.first][ startTile->m_pathNode.second];
	}
}

void Grid::toggleCost() {
	if (m_toggleCost)
		m_toggleCost = false;
	else
		m_toggleCost = true;

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i]->m_toggleCost = m_toggleCost;
		}
	}
}

void Grid::toggleVector() {
	if (m_toggleVector)
		m_toggleVector = false;
	else
		m_toggleVector = true;

	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i]->m_toggleVector = m_toggleVector;
		}
	}
}

void Grid::clearGrid() {
	m_start = false;
	m_end = false;
	m_startCalc = false;
	for (int i = 0; i < m_height; i++) {
		for (int e = 0; e < m_width; e++) {
			m_grid[e][i]->m_cost = 0;
			m_grid[e][i]->m_start = false;
			m_grid[e][i]->m_end = false;
			m_grid[e][i]->m_path = false;
			m_grid[e][i]->m_obstacle = false;
			m_grid[e][i]->m_marked = false;
			m_grid[e][i]->m_pathNode.first = -1;
			m_grid[e][i]->m_line.setRotation(0);
			m_grid[e][i]->m_line.setFillColor(sf::Color::White);
			m_grid[e][i]->m_line.setOutlineColor(sf::Color::White);
			
		}
	}
}


