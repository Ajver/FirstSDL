#pragma once

#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <Bengine/Errors.h>
#include <Bengine/Sprite.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/GLTexture.h>
#include <Bengine/Window.h>
#include <Bengine/Camera2D.h>
#include <Bengine/SpriteBatch.h>

#include <vector>

enum class GameState 
{
	PLAY,
	EXIT
};


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	int screenWidth, screenHeight;
	Bengine::Window window;
	Bengine::Camera2D camera;
	Bengine::SpriteBatch spriteBatch;

	GameState gameState;

	Bengine::GLTexture playerTexture;
	float time; 
	
	Bengine::GLSLProgram colorProgram;

	float fps;
	float maxFPS;

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void render();
};

