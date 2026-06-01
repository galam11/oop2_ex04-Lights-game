#pragma once
#include <array>
#include <SFML/Graphics.hpp>

const float HEX_SIZE = 50.0f;
const float HEX_CLICABLE_SIZE = HEX_SIZE * 0.75f;
const float RADIUS_SIZE = 17.0f;
const float ROTATION_ANGLE = 60.0f;
const unsigned int WINDOW_WIDTH = 1100;
const unsigned int WINDOW_HEIGHT = 900;
const sf::Vector2f WINDOW_CENTER = { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f };

const std::array<const sf::Vector2i, 6> NIGBORS_DIR = {
	sf::Vector2i(1, 0), 
	sf::Vector2i(0, 1), 
	sf::Vector2i(-1, 1),
	sf::Vector2i(-1, 0), 
	sf::Vector2i(0, -1), 
	sf::Vector2i(1, -1)
};

const sf::Color ON_COLOR = sf::Color(255, 255, 0);
const sf::Color OFF_COLOR = sf::Color(100, 100, 0);
