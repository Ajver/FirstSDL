#pragma once

#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Errors.h"
#include "Sprite.h"
#include "GLSLProgram.h"


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
	int WW, WH;
	SDL_Window *window;

	GameState gameState;

	Sprite testSprite;

	GLSLProgram colorProgram;

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void render();

	float _time;
};

