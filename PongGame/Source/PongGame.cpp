#include "PongGame.h"

PongGame::PongGame()
{
    bool success;
    
    //Create window
    m_Window = std::make_unique<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode({ m_Settings.width, m_Settings.height }), m_Settings.title));
    if (!m_Window->isOpen())
        std::cerr << "Failed to create window!" << std::endl;

    //Load icon
    sf::Image icon;
    success = icon.loadFromMemory(PongAssets::GetIconimageEmbedData(), PongAssets::GetIconimageEmbedSize());
    if (!success)
        std::cerr << "Failed to load icon image!" << std::endl;
    m_Window->setIcon(icon);

    //Create rendertexture
	m_RenderTexture = std::make_unique<sf::RenderTexture>();
    m_RenderTexture->setSmooth(true);
	success = m_RenderTexture->resize(sf::Vector2u(m_Settings.width, m_Settings.height));
    if (!success)
        std::cerr << "Failed to set size of rendertexture!" << std::endl;

    //Create view
    m_View.setSize(sf::Vector2f((float)m_Settings.width, (float)m_Settings.height));
	m_View.setCenter(sf::Vector2f((float)m_Settings.width / 2, (float)m_Settings.height / 2));
	Utilities::ResizeView(m_View, sf::Vector2u(m_Settings.width,m_Settings.height));

    //Create post-processing shader
    #include "postprocessingshader.glsl"
    m_PostProcessShader = std::make_unique<sf::Shader>();
    success = m_PostProcessShader->loadFromMemory(fragmentShader, sf::Shader::Type::Fragment);
    if (!success)
        std::cerr << "Failed to compile post-processing shader!" << std::endl;

    InitGameEntities();
}

void PongGame::InitGameEntities()
{
    //Init entities
    m_Player1 = std::make_unique<Player>(m_Settings, 0.1f, sf::Keyboard::Key::W, sf::Keyboard::Key::S);
    m_Player2 = std::make_unique<Player>(m_Settings, 0.9f, sf::Keyboard::Key::Up, sf::Keyboard::Key::Down);
    m_Ball = std::make_unique<Ball>(m_Settings);

    //Load music
    bool success;
	success = m_Music.openFromMemory(PongAssets::GetPongmusicEmbedData(), PongAssets::GetPongmusicEmbedSize());
    if (!success)
        std::cerr << "Failed to load music!" << std::endl;
    m_Music.setLooping(true);
    m_Music.play();
    
    //Load score sound
    success = m_ScoreSoundBuffer.loadFromMemory(PongAssets::GetBallescapesoundEmbedData(), PongAssets::GetBallescapesoundEmbedSize());
    if (!success)
        std::cerr << "Failed to load scoring sound!" << std::endl;
	m_ScoreSound = std::make_unique<sf::Sound>(m_ScoreSoundBuffer);

    //Load font
    success = m_Font.openFromMemory(PongAssets::GetObliviousfontEmbedData(), PongAssets::GetObliviousfontEmbedSize());
    if (!success)
        std::cerr << "Failed to load font!" << std::endl;

    //Init score text
    m_ScoreText = new sf::Text(m_Font, "", 30);
    m_ScoreText->setFillColor(sf::Color::White);
	Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: 0      |      Player 2: 0", { 0.5f, 0.05f }, *m_Window);

    //Init title text
    m_TitleText = new sf::Text(m_Font, "", 100);
	m_TitleText->setStyle(sf::Text::Bold);
	m_TitleText->setLetterSpacing(4.5f);
	m_TitleText->setFillColor(sf::Color::White);
	Utilities::SetTextAndPosition(*m_TitleText, m_Settings.title, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);

    //Init prompt text
    m_PromptText = new sf::Text(m_Font, "", 20);
    m_PromptText->setFillColor(sf::Color::White);
	m_PromptText->setLineSpacing(1.5f);
    m_PromptText->setOrigin({ 0.5f * m_TitleText->getLocalBounds().size.x, 0.5f * m_TitleText->getLocalBounds().size.y });
    m_PromptText->setPosition({ 0.5f * m_Window->getView().getSize().x, 0.7f * m_Window->getView().getSize().y });
	Utilities::SetTextAndPosition(*m_PromptText, m_Settings.menuPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
}

PongGame::~PongGame()
{
}

void PongGame::Run()
{
    while (m_Window->isOpen())
	{
		CalculateTime();
        ProcessEvents();
        if (m_GameState == GameState::Running)
            UpdateGame();
		Draw();
    }
}

void PongGame::CalculateTime()
{
    m_DeltaTime = m_Clock.restart().asSeconds();

	//Scrolling time is used for post-processing effects
    m_ScrollingTime += m_DeltaTime;
    if (m_ScrollingTime > 10.0f)
        m_ScrollingTime = 0.0f;
}

void PongGame::UpdateGame()
{
    m_Player1->Update(m_DeltaTime, *m_Window);
    m_Player2->Update(m_DeltaTime, *m_Window);
    m_Ball->Update(m_DeltaTime, *m_Window, *m_Player1, *m_Player2);
    CheckBallEscape();
}

void PongGame::AddScore(Player& player)
{
    player.AddScore();
	Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->GetCurrentScore()) + "      |      " + "Player 2: " + std::to_string(m_Player2->GetCurrentScore()), { 0.5f, 0.05f }, *m_Window);

	//Check if game should end
    if (player.GetCurrentScore() >= 11)
    {
	    Player& opponent = (&player == m_Player1.get()) ? *m_Player2 : *m_Player1;
        if (player.GetCurrentScore() - opponent.GetCurrentScore() >= 2)
			ChangeGameState(GameState::GameOver);
    }
	m_ScoreSound->play();
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
            Utilities::ResizeView(m_View, newSize);
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
			//Pause or move to menu when escape is pressed
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
				m_Player1->AddScore();
                    continue;
            }
#endif
			continue;
        }
    }
}

void PongGame::Draw() const
{
	//Draw to render texture entities depending on game state
	m_RenderTexture->clear();
    switch (m_GameState)
    {
        case GameState::Menu:
			m_RenderTexture->draw(*m_TitleText);
			m_RenderTexture->draw(*m_PromptText);
            break;
        case GameState::Running:
            m_RenderTexture->draw(*m_ScoreText);
            m_RenderTexture->draw(*m_Player1);
            m_RenderTexture->draw(*m_Player2);
            m_RenderTexture->draw(*m_Ball);
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
    }
	m_RenderTexture->display();

	//Draw render texture to screen with post-processing shader
    m_Window->clear();
    m_Window->setView(m_View);
    m_PostProcessShader->setUniform("time", m_ScrollingTime);
    m_PostProcessShader->setUniform("texture", sf::Shader::CurrentTexture);
    m_Window->draw(sf::Sprite(m_RenderTexture->getTexture()), m_PostProcessShader.get());
    m_Window->display();
}

void PongGame::ChangeGameState(GameState newState)
{
    switch (newState)
    {
        case GameState::Menu:
            //Set menu texts
            m_TitleText->setLetterSpacing(m_Settings.wideTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.title, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
			Utilities::SetTextAndPosition(*m_PromptText, m_Settings.menuPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::Menu;
			break;
        case GameState::Running:
            //Reset entites and texts if last state was not pause
            if (m_GameState == GameState::Paused)
            {
				m_GameState = GameState::Running;
                return;
            }
			m_Player1->Reset();
            m_Player2->Reset();
			m_Ball->Reset();
			Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->GetCurrentScore()) + "      |      " + "Player 2: " + std::to_string(m_Player2->GetCurrentScore()), { 0.5f, 0.05f }, *m_Window);
            m_GameState = GameState::Running;
            break;
        case GameState::Paused:
            //Set pause texts
            m_TitleText->setLetterSpacing(m_Settings.normalTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.pauseTitleText, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
            Utilities::SetTextAndPosition(*m_PromptText, m_Settings.pausePromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::Paused;
            break;
        case GameState::GameOver:
            //Set gameover texts
			m_TitleText->setLetterSpacing(m_Settings.normalTitleLetterSpacing);
			Utilities::SetTextAndPosition(*m_TitleText, m_Settings.gameoverTitleText, { 0.5f, m_Settings.topTitlePositionY }, *m_Window);
			Utilities::SetTextAndPosition(*m_ScoreText, "Player 1: " + std::to_string(m_Player1->GetCurrentScore()) + "      |      " + "Player 2: " + std::to_string(m_Player2->GetCurrentScore()), { 0.5f, 0.5f }, *m_Window);
            Utilities::SetTextAndPosition(*m_PromptText, m_Settings.gameOverPromptText, { 0.5f, m_Settings.promptTextPositionY }, *m_Window);
            m_GameState = GameState::GameOver;
            break;
    }
}