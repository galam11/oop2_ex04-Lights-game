#include "LightNodeShape.h"
#include "Consts.h"

LightNodeShape::LightNodeShape(sf::Vector2i pos, std::array<bool, 6> arms)
	: m_center(RADIUS_SIZE)
{
	auto worldPos = nodeSpaceToWorldSpace(pos);

	m_center.setOrigin(sf::Vector2f(RADIUS_SIZE, RADIUS_SIZE));
	m_center.setPosition(worldPos);
	m_center.setFillColor(OFF_COLOR);
	m_center.setOutlineColor(sf::Color::Black);
	m_center.setOutlineThickness(2);

	m_transfrom.translate(worldPos);
	
	int lines = std::count_if(arms.cbegin(), arms.cend(), [](bool val) { return val; });

	m_lines.setPrimitiveType(sf::PrimitiveType::Lines);
	m_lines.resize(lines * 2);

	for (int i = 0, j = 0; i < NIGBORS_DIR.size(); i++)
	{
		if (!arms[i]) continue;

		m_lines[j * 2] = sf::Vertex
		{ 
			.position = sf::Vector2f(0,0), 
			.color = sf::Color::Black 
		};

		m_lines[j * 2 + 1] = sf::Vertex
		{ 
			.position = (nodeSpaceToWorldSpace(NIGBORS_DIR[i]) - WINDOW_CENTER).normalized() * HEX_SIZE,
			.color = sf::Color::Black 
		};
		j++;
	}

}

void LightNodeShape::draw(sf::RenderWindow& window) const
{
	window.draw(m_lines, m_transfrom);
	window.draw(m_center);
}

sf::Vector2f LightNodeShape::nodeSpaceToWorldSpace(const sf::Vector2i& position) const
{
	float q = static_cast<float>(position.x);
	float r = static_cast<float>(position.y);

	float x = HEX_SIZE * (std::sqrt(3.0f) * (q + r / 2.0f));
	float y = HEX_SIZE * (3.0f / 2.0f * r);

	return sf::Vector2f(x, y) + WINDOW_CENTER;
}

void LightNodeShape::setLit(bool lit) 
{ 
	m_center.setFillColor(lit ? ON_COLOR : OFF_COLOR);
}

void LightNodeShape::rotateRight() { m_transfrom.rotate(sf::degrees( ROTATION_ANGLE)); }

void LightNodeShape::rotateLeft()  { m_transfrom.rotate(sf::degrees(-ROTATION_ANGLE)); }

sf::Vector2f LightNodeShape::getPosition() const { return m_center.getPosition(); }
