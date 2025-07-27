#pragma once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"

class PongGame
{
public:
	PongGame();
	~PongGame();
	void Run();

private:
	PongSettings m_Settings;
	sf::RenderWindow* m_Window;
};