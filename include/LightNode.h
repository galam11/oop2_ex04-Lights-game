#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Consts.h"
#include "LightNodeShape.h"

class LightNode 
{
public:
	LightNode() = default;
	LightNode(sf::Vector2i pos, std::array<bool, 6> arms);
	void draw(sf::RenderWindow& window) const;
	void setLit(bool lit);
	bool isLit() const;

	void rotateRight();
	void rotateLeft();
	bool mouseOverNode(const sf::Vector2f& mousePos) const;

	const std::array<sf::Vector2i, 6>& getNeighbors() const;

	bool connectedTo(const LightNode& other) const;

	
private:
	bool m_lit = false;
	std::array<bool, 6> m_arms = {false};
	//std::array<sf::RectangleShape, 6> m_armsShapes;
	std::array<sf::Vector2i, 6> m_neighbors;

	LightNodeShape m_shape;

	//sf::CircleShape m_circle;
	sf::Vector2i m_pos;
	
};