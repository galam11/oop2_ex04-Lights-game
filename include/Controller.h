#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Controller
{
public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	Board m_board;
	int m_middleRowCount = 5;
};