#include "Controller.h"
#include "Consts.h"

Controller::Controller() : 
	m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML Window"),
	m_board(9)
{
	std::srand(std::time(nullptr));
	m_window.setFramerateLimit(60);
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		while (auto event = m_window.pollEvent())
			event->visit([this](const auto& ev) { handleEvent(ev); });

		if (m_board.isSolved())
			m_window.close();

		m_window.clear(sf::Color::White);

		m_board.draw(m_window);

		m_window.display();
	}
}

void Controller::handleEvent(const auto& event) { }

void Controller::handleEvent(const sf::Event::Closed&) { m_window.close(); }

void Controller::handleEvent(const sf::Event::MouseButtonPressed& mouseButtonPressedEvent)
{

	sf::Vector2f worldPos = m_window.mapPixelToCoords(mouseButtonPressedEvent.position);

	switch (mouseButtonPressedEvent.button)
	{
		using enum sf::Mouse::Button;

		case Left : m_board.handleClick(worldPos, true);  break;

		case Right: m_board.handleClick(worldPos, false); break;
	}	
}
