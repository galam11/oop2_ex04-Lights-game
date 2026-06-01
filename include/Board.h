#pragma once
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>
#include "HexNode.h"

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
	Board(int middleRowCount = 5);
	void draw(sf::RenderWindow& window) const;
	void handleClick(const sf::Vector2f& position,bool clockWise);
	bool isSolved() const;

private:
	std::map<sf::Vector2i, HexNode> m_nodes;
	
	// Helper functions for board generation
	void generateGrid(int radius, std::vector<sf::Vector2i>& all_coords);
	void buildSpanningTree(const std::vector<sf::Vector2i>& all_coords, std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms);
	void addFakeArms(std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms);
	void createAndScrambleNodes(const std::vector<sf::Vector2i>& all_coords, std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms);
	
	void updateLighting();
};