#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include "Board.h"
#include <memory>

class Controller
{
public:
	Controller();
	void run();

private:

	void handleEvent(const auto&);
	void handleEvent(const sf::Event::Closed&);
	void handleEvent(const sf::Event::MouseButtonPressed& mouseButtonPressedEvent);
	void handleEvent(const sf::Event::KeyPressed& keyPressedEvent);

	void loadMidRowPlayList();
	void loadAndCreateText();

	void nextLevel();

	sf::RenderWindow m_window;
	Board m_board;
	std::queue<int> m_midRowQueue;

	std::unique_ptr<sf::Text> m_winText = nullptr;
	std::unique_ptr<sf::Text> m_nextLevelText = nullptr;
	std::unique_ptr<sf::Text> m_pressToContinueText = nullptr;
	sf::Font m_font;

	bool m_paused = false;
	bool m_gameOver = false;
};