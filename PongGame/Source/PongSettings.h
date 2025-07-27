#pragma once
#include <string>

struct PongSettings 
{
	//Window settings
	const unsigned int width = 1280;
	const unsigned int height = 800;
	const std::string title = "Pong";

	//Player settings
	const float playerWidth = 50.0f;
	const float playerHeight = 250.0f;
	const float playerSpeed = 1.3f;

	//Ball settings
	const float ballRadius = 45.0f;
	const float ballSpeed = 1.0f;
};