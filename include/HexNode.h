#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Consts.h"

class HexNode 
{
public:
	HexNode() = default;
	HexNode(sf::Vector2i pos, std::array<bool, 6> arms, bool center = false);
	void draw(sf::RenderWindow& window) const;
	void setLit(bool lit);
	bool isLit() const;

	void rotateRight();
	void rotateLeft();
	bool clickedOnNode(const sf::Vector2f& mousePos) const;

	const std::array<sf::Vector2i, 6>& getNeighbors() const;

	bool connectedTo(const HexNode& other) const;

private:
	bool m_center = false;
	bool m_lit = false;
	std::array<bool, 6> m_arms = {false};
	std::array<sf::RectangleShape, 6> m_armsShapes;
	std::array<sf::Vector2i, 6> m_neighbors;

	sf::CircleShape m_circle;
	sf::Vector2i m_pos;
	sf::Vector2f node2World(const sf::Vector2i& position) const;
};