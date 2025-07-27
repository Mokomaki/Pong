#include "Ball.h"


Ball::Ball(float x, float y, float radius, sf::Color color, float speed)
	: m_Position(x, y), m_Speed(speed), m_Radius(radius)
{

	m_Shape.setRadius(radius);
	m_Shape.setFillColor(color);
	m_Shape.setOrigin({ radius, radius });

	m_Direction = GetRandomDirection();
}

sf::Vector2f Ball::GetRandomDirection() 
{
	//Get the sign of the x direction randomly
	int signX = rand() % 2 == 0 ? 1 : -1;
	//Get the sign of the y direction randomly
	int signY = rand() % 2 == 0 ? 1 : -1;
	//Get the x direction randomly between 0.4 and 0.8
	float xdir = signX * (rand() % 40 + 40) / 100.0f;
	float ydir = signY * cos(xdir);
	return { xdir, ydir };
}

void Ball::Reset()
{
	m_Position = { 0.5f, 0.5f };
	m_Direction = GetRandomDirection();
}

void Ball::Draw(sf::RenderWindow& window)
{
	int windowHeight = window.getSize().y;
	int windowWidth = window.getSize().x;

	m_Shape.setPosition({ m_Position.x * windowWidth, m_Position.y * windowHeight });
	window.draw(m_Shape);
}

void Ball::Update(float deltaTime, sf::RenderWindow& window)
{

	m_Position.y += m_Speed * m_Direction.y * deltaTime;
	m_Position.x += m_Speed * m_Direction.x * deltaTime;

	// Clamp position to stay within the window bounds
	int windowHeight = window.getSize().y;
	int windowWidth = window.getSize().x;
	if (m_Position.y < 0 + m_Radius / windowHeight || m_Position.y > 1 - m_Radius / windowHeight)
		m_Direction.y *= -1;
	if (m_Position.x < 0 + m_Radius / windowWidth || m_Position.x > 1 - m_Radius / windowWidth)
		Reset();
}