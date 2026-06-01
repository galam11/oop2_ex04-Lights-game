#pragma once
#include <map>

#include <SFML/Graphics.hpp>
#include "LightNode.h"

namespace std {
	template <>
	struct less<sf::Vector2i> {
		bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
			if (lhs.x != rhs.x) return lhs.x < rhs.x;
			return lhs.y < rhs.y;
		}
	};
}

class Board
{
public:
	Board(int middleRowCount);
	void draw(sf::RenderWindow& window) const;
	void handleClick(const sf::Vector2f& position,bool clockWise);
	bool isSolved() const;

private:
	std::map<sf::Vector2i, LightNode> m_nodes;
	

	void updateLighting();
};