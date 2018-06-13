#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void initSystems();

private:
	int WW, WH;
	SDL_Window *window;

};

