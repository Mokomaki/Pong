#pragma once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"

enum class GameState
{
	Running,
	Paused,
	GameOver
};

class PongGame
{
public:
	PongGame();
	~PongGame();
	void Run();
private:
	void Draw();
	void ProcessInput();
private:
	GameState m_GameState = GameState::Running;
	PongSettings m_Settings;
	sf::RenderWindow* m_Window;
};