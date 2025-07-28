#include "PongGame.h"

PongGame::PongGame()
{
    m_Window = new sf::RenderWindow(sf::VideoMode({ m_Settings.width, m_Settings.height }), m_Settings.title);
    m_View.setSize(sf::Vector2f(m_Settings.width, m_Settings.height));
	m_View.setCenter(sf::Vector2f(m_Settings.width/2, m_Settings.height/2));
	m_View = ResizeView(m_View, sf::Vector2u(m_Settings.width,m_Settings.height));

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
	
    m_Font.openFromFile("../Resources/ObliviousFont.ttf");
	m_ScoreText = new sf::Text(m_Font, "Player 1: 0      |      Player 2: 0", 30);
    m_ScoreText->setOrigin({ 0.5f * m_ScoreText->getLocalBounds().size.x, 0.5f * m_ScoreText->getLocalBounds().size.y });
	m_ScoreText->setPosition({ 0.5f * m_Window->getSize().x, 0.05f * m_Window->getSize().y});
	m_ScoreText->setFillColor(sf::Color::White);
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
    
	m_ScoreText->setString("Player 1: " + std::to_string(m_Player1->m_CurrentScore) + "      |      Player 2: " + std::to_string(m_Player2->m_CurrentScore));
    m_ScoreText->setOrigin({ 0.5f * m_ScoreText->getLocalBounds().size.x, 0.5f * m_ScoreText->getLocalBounds().size.y });
    m_ScoreText->setPosition({ 0.5f * m_Window->getSize().x, 0.05f * m_Window->getSize().y });

	//Check if game should end
    if (player.m_CurrentScore >= 11)
    {
	    Player& opponent = (&player == m_Player1) ? *m_Player2 : *m_Player1;
        if (player.m_CurrentScore - opponent.m_CurrentScore >= 2)
        {
            m_ScoreText->setString("Player 1: " + std::to_string(m_Player1->m_CurrentScore) + "         GAME OVER!         Player 2: " + std::to_string(m_Player2->m_CurrentScore));
            m_ScoreText->setOrigin({ 0.5f * m_ScoreText->getLocalBounds().size.x, 0.5f * m_ScoreText->getLocalBounds().size.y });
			m_ScoreText->setPosition({ 0.5f * m_Window->getSize().x, 0.5f * m_Window->getSize().y });
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

		//Resize event
        if(event->is<sf::Event::Resized>())
        {
            sf::Vector2u newSize = event->getIf<sf::Event::Resized>()->size;
            m_View = ResizeView(m_View, newSize);
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
#ifdef DEBUG
            if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::A)
            {
				m_Player1->m_CurrentScore++;
                    continue;
            }
#endif
			continue;
        }
    }
}

void PongGame::Draw()
{
    m_Window->clear();
	m_Window->setView(m_View);
    switch (m_GameState)
    {
    case GameState::Running:
		m_Window->draw(*m_ScoreText);
		m_Player1->Draw(*m_Window);
		m_Player2->Draw(*m_Window);
		m_Ball->Draw(*m_Window);
        break;
    case GameState::Paused:
        break;
    case GameState::GameOver:
		m_Window->draw(*m_ScoreText);
        break;
    default:
        break;
    }
    m_Window->display();
}

sf::View PongGame::ResizeView(sf::View view, const sf::Vector2u& windowSize)
{
    float windowRatio = (float)windowSize.x / (float)windowSize.y;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) 
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY)));

    return view;
}