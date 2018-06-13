#include "MainGame.h"



MainGame::MainGame() {
	WW = 1024;
	WH = 768;

	window = nullptr;

	initSystems();
}


MainGame::~MainGame() {

}

void MainGame::initSystems() {
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("First SDL program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		WW, WH, SDL_WINDOW_OPENGL);

	
}

void MainGame::run() {

}

