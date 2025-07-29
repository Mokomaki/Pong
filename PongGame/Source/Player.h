#pragma	once
#include <SFML/Graphics.hpp>

class Player {
public:
	Player(float x, float y, float width, float height, sf::Color color,float outlineThickness, float speed, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
	void Update(float deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderTarget& target);
	void Reset();
	sf::Vector2f GetPosition() const { return m_Position; }
	float GetHalfHeight() const { return m_HalfHeight; }
	float GetHalfWidth() const { return m_HalfWidth; }
	sf::FloatRect GetBoundingBox() const {
		return sf::FloatRect({ m_Position.x, m_Position.y}, { m_HalfWidth * 2, m_HalfHeight * 2 });
	}
public:
	short m_CurrentScore = 0;
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_Shape;
	float m_HalfHeight;
	float m_HalfWidth;
	float m_Speed;
	sf::Keyboard::Key m_UpKey;
	sf::Keyboard::Key m_DownKey;
};