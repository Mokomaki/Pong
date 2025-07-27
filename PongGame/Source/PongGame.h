#pragma once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"
#include "Player.h"

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
	void ProcessEvents();
private:
	sf::RenderWindow* m_Window;
	sf::View m_View;
	PongSettings m_Settings;
	float m_deltaTime = 0.0f;
	GameState m_GameState = GameState::Running;
	Player* m_Player1;
	Player* m_Player2;
};