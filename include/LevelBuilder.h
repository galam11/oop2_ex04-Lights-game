#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "LightNode.h"
#include "Board.h"
#include "NodeMap.h"

class LevelBuilder
{
public:
	LevelBuilder(int middleRowCount);
	void generateLevel(NodeMap& nodes);

private:
	int m_middleRowCount;
	std::vector<sf::Vector2i> m_NodesPos;
	std::unordered_map<sf::Vector2i, std::array<bool, 6>, VectorHash> m_Arms;

	void generateGrid();
	void buildSpanningTree();
	void createAndScrambleNodes(NodeMap& nodes);
};