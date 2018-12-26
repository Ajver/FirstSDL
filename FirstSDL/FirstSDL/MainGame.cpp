#include "MainGame.h"

#include <Bengine/ImageLoader.h>
#include <Bengine/Bengine.h>

#include <string>


MainGame::MainGame() :
	time(0.0f),
	WW(1024),
	WH(768),
	gameState(GameState::PLAY),
	maxFPS(60.0f)
{
} 


MainGame::~MainGame() 
{
}

void MainGame::processInput() 
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT: gameState = GameState::EXIT; break;
		case SDL_MOUSEMOTION: 
			//std::cout << "X> " << evnt.motion.x << "  |  " << evnt.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::initSystems() 
{
	// Init engine
	Bengine::init();

	window.create("Game engine!!!", WW, WH, Bengine::WindowFlags::DEFAULT);

	initShaders();
}

void MainGame::run() 
{
	initSystems();

	// Initialize sprites
	sprites.push_back(new Bengine::Sprite());
	sprites.back()->init(-0.5f, -1, 1, 1, "Graphics/ItemSpawner.png");

	//sprites.push_back(new Sprite());
	//sprites.back()->init(0, 0, 1, 1, "Graphics/ItemSpawner.png");

	sprites.push_back(new Bengine::Sprite());
	sprites.back()->init(0, 0, 1, 1, "Graphics/Player.png");

	gameLoop();
}

void MainGame::gameLoop() 
{
	int fpsCount = 0;
	float timer = SDL_GetTicks();
	float elapsedTime = 0;

	while (gameState != GameState::EXIT) 
	{
		// Used for delay
		float startTicks = SDL_GetTicks();

		fpsCount++;

		switch (gameState)
		{
		case GameState::PLAY:
			time += 0.001f;
			processInput();
			render();
		}

		//for (int i = 0; i < 400000; i++)
		//{
		//	double r = rand() % (i * 2 % 2 + 1) + 1;
		//}

		elapsedTime = SDL_GetTicks() - startTicks;
		
		// Limit the fps to the max fps
		if (1000.0f / maxFPS > elapsedTime) {
			SDL_Delay(1000.0f / maxFPS - elapsedTime);
		}

		elapsedTime = (SDL_GetTicks() - startTicks) / 1000.0f;
	
		if (SDL_GetTicks() - timer >= 1000.0f) {
			fps = fpsCount;
			std::cout << "FPS: " << fpsCount << std::endl;
			std::cout << "ET: " << elapsedTime << std::endl;
			fpsCount = 0;
			timer += 1000.0f;
		}
	}
}

void MainGame::render()
{
	glClearDepth(1.0);

	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable the shader
	colorProgram.use();

	// We are using texture uint 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, playerTexture.id);
	
	GLint textureLocation = colorProgram.getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	// Get uniform location
	//GLint timeLocation = colorProgram.getUnitformLocation("time");

	// Send time var into GPU
	//glUniform1f(timeLocation, time);

	// Draw sprite
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->render();
	}

	// Disable all textures
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable the shader
	colorProgram.unuse();

	window.swapBuffer();
}

void MainGame::initShaders()
{
	colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	colorProgram.addAtribute("vertexPosition");
	colorProgram.addAtribute("vertexColor");
	colorProgram.addAtribute("vertexUV");
	colorProgram.linkShaders();
}