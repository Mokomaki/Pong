#include "Player.h"

Player::Player(const PongSettings& settings, float xPosition, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) 
	:m_Position(xPosition,0.5f), m_UpKey(upKey), m_DownKey(downKey), m_Speed(settings.playerSpeed)
{
	m_HalfHeight = (settings.playerHeight + (settings.playerOutlineThickness * 2)) / 2;
	m_HalfWidth = (settings.playerWidth + (settings.playerOutlineThickness * 2)) / 2;

	m_Shape.setSize({ settings.playerWidth, settings.playerHeight });
	m_Shape.setFillColor(sf::Color::Black);
	m_Shape.setOutlineThickness(settings.playerOutlineThickness);
	m_Shape.setOutlineColor(sf::Color::White);
	m_Shape.setOrigin({ m_Shape.getSize().x / 2, m_Shape.getSize().y / 2 });
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
}

void Player::Update(float deltaTime, const sf::RenderWindow& window)
{
	int windowHeight = (int)window.getView().getSize().y;
	int windowWidth = (int)window.getView().getSize().x;

	//Move based on input
	if (sf::Keyboard::isKeyPressed(m_UpKey))
		m_Position.y -= m_Speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(m_DownKey))
		m_Position.y += m_Speed * deltaTime;
	
	// Clamp position to stay within the window bounds
	if (m_Position.y < 0 + m_HalfHeight / windowHeight)
		m_Position.y = 0 + m_HalfHeight / windowHeight;

	if (m_Position.y > 1 - m_HalfHeight / windowHeight)
		m_Position.y = 1 - m_HalfHeight / windowHeight;

	m_Shape.setPosition({ m_Position.x * windowWidth, m_Position.y * windowHeight });
}

void Player::Reset()
{
	m_CurrentScore = 0;
	m_Position = sf::Vector2f(m_Position.x, 0.5f );
}