#include "Controller.h"
#include "Consts.h"

Controller::Controller()
	: m_window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "SFML Window")
{
}
void Controller::run()
{
	while (m_window.isOpen())
	{
		while (auto event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				m_window.close();
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2i pixelPos = mousePressed->position;
                sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);
                if (mousePressed->button == sf::Mouse::Button::Left)
                    m_board.handleClick(worldPos, true);
                else if (mousePressed->button == sf::Mouse::Button::Right) 
                    m_board.handleClick(worldPos, false);
				
                if (m_board.isSolved())
                {
                    m_middleRowCount += 2;
                    if (m_middleRowCount > 9)
                    {
                        m_window.close();
                    }
                    else
                    {
                        m_board = Board(m_middleRowCount);
                    }
                }
            }
        }
        m_window.clear(sf::Color::White);
        m_board.draw(m_window);
        m_window.display();
	}
}