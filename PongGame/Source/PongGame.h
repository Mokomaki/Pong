#pragma once
#include <SFML/Graphics.hpp>
#include "PongSettings.h"
#include "Player.h"
#include "Ball.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>

enum class GameState
{
	Menu,
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
	void InitGameEntities();
	void ChangeGameState(GameState newState);
private:
	sf::RenderWindow* m_Window;
	sf::RenderTexture* m_RenderTexture;
	sf::View m_View;
	sf::Font m_Font;
	PongSettings m_Settings;
	GameState m_GameState = GameState::Menu;
	float m_deltaTime = 0.0f;
	sf::Text* m_ScoreText;
	sf::Text* m_TitleText;
	sf::Text* m_PromptText;
	Player* m_Player1;
	Player* m_Player2;
	Ball* m_Ball;
};