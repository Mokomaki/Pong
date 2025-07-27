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
    while (m_Window->isOpen())
    {


        ProcessEvents();
		Draw();
    }
}

void PongGame::ProcessEvents()
{
    while (const std::optional event = m_Window->pollEvent())
    {   
        //Close event
        if (event->is<sf::Event::Closed>())
        {
            m_Window->close();
            continue;
        }

		//Key pressed event
        if (event->is<sf::Event::KeyPressed>())
        {
			continue;
        }
		//Key released event
        if (event->is<sf::Event::KeyReleased>())
        {
			//Pause when escape is pressed
            if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape)
            {
                if (m_GameState == GameState::GameOver)
                    continue;
				m_GameState = (m_GameState == GameState::Running) ? GameState::Paused : GameState::Running;
            }
			continue;
        }
    }
}

void PongGame::Draw()
{
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color::Red);

    m_Window->clear();
    switch (m_GameState)
    {
    case GameState::Running:
        break;
    case GameState::Paused:
		m_Window->draw(shape);
        break;
    case GameState::GameOver:
        break;
    default:
        break;
    }
    m_Window->display();
}