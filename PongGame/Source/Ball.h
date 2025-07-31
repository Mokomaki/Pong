#pragma	once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

class Ball {
public:
	Ball(float x, float y, float radius, sf::Color color, float speed);
	void Update(float deltaTime,const sf::RenderWindow& window,const Player& player1,const Player& player2);
	void Draw(sf::RenderTarget& target);
	void Reset();
	sf::Vector2f GetPosition() const { return m_Position; }
	float GetRadius() const { return m_Radius; }
private:
	sf::Vector2f GetRandomDirection();
private:
	sf::CircleShape m_Shape;
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Radius;
	float m_Speed;
	float m_CurrentSpeed;
	float m_Acceleration = 0.05f;
	bool m_CanTurn = true;
	sf::Sound* m_BallHitSound;
	sf::SoundBuffer m_BallHitBuffer;
};