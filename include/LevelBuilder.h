#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "LightNode.h"
#include "Board.h"

class LevelBuilder
{
public:
	LevelBuilder(int middleRowCount);
	void generateLevel(std::map<sf::Vector2i, LightNode>& nodes);

private:
	int m_middleRowCount;
	std::vector<sf::Vector2i> m_NodesPos;
	std::map<sf::Vector2i, std::array<bool, 6>> m_Arms;

	void generateGrid();
	void buildSpanningTree();
	void createAndScrambleNodes(std::map<sf::Vector2i, LightNode>& nodes);
};