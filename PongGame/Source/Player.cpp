#include "Player.h"

Player::Player(float x, float y, float width, float height, sf::Color color, float outlineThickness, float speed, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
	: m_Position(x, y), m_Speed(speed), m_UpKey(upKey), m_DownKey(downKey)
{
	m_HalfHeight = (height + (outlineThickness*2)) / 2;
	m_HalfWidth = (width + (outlineThickness * 2)) / 2;

	m_Shape.setSize({width, height});
	m_Shape.setFillColor(sf::Color::Black);
	m_Shape.setOutlineThickness(outlineThickness);
	m_Shape.setOutlineColor(color);
	m_Shape.setOrigin({ width / 2, height / 2 });
}

void Player::Draw(sf::RenderWindow& window)
{
	int windowHeight = window.getSize().y;
	int windowWidth = window.getSize().x;

	m_Shape.setPosition({m_Position.x * windowWidth, m_Position.y * windowHeight});
	window.draw(m_Shape);
}

void Player::Update(float deltaTime, sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(m_UpKey))
	{
		m_Position.y -= m_Speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(m_DownKey))
	{
		m_Position.y += m_Speed * deltaTime;
	}
	
	// Clamp position to stay within the window bounds
	int windowHeight = window.getSize().y;
	if (m_Position.y < 0 + m_HalfHeight / windowHeight) m_Position.y = 0 + m_HalfHeight / windowHeight;
	if (m_Position.y > 1 - m_HalfHeight / windowHeight) m_Position.y = 1 - m_HalfHeight / windowHeight;
}