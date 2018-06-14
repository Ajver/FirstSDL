#pragma once

#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>


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

	void initSystems();
	void gameLoop();
	void processInput();
	void render();
};

