#include "PongGame.h"

PongGame::PongGame()
{
	m_Window = new sf::RenderWindow(sf::VideoMode({m_Settings.width, m_Settings.height}), m_Settings.title);
}

PongGame::~PongGame()
{
	delete m_Window;
}

void PongGame::Run()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (m_Window->isOpen())
    {
        while (const std::optional event = m_Window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_Window->close();
        }

        m_Window->clear();
		m_Window->draw(shape);
        m_Window->display();
    }
}