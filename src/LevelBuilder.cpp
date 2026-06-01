#include "levelBuilder.h"
#include <stack>

LevelBuilder::LevelBuilder(int middleRowCount)
	: m_middleRowCount(middleRowCount)
{ }

void LevelBuilder::generateLevel(NodeMap& nodes)
{
	generateGrid();
	buildSpanningTree();
	createAndScrambleNodes(nodes);
}

void LevelBuilder::generateGrid()
{
	int radius = (m_middleRowCount - 1) / 2;

	for (int j = 0; j < m_middleRowCount; ++j)
		m_NodesPos.push_back(sf::Vector2i(j - radius, 0));
	

	for (int i = m_middleRowCount - 1, level = 1; i >= 3; --i, level++)
		for (int j = 0; j < i; ++j)
		{
			auto pos = sf::Vector2i(j - radius, level);
			m_NodesPos.push_back(pos);
			m_NodesPos.push_back(-pos);
		}
	
}

void LevelBuilder::buildSpanningTree()
{
	std::unordered_map<sf::Vector2i, bool,VectorHash> visited;
	for (const auto& coord : m_NodesPos)
	{
		m_Arms[coord] = { false, false, false, false, false, false };
		visited[coord] = false;
	}

	std::stack<sf::Vector2i> stack;
	sf::Vector2i start(0, 0);
	stack.push(start);
	visited[start] = true;

	while (!stack.empty())
	{
		sf::Vector2i curr = stack.top();
		std::vector<int> unvisited_dirs;

		for (int dir = 0; dir < 6; ++dir)
		{
			sf::Vector2i neighbor = curr + NIGBORS_DIR[dir];
			if (visited.find(neighbor) != visited.end() && !visited[neighbor])
			{
				unvisited_dirs.push_back(dir);
			}
		}

		if (!unvisited_dirs.empty())
		{
			int random_idx = std::rand() % unvisited_dirs.size();
			int dir = unvisited_dirs[random_idx];
			sf::Vector2i next = curr + NIGBORS_DIR[dir];

			m_Arms[curr][dir] = true;
			m_Arms[next][(dir + 3) % 6] = true;
			visited[next] = true;
			stack.push(next);
		}
		else
		{
			stack.pop();
		}
	}
}

void LevelBuilder::createAndScrambleNodes(NodeMap& nodes)
{
	for (const auto& coord : m_NodesPos)
	{
		LightNode node(coord, m_Arms[coord]);

		int rotations = std::rand() % 6;
		for (int i = 0; i < rotations; ++i)
			node.rotateRight();
		
		nodes.emplace(coord, node);
	}
}