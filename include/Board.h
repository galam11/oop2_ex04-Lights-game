#pragma once


#include <SFML/Graphics.hpp>
#include "LightNode.h"
#include "NodeMap.h"


class Board
{
public:
	Board() = default;
	Board(int middleRowCount);
	void draw(sf::RenderWindow& window) const;
	void handleClick(const sf::Vector2f& position,bool clockWise);
	bool isSolved() const;

private:
	NodeMap m_nodes;
	
	void updateLighting();
};