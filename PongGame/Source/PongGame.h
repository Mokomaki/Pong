#pragma once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"
#include "Player.h"
#include "Ball.h"
#include <iostream>

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
	void CheckBallEscape();
	void AddScore(Player& player);
	void UpdateGame();
	sf::View ResizeView(sf::View view, const sf::Vector2u& windowSize);
private:
	sf::RenderWindow* m_Window;
	sf::View m_View;
	sf::Font m_Font;
	sf::Text* m_ScoreText;
	PongSettings m_Settings;
	float m_deltaTime = 0.0f;
	GameState m_GameState = GameState::Running;
	Player* m_Player1;
	Player* m_Player2;
	Ball* m_Ball;
};