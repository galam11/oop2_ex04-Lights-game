#include "LightNode.h"


LightNode::LightNode(sf::Vector2i pos, std::array<bool, 6> arms)
	: m_pos(pos), m_arms(arms), m_shape(pos, arms)
{
	for (int i = 0; i < NIGBORS_DIR.size(); i++)
		m_neighbors[i] = m_pos + NIGBORS_DIR[i];
}	

void LightNode::draw(sf::RenderWindow& window) const
{
	m_shape.draw(window);
}

void LightNode::setLit(bool lit)
{
	m_lit = lit;
	m_shape.setLit(lit);
}

bool LightNode::isLit() const
{
	return m_lit;
}

void LightNode::rotateRight()
{
	std::rotate(m_arms.rbegin(), m_arms.rbegin() + 1, m_arms.rend());
	m_shape.rotateRight();
}

void LightNode::rotateLeft()
{
	std::rotate(m_arms.begin(), m_arms.begin() + 1, m_arms.end());
	m_shape.rotateLeft();
}

bool LightNode::mouseOverNode(const sf::Vector2f& mousePos) const
{
	auto worldPos = m_shape.getPosition();

	float dx = mousePos.x - worldPos.x;
	float dy = mousePos.y - worldPos.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	return distance <= HEX_CLICABLE_SIZE;

}

const std::array<sf::Vector2i, 6>& LightNode::getNeighbors() const
{
	return m_neighbors;
}

bool LightNode::connectedTo(const LightNode& other) const
{
	for (int i = 0; i < m_arms.size(); ++i)
	{
		if (m_arms[i])
		{
			auto& neighbor = m_neighbors[i];
			if (neighbor == other.m_pos)
				return other.m_arms[(i + 3) % 6];
		}
	}
	return false;
}