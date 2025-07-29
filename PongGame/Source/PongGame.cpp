#include "PongGame.h"

PongGame::PongGame()
{
    m_Window = new sf::RenderWindow(sf::VideoMode({ m_Settings.width, m_Settings.height }), m_Settings.title);
	m_RenderTexture = new sf::RenderTexture();
    m_RenderTexture->setSmooth(true);
	m_RenderTexture->resize(sf::Vector2u(m_Settings.width, m_Settings.height));
    m_View.setSize(sf::Vector2f(m_Settings.width, m_Settings.height));
	m_View.setCenter(sf::Vector2f(m_Settings.width/2, m_Settings.height/2));
	m_View = Utilities::ResizeView(m_View, sf::Vector2u(m_Settings.width,m_Settings.height));

    InitGameEntities();
}

void PongGame::InitGameEntities()
{
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
    m_ScoreText = new sf::Text(m_Font, "", 30);
    m_ScoreText->setFillColor(sf::Color::White);
	Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: 0      |      Player 2: 0", { 0.5f, 0.05f }, *m_Window);

    m_TitleText = new sf::Text(m_Font, "", 100);
	m_TitleText->setStyle(sf::Text::Bold);
	m_TitleText->setLetterSpacing(4.5f);
	m_TitleText->setFillColor(sf::Color::White);
	Utilities::SetTextAndPosition(*m_TitleText, m_Settings.title, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);

    m_PromptText = new sf::Text(m_Font, "", 20);
    m_PromptText->setFillColor(sf::Color::White);
	m_PromptText->setLineSpacing(1.5f);
    m_PromptText->setOrigin({ 0.5f * m_TitleText->getLocalBounds().size.x, 0.5f * m_TitleText->getLocalBounds().size.y });
    m_PromptText->setPosition({ 0.5f * m_Window->getView().getSize().x, 0.7f * m_Window->getView().getSize().y });
	Utilities::SetTextAndPosition(*m_PromptText, m_Settings.menuPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
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
    
	Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->m_CurrentScore) + "      |      " + "Player 2: " + std::to_string(m_Player2->m_CurrentScore), { 0.5f, 0.05f }, *m_Window);

	//Check if game should end
    if (player.m_CurrentScore >= 11)
    {
	    Player& opponent = (&player == m_Player1) ? *m_Player2 : *m_Player1;
        if (player.m_CurrentScore - opponent.m_CurrentScore >= 2)
        {
			ChangeGameState(GameState::GameOver);
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
            m_View = Utilities::ResizeView(m_View, newSize);
            continue;
		}


		//Key pressed event
        if (event->is<sf::Event::KeyPressed>())
        {
#ifdef DEBUG
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
                if(m_GameState == GameState::Paused || m_GameState == GameState::GameOver)
				    ChangeGameState(GameState::Menu);
                else if (m_GameState == GameState::Running)
				    ChangeGameState(GameState::Paused);
				continue;
            }

			//Start the game when enter is pressed
            if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Enter)
            {
                if (m_GameState == GameState::Running)
                    continue;
                ChangeGameState(GameState::Running);
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
	m_RenderTexture->clear();
	//m_RenderTexture->setView(m_View);
    switch (m_GameState)
    {
        case GameState::Menu:
			m_RenderTexture->draw(*m_TitleText);
			m_RenderTexture->draw(*m_PromptText);
            //m_Window->draw(*m_PromptText);
			//m_Window->draw(*m_TitleText);
            break;
        case GameState::Running:
            m_RenderTexture->draw(*m_ScoreText);
	    	m_Player1->Draw(*m_RenderTexture);
	    	m_Player2->Draw(*m_RenderTexture);
	    	m_Ball->Draw(*m_RenderTexture);
            break;
        case GameState::Paused:
            m_RenderTexture->draw(*m_TitleText);
            m_RenderTexture->draw(*m_PromptText);
            break;
        case GameState::GameOver:
            m_RenderTexture->draw(*m_TitleText);
            m_RenderTexture->draw(*m_ScoreText);
            m_RenderTexture->draw(*m_PromptText);
            break;
        default:
            break;
    }
	m_RenderTexture->display();
    m_Window->clear();
	
    m_Window->setView(m_View);
	m_Window->draw(sf::Sprite(m_RenderTexture->getTexture()));
    m_Window->display();
}

void PongGame::ChangeGameState(GameState newState)
{
    switch (newState)
    {
        case GameState::Menu:
            m_TitleText->setLetterSpacing(m_Settings.wideTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.title, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
			Utilities::SetTextAndPosition(*m_PromptText, m_Settings.menuPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::Menu;
			break;
        case GameState::Running:
            if (m_GameState == GameState::Paused)
            {
				m_GameState = GameState::Running;
                return;
            }
			m_Player1->Reset();
            m_Player2->Reset();
			m_Ball->Reset();

			Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->m_CurrentScore) + "      |      " + "Player 2: " + std::to_string(m_Player2->m_CurrentScore), { 0.5f, 0.05f }, *m_Window);

            m_GameState = GameState::Running;
            break;
        case GameState::Paused:
            m_TitleText->setLetterSpacing(m_Settings.normalTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.pauseTitleText, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
            Utilities::SetTextAndPosition(*m_PromptText, m_Settings.pausePromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::Paused;
            break;
        case GameState::GameOver:
			m_TitleText->setLetterSpacing(m_Settings.normalTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.gameoverTitleText, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
			Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->m_CurrentScore) + "      |      " + "Player 2: " + std::to_string(m_Player2->m_CurrentScore), { 0.5f, 0.5f }, *m_Window);
            Utilities::SetTextAndPosition(*m_PromptText, m_Settings.gameOverPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::GameOver;
            break;
        default:
			break;

    }
}