#include "PongGame.h"

PongGame::PongGame()
{
    m_Window = new sf::RenderWindow(sf::VideoMode({ m_Settings.width, m_Settings.height }), m_Settings.title);
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
    m_Ball = new Ball
    (
        0.5f,
        0.5f,
        m_Settings.ballRadius,
        sf::Color::White,
		m_Settings.ballSpeed
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
        switch (m_GameState)
        {
        case GameState::Running:
            UpdateGame();
            break;
        case GameState::Paused:
            break;
        case GameState::GameOver:
            break;
        default:
            break;
        }
		Draw();
    }
}

void PongGame::UpdateGame()
{
    m_Player1->Update(m_deltaTime, *m_Window);
    m_Player2->Update(m_deltaTime, *m_Window);
    m_Ball->Update(m_deltaTime, *m_Window, *m_Player1, *m_Player2);
    CheckBallEscape();
}

void PongGame::AddScore(Player& player)
{
    player.m_CurrentScore++;
#ifdef DEBUG
	std::cout << "Player1 score: " << m_Player1->m_CurrentScore << " | Player2 score: " << m_Player2->m_CurrentScore << std::endl;
#endif
	//Check if game should end
    if (player.m_CurrentScore >= 11)
    {
	    Player& opponent = (&player == m_Player1) ? *m_Player2 : *m_Player1;
        if (player.m_CurrentScore - opponent.m_CurrentScore >= 2)
        {
#ifdef DEBUG
			std::cout << "Game Over!" << std::endl;
#endif
            m_GameState = GameState::GameOver;
        }
    }
}

void PongGame::CheckBallEscape()
{
    //Check if the ball has escaped the left or right side of the screen
    if (m_Ball->GetPosition().x < -0.1f)
    {
		AddScore(*m_Player2);
        m_Ball->Reset();
    }
    else if (m_Ball->GetPosition().x > 1.1f)
    {
		AddScore(*m_Player1);
        m_Ball->Reset();
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
#if DEBUG
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R)
            {
				m_Ball->Reset();
			    continue;
            }
#endif
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
    m_Window->clear();
    switch (m_GameState)
    {
    case GameState::Running:
		m_Player1->Draw(*m_Window);
		m_Player2->Draw(*m_Window);
		m_Ball->Draw(*m_Window);
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