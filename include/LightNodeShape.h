#pragma once
#include <SFML/Graphics.hpp>

class LightNodeShape
{
public:
	LightNodeShape() = default;
	LightNodeShape(sf::Vector2i pos, std::array<bool, 6> arms);

	void draw(sf::RenderWindow& window) const;

	void setLit(bool lit);

	void rotateRight();
	void rotateLeft();

	sf::Vector2f getPosition() const;

private:
	sf::VertexArray m_lines;
	sf::Transform m_transfrom;
	sf::CircleShape m_center;

	sf::Vector2f nodeSpaceToWorldSpace(const sf::Vector2i& position) const;
};