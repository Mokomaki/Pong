#pragma	once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Ball {
public:
	Ball(float x, float y, float radius, sf::Color color, float speed);
	void Update(float deltaTime, sf::RenderWindow& window, Player& player1, Player& player2);
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
	bool m_CanTurn = true;
};