#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

namespace Utilities
{
	float Clamp(float value, float min, float max)
	{
		return (value > max) ? max : min;
	}

	sf::Vector2f CircleAABBCollision(const sf::Vector2f& circleCenter,float radius, const sf::FloatRect& aabb)
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

	void SetTextAndPosition(sf::Text& text, const std::string& str, const sf::Vector2f& position, const sf::RenderWindow& window)
	{
		text.setString(str);
		text.setOrigin({ text.getLocalBounds().size.x / 2, text.getLocalBounds().size.y / 2 });
		text.setPosition({ window.getView().getSize().x * position.x, window.getView().getSize().y * position.y });
	}

	void ResizeView(sf::View& view, const sf::Vector2u& newSize)
	{
		float windowRatio = (float)newSize.x / (float)newSize.y;
		float viewRatio = view.getSize().x / view.getSize().y;
		float sizeX = 1;
		float sizeY = 1;
		float posX = 0;
		float posY = 0;

		if (windowRatio < viewRatio)
		{
			sizeY = windowRatio / viewRatio;
			posY = (1 - sizeY) / 2.f;
		}
		else
		{
			sizeX = viewRatio / windowRatio;
			posX = (1 - sizeX) / 2.f;
		}

		view.setViewport(sf::FloatRect(sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY)));
	}
}