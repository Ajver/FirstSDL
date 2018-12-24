#include "MainGame.h"
#include "ImageLoader.h"

#include <string>


MainGame::MainGame() : 
	time(0.0f), 
	WW(1024), 
	WH(768), 
	window(nullptr), 
	gameState(GameState::PLAY)
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
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("First SDL program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		WW, WH, SDL_WINDOW_OPENGL);	

	if (window == nullptr) 
		fatalError("SDL Window could not be created!");
	
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	if (glContext == nullptr)
		fatalError("SDL_GL context could not be created!");

	GLenum error = glewInit();

	if (error != GLEW_OK)
		fatalError("Glew could not be initialized!");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	initShaders();
}

void MainGame::run() 
{
	initSystems();

	testSprite.init(-1, -1, 2, 2);

	//playerTexture = ImageLoader::loadPNG("Graphics/Player.png");

	gameLoop();
}

#include <chrono>

void MainGame::gameLoop() 
{
	auto start = std::chrono::system_clock::now();
	auto timer = start;

	int fpsCount = 0;

	while (gameState != GameState::EXIT) 
	{
		fpsCount++;

		switch (gameState)
		{
		case GameState::PLAY:
			time += 0.001f;
			processInput();
			render();
			break;
		}

		auto stop = std::chrono::system_clock::now();

		// Elapsed time
		std::chrono::duration<float> et = stop - start;
		std::chrono::duration<float> timerElapse = stop - timer;

		if (timerElapse.count() >= 1.0f) {
			std::cout << "FPS: " << fpsCount << std::endl;
			fpsCount = 0;
			timer = std::chrono::system_clock::now();
		}

	}
}

void MainGame::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorProgram.use();
	
	GLint timeLocation = colorProgram.getUnitformLocation("time");

	// Send time var into GPU
	glUniform1f(timeLocation, time);

	// Draw sprite
	testSprite.render();


	colorProgram.unuse();

	SDL_GL_SwapWindow(window);

}

void MainGame::initShaders()
{
	colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	colorProgram.addAtribute("vertexPosition");
	colorProgram.addAtribute("vertexColor");
	colorProgram.linkShaders();
}

