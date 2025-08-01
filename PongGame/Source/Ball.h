#pragma	once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include "Player.h"
#include "PongAssets.h"
#include "Utilities.h"
#include "PongSettings.h"

class Ball : public sf::Drawable{
public:
	Ball(const PongSettings& settings);
	void Update(float deltaTime,const sf::RenderWindow& window,const Player& player1,const Player& player2);
	void Reset();
	inline sf::Vector2f GetPosition() const { return m_Position; }
	inline float GetRadius() const { return m_Radius; }
private:
	sf::Vector2f GetRandomDirection();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::CircleShape m_Shape;
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Radius;
	float m_Speed;
	float m_CurrentSpeed;
	float m_Acceleration = 0.05f;
	bool m_CanTurn = true;
	sf::SoundBuffer m_BallHitBuffer;
	std::unique_ptr<sf::Sound> m_BallHitSound;
};