#pragma once
#include <SFML/Graphics.hpp>

namespace Utilities
{
	float Clamp(float value, float min, float max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	sf::Vector2f CircleAABBCollision(const sf::Vector2f& circleCenter, float radius, const sf::FloatRect& aabb)
	{
		sf::Vector2f direction = circleCenter - aabb.position;
		sf::Vector2f aabbHalfSize = { aabb.size.x / 2.0f, aabb.size.y / 2.0f };
		float x = Utilities::Clamp(direction.x, -aabbHalfSize.x, aabbHalfSize.x);
		float y = Utilities::Clamp(direction.y, -aabbHalfSize.y, aabbHalfSize.y);
		sf::Vector2f closestPoint = aabb.position + sf::Vector2f(x, y);
		direction = closestPoint - circleCenter;

		float diff = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		if (diff <= radius)
		{
			// Collision detected
			return direction.normalized();
		}
		// No collision
		return { 0.0f, 0.0f };
	}
}