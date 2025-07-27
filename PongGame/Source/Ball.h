#pragma	once
#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball(float x, float y, float radius, sf::Color color, float speed);
	void Update(float deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Reset();
private:
	sf::Vector2f GetRandomDirection();
private:
	sf::CircleShape m_Shape;
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Radius;
	float m_Speed;
};