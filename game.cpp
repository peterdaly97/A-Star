#include "game.h"

static sf::Int32 MS_PER_UPDATE = 10.0;


Game::Game() : m_window(sf::VideoMode(1800, 1500), "AI") {

	m_window.setFramerateLimit(60);
	std::string clearText = "Clear Grid";
	m_buttonClear = new Button(&clearText, new sf::Vector2f(1600, 100), &grid.m_font);
	std::string costText = "Toggle Cost";
	m_buttonCost = new Button(&costText, new sf::Vector2f(1600, 300), &grid.m_font);
	std::string vectorText = "Toggle Vector";
	m_buttonVector = new Button(&vectorText, new sf::Vector2f(1600, 500), &grid.m_font);

	lmbText.setFont(grid.m_font);
	rmbText.setFont(grid.m_font);
	mmbText.setFont(grid.m_font);
	lmbText.setCharacterSize(16.0f);
	rmbText.setCharacterSize(16.0f);
	mmbText.setCharacterSize(16.0f);
	lmbText.setFillColor(sf::Color(255, 255, 255, 255));
	rmbText.setFillColor(sf::Color(255, 255, 255, 255));
	mmbText.setFillColor(sf::Color(255, 255, 255, 255));
	lmbText.setPosition(sf::Vector2f(1520, 700));
	rmbText.setPosition(sf::Vector2f(1520, 800));
	mmbText.setPosition(sf::Vector2f(1520, 900));
	lmbText.setString("Left Mouse Button to select start");
	rmbText.setString("Right Mouse Button to select end");
	mmbText.setString("Middle Mouse Button to place obstacle");
}

Game::~Game() {

}

void Game::run() {
	m_window.setKeyRepeatEnabled(false);
	while (m_window.isOpen()) {
		update();
		while (m_window.pollEvent(event))
		{
				
		}
		mousePos.x = m_mouse.getPosition(m_window).x / 30;
		mousePos.y = m_mouse.getPosition(m_window).y / 30;
		if (m_mouse.isButtonPressed(sf::Mouse::Left)) {
			if (mousePos.x < 50)
				grid.selectLeft(mousePos);
			if (m_buttonCost->isInside((sf::Vector2f)m_mouse.getPosition(m_window)))
				grid.toggleCost();
			if (m_buttonVector->isInside((sf::Vector2f)m_mouse.getPosition(m_window)))
				grid.toggleVector();
			if (m_buttonClear->isInside((sf::Vector2f)m_mouse.getPosition(m_window)))
				grid.clearGrid();
		}
		if (m_mouse.isButtonPressed(sf::Mouse::Right)) {
			if (mousePos.x < 50)
				grid.selectRight(mousePos);
		}
		if (m_mouse.isButtonPressed(sf::Mouse::Middle)) {
			if (mousePos.x < 50)
				grid.selectMiddle(mousePos);
		}

		render();
	}
}

void Game::update() {
	grid.update();

}

void Game::render() {
	m_window.clear(sf::Color(45,45,45, 255));
	
	grid.render(&m_window);
	m_buttonClear->render(m_window);
	m_buttonCost->render(m_window);
	m_buttonVector->render(m_window);
	m_window.draw(lmbText);
	m_window.draw(rmbText);
	m_window.draw(mmbText);
	m_window.display();

}