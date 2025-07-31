#include "Ball.h"
#include "Utilities.h"

Ball::Ball(float x, float y, float radius, sf::Color color, float speed)
	: m_Position(x, y), m_Speed(speed), m_Radius(radius), m_CurrentSpeed(speed)
{

	m_Shape.setRadius(radius);
	m_Shape.setFillColor(sf::Color::Black);
	m_Shape.setOutlineColor(color);
	m_Shape.setOutlineThickness(5.0f);
	m_Shape.setOrigin({ radius, radius });

	m_Direction = GetRandomDirection();

	m_BallHitBuffer.loadFromMemory(PongAssets::GetBallhitsoundEmbedData(), PongAssets::GetBallhitsoundEmbedSize());
	//m_BallHitBuffer.loadFromFile("../Resources/ballhit.ogg");
	m_BallHitSound = new sf::Sound(m_BallHitBuffer);
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
	m_CurrentSpeed = m_Speed;
}

void Ball::Draw(sf::RenderTarget& target)
{
	int windowHeight = target.getView().getSize().y;
	int windowWidth = target.getView().getSize().x;

	m_Shape.setPosition({ m_Position.x * windowWidth, m_Position.y * windowHeight });
	target.draw(m_Shape);
}

void Ball::Update(float deltaTime,const sf::RenderWindow& window,const Player& player1,const Player& player2)
{
	m_CurrentSpeed += m_Acceleration * deltaTime;

	m_Position.y += m_CurrentSpeed * m_Direction.y * deltaTime;
	m_Position.x += m_CurrentSpeed * m_Direction.x * deltaTime;

	// Clamp position to stay within the window bounds
	int windowHeight = window.getView().getSize().y;
	int windowWidth = window.getView().getSize().x;
	if (m_Position.y < 0 + m_Radius / windowHeight || m_Position.y > 1 - m_Radius / windowHeight)
	{
		m_BallHitSound->play();
		m_Direction.y *= -1;
	}

	// Reset the can turn flag if the ball is in the middle of the screen
	if(m_Position.x < 0.6f && m_Position.x > 0.4f)
		m_CanTurn = true;

	//Check for collision with players
	if (m_CanTurn)
	{
		sf::FloatRect player1BoundingBox = player1.GetBoundingBox();
		player1BoundingBox.position = { player1.GetPosition().x * windowWidth, player1.GetPosition().y * windowHeight};

		sf::Vector2f p1Collision = Utilities::CircleAABBCollision({ m_Position.x * windowWidth, m_Position.y * windowHeight}, m_Radius, player1BoundingBox);

		sf::FloatRect player2BoundingBox = player2.GetBoundingBox();
		player2BoundingBox.position = { player2.GetPosition().x * windowWidth, player2.GetPosition().y * windowHeight };

		sf::Vector2f p2Collision = Utilities::CircleAABBCollision({ m_Position.x * windowWidth, m_Position.y * windowHeight }, m_Radius, player2BoundingBox);
		
		//Turn if ball collides with either player
		if (p1Collision.length() > 0.0f || p2Collision.length() > 0.0f)
		{
			m_Direction.x *= -1;
			m_CanTurn = false;

			// If the collision is mostly vertical, invert the y direction
			if( p1Collision.y > 0.8f || p1Collision.y < -0.8f || p2Collision.y > 0.8f || p2Collision.y < -0.8f)
			{
				m_Direction.y *= -1;
			}
			m_BallHitSound->play();
		}
	}
}