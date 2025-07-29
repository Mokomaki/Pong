#pragma once
#include <string>

struct PongSettings 
{
	//Window settings
	const unsigned int width = 1280;
	const unsigned int height = 800;
	const std::string title = "Pong";

	//Player settings
	const float playerWidth = 35.0f;
	const float playerHeight = 175.0f;
	const float playerOutlineThickness = 5.0f;
	const float playerSpeed = 1.3f;
	const float playerSideOffset = 0.05f;

	//Ball settings
	const float ballRadius = 30.0f;
	const float ballSpeed = 1.0f;

	//Menu settings
	const float wideTitleLetterSpacing = 4.5f;
	const float topTitlePositionY = 0.2f;
	const float normalTitleLetterSpacing = 1.0f;
	const float centerTitlePositionY = 0.5f;
	const float promptTextPositionY = 0.7f;
	const std::string pauseTitleText = "PAUSE";
	const std::string gameoverTitleText = "GAME OVER";
	const std::string menuPromptText = "Press  [ ENTER ]  to start\nControls: [ W ]  [ S ]  [ UP ]  [ DOWN ]\n[ ESC ]  for pause";
	const std::string pausePromptText = "Press  [ ENTER ]  to resume\nPress  [ ESC ]  to return to menu";
	const std::string gameOverPromptText = "Press  [ ENTER ]  to restart\nPress  [ ESC ]  to return to menu";
};