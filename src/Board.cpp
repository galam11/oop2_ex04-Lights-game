#include "Board.h"
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>

Board::Board(int middleRowCount)
{
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		seeded = true;
	}

	int radius = (middleRowCount - 1) / 2;
	std::vector<sf::Vector2i> all_coords;
	std::map<sf::Vector2i, std::array<bool, 6>> temp_arms;

	generateGrid(radius, all_coords);
	buildSpanningTree(all_coords, temp_arms);
	addFakeArms(temp_arms);
	createAndScrambleNodes(all_coords, temp_arms);

	updateLighting();
}

void Board::generateGrid(int radius, std::vector<sf::Vector2i>& all_coords)
{
	for (int q = -radius; q <= radius; ++q)
	{
		for (int r = -radius; r <= radius; ++r)
		{
			if (std::abs(q + r) <= radius)
			{
				all_coords.push_back(sf::Vector2i(q, r));
			}
		}
	}
}

void Board::buildSpanningTree(const std::vector<sf::Vector2i>& all_coords, std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms)
{
	std::map<sf::Vector2i, bool> visited;
	for (const auto& coord : all_coords)
	{
		temp_arms[coord] = { false, false, false, false, false, false };
		visited[coord] = false;
	}

	std::stack<sf::Vector2i> stack;
	sf::Vector2i start(0, 0);
	stack.push(start);
	visited[start] = true;

	std::array<sf::Vector2i, 6> directions = {
		sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 1),
		sf::Vector2i(-1, 0), sf::Vector2i(0, -1), sf::Vector2i(1, -1)
	};

	while (!stack.empty())
	{
		sf::Vector2i curr = stack.top();
		std::vector<int> unvisited_dirs;
		
		for (int dir = 0; dir < 6; ++dir)
		{
			sf::Vector2i neighbor = curr + directions[dir];
			if (visited.find(neighbor) != visited.end() && !visited[neighbor])
			{
				unvisited_dirs.push_back(dir);
			}
		}

		if (!unvisited_dirs.empty())
		{
			int random_idx = std::rand() % unvisited_dirs.size();
			int dir = unvisited_dirs[random_idx];
			sf::Vector2i next = curr + directions[dir];

			temp_arms[curr][dir] = true;
			temp_arms[next][(dir + 3) % 6] = true;
			visited[next] = true;
			stack.push(next);
		}
		else
		{
			stack.pop();
		}
	}
}

void Board::addFakeArms(std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms)
{
	std::array<sf::Vector2i, 6> directions = {
		sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 1),
		sf::Vector2i(-1, 0), sf::Vector2i(0, -1), sf::Vector2i(1, -1)
	};

	for (auto& pair : temp_arms)
	{
		sf::Vector2i curr = pair.first;
		for (int dir = 0; dir < 6; ++dir)
		{
			if (!temp_arms[curr][dir])
			{
				if (std::rand() % 100 < 10) // 10% chance for noise
				{
					sf::Vector2i neighbor = curr + directions[dir];
					if (temp_arms.find(neighbor) != temp_arms.end())
					{
						temp_arms[curr][dir] = true;
						temp_arms[neighbor][(dir + 3) % 6] = true;
					}
				}
			}
		}
	}
}

void Board::createAndScrambleNodes(const std::vector<sf::Vector2i>& all_coords, std::map<sf::Vector2i, std::array<bool, 6>>& temp_arms)
{
	for (const auto& coord : all_coords)
	{
		bool isCenter = (coord.x == 0 && coord.y == 0);
		HexNode node(coord, temp_arms[coord], isCenter);
		
		int rotations = std::rand() % 6;
		for (int i = 0; i < rotations; ++i)
		{
			node.rotateRight();
		}

		m_nodes[coord] = node;
	}
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
		if (pair.second.clickedOnNode(position))
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
	{
		pair.second.setLit(false);
	}

	auto centerIt = m_nodes.find(sf::Vector2i(0, 0));
	if (centerIt == m_nodes.end()) return;

	centerIt->second.setLit(true);

	std::queue<sf::Vector2i> q;
	q.push(sf::Vector2i(0, 0));

	while (!q.empty())
	{
		sf::Vector2i currPos = q.front();
		q.pop();

		HexNode& currNode = m_nodes[currPos];

		for (const sf::Vector2i& neighborPos : currNode.getNeighbors())
		{
			auto neighborIt = m_nodes.find(neighborPos);
			if (neighborIt != m_nodes.end())
			{
				HexNode& neighborNode = neighborIt->second;
				
				if (!neighborNode.isLit() && currNode.connectedTo(neighborNode))
				{
					neighborNode.setLit(true);
					q.push(neighborPos);
				}
			} // חסר כאן הסוגר של ה-if
		}
	}
}

bool Board::isSolved() const
{
	for (const auto& pair : m_nodes)
	{
		if (!pair.second.isLit())
		{
			return false;
		}
	}
	return true;
}
