#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include "PongSettings.h"
#include "Player.h"
#include "Ball.h"
#include "Utilities.h"
#include "PongAssets.h"

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
	void Draw() const;
	void ProcessEvents();
	void CheckBallEscape();
	void AddScore(Player& player);
	void UpdateGame();
	void InitGameEntities();
	void ChangeGameState(GameState newState);
	void CalculateTime();
private:
	std::unique_ptr<sf::RenderWindow> m_Window;
	std::unique_ptr<sf::RenderTexture> m_RenderTexture;
	sf::View m_View;
	std::unique_ptr<sf::Shader> m_PostProcessShader;
	PongSettings m_Settings;
	sf::Clock m_Clock;
	GameState m_GameState = GameState::Menu;
	float m_DeltaTime = 0.0f;
	float m_ScrollingTime = 0.0f;
	sf::Music m_Music;
	sf::SoundBuffer m_ScoreSoundBuffer;
	std::unique_ptr<sf::Sound> m_ScoreSound;
	sf::Font m_Font;
	std::unique_ptr<sf::Text> m_ScoreText;
	std::unique_ptr<sf::Text> m_TitleText;
	std::unique_ptr<sf::Text> m_PromptText;
	std::unique_ptr<Player> m_Player1;
	std::unique_ptr<Player> m_Player2;
	std::unique_ptr<Ball> m_Ball;
};