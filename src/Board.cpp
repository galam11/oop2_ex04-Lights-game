#include "Board.h"
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "LevelBuilder.h"

Board::Board(int middleRowCount)
{

	LevelBuilder builder(middleRowCount);
	builder.generateLevel(m_nodes);

	updateLighting();
}

void Board::draw(sf::RenderWindow& window) const
{
	for (const auto& pair : m_nodes)
	{
		pair.second.draw(window);
	}
}

void Board::handleClick(const sf::Vector2f& position, bool clockWise)
{
	for (auto& pair : m_nodes)
	{
		if (pair.second.mouseOverNode(position))
		{
			if (clockWise)
				pair.second.rotateRight();
			else
				pair.second.rotateLeft();

			updateLighting();
			break;
		}
	}
}

void Board::updateLighting()
{
	for (auto& pair : m_nodes)
		pair.second.setLit(false);
	
	m_nodes[sf::Vector2i(0, 0)].setLit(true);

	std::queue<sf::Vector2i> q;
	q.push(sf::Vector2i(0, 0));

	while (!q.empty())
	{
		sf::Vector2i currPos = q.front();
		q.pop();

		LightNode& currNode = m_nodes[currPos];

		for (const sf::Vector2i& neighborPos : currNode.getNeighbors())
		{
			auto neighborIt = m_nodes.find(neighborPos);
			if (neighborIt == m_nodes.end())
				continue;

			LightNode& neighborNode = neighborIt->second;
				
			if (!neighborNode.isLit() && currNode.connectedTo(neighborNode))
			{
				neighborNode.setLit(true);
				q.push(neighborPos);
			}
			
		}
	}
}

bool Board::isSolved() const
{
	return std::all_of(m_nodes.begin(), m_nodes.end(), 
		[](const auto& pair) { return pair.second.isLit(); }
);
}
