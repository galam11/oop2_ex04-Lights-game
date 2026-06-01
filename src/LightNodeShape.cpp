#include "LightNodeShape.h"
#include "Consts.h"

LightNodeShape::LightNodeShape(sf::Vector2i pos, sf::Vector2f worldPos, std::array<bool, 6> arms)
	: m_center(RADIUS_SIZE)
{
	m_transfrom.translate(worldPos);
	
	int lines = std::count_if(arms.cbegin(), arms.cend(), [](bool val) { return val; });

	m_lines.setPrimitiveType(sf::PrimitiveType::Lines);
	m_lines.resize(lines * 2);

	for (int i = 0; i < NIGBORS_DIR.size(); i++)
	{
		m_lines[i * 2] = sf::Vertex{ .position = sf::Vector2f(0,0) , .color = sf::Color::Black };
		m_lines[i * 2 + 1] = sf::Vertex{ .position = ((sf::Vector2f)NIGBORS_DIR[i] * HEX_SIZE) , .color = sf::Color::Black };
	}

}

void LightNodeShape::draw(sf::RenderWindow& window) const
{
	window.draw(m_center);
	window.draw(m_lines, m_transfrom);
}

void LightNodeShape::setLit(bool lit)
{
	m_center.setFillColor(lit ? sf::Color::Yellow : sf::Color(200, 200, 200));
}

void LightNodeShape::rotateRight()
{
	m_transfrom.rotate(sf::degrees(60.0f));
}

void LightNodeShape::rotateLeft()
{
	m_transfrom.rotate(sf::degrees(-60.0f));
}
