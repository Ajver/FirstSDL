#pragma once

#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Errors.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

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
	int WW, WH;
	SDL_Window *window;

	GameState gameState;

	GLTexture playerTexture;
	std::vector<Sprite*> sprites;
	float time; 
	
	GLSLProgram colorProgram;

	float fps;
	float maxFPS;

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void render();
};

