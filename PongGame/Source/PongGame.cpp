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
        while (const std::optional event = m_Window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_Window->close();
        }

        ProcessInput();
		Draw();
    }
}

void PongGame::ProcessInput()
{
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
}

void PongGame::Draw()
{
    m_Window->clear();
    switch (m_GameState)
    {
    case GameState::Running:
        break;
    case GameState::Paused:
        break;
    case GameState::GameOver:
        break;
    default:
        break;
    }
    m_Window->display();
}