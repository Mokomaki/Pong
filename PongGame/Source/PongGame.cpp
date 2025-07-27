#include "PongGame.h"

PongGame::PongGame()
{
	m_Window = new sf::RenderWindow(sf::VideoMode({m_Settings.width, m_Settings.height}), m_Settings.title);
	m_Player1 = new Player
    (
        0.1,
        0.5,
        m_Settings.playerWidth,
        m_Settings.playerHeight,
        sf::Color::White,
        5.0f,
        m_Settings.playerSpeed,
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::S
    );
    m_Player2 = new Player
    (
        0.9,
        0.5,
        m_Settings.playerWidth,
        m_Settings.playerHeight,
        sf::Color::White,
        5.0f,
        m_Settings.playerSpeed,
        sf::Keyboard::Key::Up,
        sf::Keyboard::Key::Down
    );
}

PongGame::~PongGame()
{
	delete m_Window;
}

void PongGame::Run()
{
	sf::Clock deltaClock;

    while (m_Window->isOpen())
	{
		m_deltaTime = deltaClock.restart().asSeconds();
        ProcessEvents();
		m_Player1->Update(m_deltaTime, *m_Window);
		m_Player2->Update(m_deltaTime, *m_Window);
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
    shape.setPosition({700.0f, 400.0f});

    m_Window->clear();
    switch (m_GameState)
    {
    case GameState::Running:
		m_Player1->Draw(*m_Window);
		m_Player2->Draw(*m_Window);
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