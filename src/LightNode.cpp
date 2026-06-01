#include "LightNode.h"


LightNode::LightNode(sf::Vector2i pos, std::array<bool, 6> arms)
    : m_pos(pos) , m_center(center), m_circle(RADIUS_SIZE) , m_arms(arms)
{
	m_circle.setOrigin(sf::Vector2f(RADIUS_SIZE, RADIUS_SIZE));
	m_circle.setPosition(nodeSpaceToWorldSpace(m_pos));
	setLit(center);

	float angle = 0.0f;
	for (auto& rectshape : m_armsShapes)
	{
		rectshape.setPosition(nodeSpaceToWorldSpace(m_pos));
		rectshape.setSize(sf::Vector2f(HEX_SIZE, 3.0f));
		rectshape.setOrigin(sf::Vector2f(0, 1.5f));
		rectshape.setFillColor(sf::Color::Black);

		rectshape.setRotation(sf::degrees(angle));
		angle += 60.0f;
	}

	for (int i = 0; i < NIGBORS_DIR.size(); i++)
		m_neighbors[i] = m_pos + NIGBORS_DIR[i];
}	

void LightNode::draw(sf::RenderWindow& window) const
{

	for (int i = 0; i < m_armsShapes.size(); ++i)
		if (m_arms[i])
			window.draw(m_armsShapes[i]);
		
	window.draw(m_circle);
}

sf::Vector2f LightNode::nodeSpaceToWorldSpace(const sf::Vector2i& position) const
{
    float q = static_cast<float>(position.x);
    float r = static_cast<float>(position.y);

    float x = HEX_SIZE * (std::sqrt(3.0f) * (q + r / 2.0f));
    float y = HEX_SIZE * (3.0f / 2.0f * r);

    return sf::Vector2f(x, y) + WINDOW_CENTER;
}

void LightNode::setLit(bool lit)
{
	m_lit = lit;
	m_circle.setFillColor(m_lit ? sf::Color::Yellow : sf::Color(200, 200, 200));
}

bool LightNode::isLit() const
{
	return m_lit;
}

void LightNode::rotateRight()
{
	std::rotate(m_arms.rbegin(), m_arms.rbegin() + 1, m_arms.rend());
}

void LightNode::rotateLeft()
{
	std::rotate(m_arms.begin(), m_arms.begin() + 1, m_arms.end());
}

bool LightNode::mouseOverNode(const sf::Vector2f& mousePos) const
{
	float dx = mousePos.x - m_circle.getPosition().x;
	float dy = mousePos.y - m_circle.getPosition().y;
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