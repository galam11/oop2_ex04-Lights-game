#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Controller
{
public:
	Controller();
	void run();

private:
	void handleEvent(const auto&);
	void handleEvent(const sf::Event::Closed&);
	void handleEvent(const sf::Event::MouseButtonPressed& mouseButtonPressedEvent);

	sf::RenderWindow m_window;
	Board m_board;
};