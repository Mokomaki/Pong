#pragma once
#include <SFML/Graphics.hpp>

namespace Utilities
{
	float Clamp(float value, float min, float max);

	sf::Vector2f CircleAABBCollision(const sf::Vector2f& circleCenter, float radius, const sf::FloatRect& aabb);

	void SetTextAndPosition(sf::Text& text, const std::string& str, const sf::Vector2f& position, const sf::RenderWindow& window);

	void ResizeView(sf::View& view, const sf::Vector2u& windowSize);
}