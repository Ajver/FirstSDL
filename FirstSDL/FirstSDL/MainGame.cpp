#include "MainGame.h"

#include <string>


MainGame::MainGame() :
	WW(1024),
	WH(768),
	_time(0),
	gameState(GameState::PLAY),
	window(nullptr)
{
	run();
}


MainGame::~MainGame() 
{}

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
	gameLoop();
}

void MainGame::gameLoop() 
{
	while (gameState != GameState::EXIT) 
	{
		processInput(); 
		_time += 0.01f;
		render();
	}
}

void MainGame::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	colorProgram.use();
	
	GLuint timeLocation = colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

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

