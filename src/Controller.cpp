#include "Controller.h"
#include "Consts.h"

#include <fstream>
#include <iostream>

Controller::Controller() : 
	m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML Window")
{
	std::srand(std::time(nullptr));
	m_window.setFramerateLimit(60);

	loadMidRowPlayList();
	loadAndCreateText();

	nextLevel();
}

void Controller::run()
{
	while (m_window.isOpen())
	{
		while (auto event = m_window.pollEvent())
			event->visit([this](const auto& ev) { handleEvent(ev); });

		if (!m_paused && m_board.isSolved())
		{
			m_paused = true;
			m_gameOver = m_midRowQueue.empty();
		}

		m_window.clear(BACKROUND_COLOR);

		m_board.draw(m_window);

		if (m_paused)
		{
			m_gameOver ? m_window.draw(*m_winText) : m_window.draw(*m_nextLevelText);
			m_window.draw(*m_pressToContinueText);
		}

		m_window.display();
	}
}

void Controller::loadMidRowPlayList()
{
	std::ifstream playListFile(PLAY_LIST_PATH);

	if (!playListFile.is_open())
		throw std::runtime_error("Failed to open playlist file at '" + PLAY_LIST_PATH + "'");

	std::string line;

	while (std::getline(playListFile, line))
	{
		if (line.empty()) continue;

		std::istringstream iss(line);
		iss.exceptions(std::ios::failbit | std::ios::badbit);

		int temp;
		try
		{
			while (iss >> temp)
				m_midRowQueue.push(temp);
		}
		catch (const std::ios_base::failure&)
		{
			if (!iss.eof())
				throw std::runtime_error("Invalid data found in playlist: expected integers.");

		}
	}
}

void Controller::loadAndCreateText()
{
	if (!m_font.openFromFile(FONT_PATH))
		throw std::runtime_error("Failed to load font from '" + FONT_PATH + "'");

	
	auto setTextProperties = [this](std::unique_ptr<sf::Text>& text, const std::string& str)
	{
		text = std::make_unique<sf::Text>(m_font, str, 70);
		text->setOrigin(text->getLocalBounds().size / 2.0f);
		text->setPosition(WINDOW_CENTER - sf::Vector2f{0, 50.f});
		text->setOutlineThickness(2.f);
		text->setOutlineColor(sf::Color::Black);
	};
	
	setTextProperties(m_winText, WIN_TEXT);
	setTextProperties(m_nextLevelText, NEXT_LEVEL_TEXT);
	setTextProperties(m_pressToContinueText, PRESS_TO_CONTINUE_TEXT);

	m_pressToContinueText->move({0, 100.f});
}

void Controller::nextLevel()
{
	if (m_gameOver) 
		m_window.close();
	else
	{
		m_board = Board(m_midRowQueue.front());
		m_midRowQueue.pop();

		m_paused = false;
	}
}

void Controller::handleEvent(const sf::Event::MouseButtonPressed& mouseButtonPressedEvent)
{
	if (m_paused)
	{
		nextLevel();
		return;
	}

	sf::Vector2f worldPos = m_window.mapPixelToCoords(mouseButtonPressedEvent.position);

	switch (mouseButtonPressedEvent.button)
	{
		using enum sf::Mouse::Button;

	case Left: m_board.handleClick(worldPos, true);  break;

	case Right: m_board.handleClick(worldPos, false); break;
	}
}

void Controller::handleEvent(const auto& event) {}

void Controller::handleEvent(const sf::Event::Closed&) { m_window.close(); }

void Controller::handleEvent(const sf::Event::KeyPressed& keyPressedEvent) { if (m_paused) nextLevel(); }

