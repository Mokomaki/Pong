#pragma	once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"

class Player : public sf::Drawable{
public:
	Player(const PongSettings& settings, float xPosition , sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
	void Update(float deltaTime, const sf::RenderWindow& window);
	void Reset();
	inline sf::Vector2f GetPosition() const { return m_Position; }
	inline float GetHalfHeight() const { return m_HalfHeight; }
	inline float GetHalfWidth() const { return m_HalfWidth; }
	inline unsigned short GetCurrentScore() const { return m_CurrentScore; }
	inline void AddScore() { m_CurrentScore++; }
	inline sf::FloatRect GetBoundingBox() const {
		return sf::FloatRect({ m_Position.x, m_Position.y}, { m_HalfWidth * 2, m_HalfHeight * 2 });
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	unsigned short m_CurrentScore = 0;
	sf::Vector2f m_Position;
	sf::RectangleShape m_Shape;
	float m_HalfHeight;
	float m_HalfWidth;
	float m_Speed;
	sf::Keyboard::Key m_UpKey;
	sf::Keyboard::Key m_DownKey;
};