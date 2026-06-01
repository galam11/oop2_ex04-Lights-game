#include "HexNode.h"


HexNode::HexNode(sf::Vector2i pos, std::array<bool, 6> arms, bool center)
    : m_pos(pos) , m_center(center), m_circle(RADIUS_SIZE) , m_arms(arms)
{
	m_circle.setOrigin(sf::Vector2f(RADIUS_SIZE, RADIUS_SIZE));
	m_circle.setPosition(node2World(m_pos));
	setLit(center);

	float angle = 0.0f;
	for (auto& rectshape : m_armsShapes)
	{
		rectshape.setPosition(node2World(m_pos));
		rectshape.setSize(sf::Vector2f(HEX_SIZE, 3.0f));
		rectshape.setOrigin(sf::Vector2f(0, 1.5f));
		rectshape.setFillColor(sf::Color::Black);

		rectshape.setRotation(sf::degrees(angle));
		angle += 60.0f;
	}

	m_neighbors = {
		pos + sf::Vector2i(1, 0),
		pos + sf::Vector2i(0, 1),
		pos + sf::Vector2i(-1, 1),
		pos + sf::Vector2i(-1, 0),
		pos + sf::Vector2i(0, -1),
		pos + sf::Vector2i(1, -1)
	};
}	

void HexNode::draw(sf::RenderWindow& window) const
{

	for (int i = 0; i < m_armsShapes.size(); ++i)
	{
		if (m_arms[i])
		{
			window.draw(m_armsShapes[i]);

			// auto& neighbor = m_neighbors[i];
			// sf::CircleShape neighborHex(4, 6);
			// neighborHex.setOrigin(sf::Vector2f(2, 2));
			// neighborHex.setPosition(node2World(neighbor));
			// neighborHex.setOutlineThickness(1.0f);
			// neighborHex.setOutlineColor(sf::Color(150, 150, 150));
			// neighborHex.setFillColor(sf::Color::Red);
			// window.draw(neighborHex);
		}
	}

	window.draw(m_circle);

	// sf::CircleShape hex(HEX_SIZE,6);
	// hex.setOrigin(sf::Vector2f(HEX_SIZE, HEX_SIZE));
	// hex.setPosition(node2World(m_pos));
	// hex.setOutlineThickness(2.0f);
	// hex.setOutlineColor(sf::Color::Black);
	// hex.setFillColor(sf::Color::Transparent);
	// window.draw(hex);


	// for	(auto& neighbor : m_neighbors)
	// {
	// 	sf::CircleShape neighborHex(4, 6);
	// 	neighborHex.setOrigin(sf::Vector2f(2, 2));
	// 	neighborHex.setPosition(node2World(neighbor));
	// 	neighborHex.setRotation(sf::degrees(30.f));
	// 	neighborHex.setOutlineThickness(1.0f);
	// 	neighborHex.setOutlineColor(sf::Color(150, 150, 150));
	// 	neighborHex.setFillColor(sf::Color::Red);
	// 	window.draw(neighborHex);
	// }
}

sf::Vector2f HexNode::node2World(const sf::Vector2i& position) const
{
    float q = static_cast<float>(position.x);
    float r = static_cast<float>(position.y);

    float x = HEX_SIZE * (std::sqrt(3.0f) * (q + r / 2.0f));
    float y = HEX_SIZE * (3.0f / 2.0f * r);

    return sf::Vector2f(x, y) + WINDOW_CENTER;
}

void HexNode::setLit(bool lit)
{
	m_lit = lit;
	m_circle.setFillColor(m_lit ? sf::Color::Yellow : sf::Color(200, 200, 200));
}

bool HexNode::isLit() const
{
	return m_lit;
}

void HexNode::rotateRight()
{
	std::rotate(m_arms.rbegin(), m_arms.rbegin() + 1, m_arms.rend());
}

void HexNode::rotateLeft()
{
	std::rotate(m_arms.begin(), m_arms.begin() + 1, m_arms.end());
}

bool HexNode::clickedOnNode(const sf::Vector2f& mousePos) const
{
	float dx = mousePos.x - m_circle.getPosition().x;
	float dy = mousePos.y - m_circle.getPosition().y;
	float distance = std::sqrt(dx * dx + dy * dy);
	if (distance <= RADIUS_SIZE)
		return true;
	return false;
}

const std::array<sf::Vector2i, 6>& HexNode::getNeighbors() const
{
	return m_neighbors;
}

bool HexNode::connectedTo(const HexNode& other) const
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