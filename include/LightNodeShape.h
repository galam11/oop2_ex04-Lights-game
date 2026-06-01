#pragma once
#include <SFML/Graphics.hpp>

class LightNodeShape
{
public:
	LightNodeShape(sf::Vector2i pos, sf::Vector2f worldPos, std::array<bool, 6> arms);

	void draw(sf::RenderWindow& window) const;

	void setLit(bool lit);

	void rotateRight();
	void rotateLeft();

private:
	sf::VertexArray m_lines;
	sf::Transform m_transfrom;
	sf::CircleShape m_center;
};