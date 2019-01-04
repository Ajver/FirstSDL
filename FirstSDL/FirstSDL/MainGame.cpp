#include "MainGame.h"

#include <Bengine/ImageLoader.h>
#include <Bengine/Bengine.h>
#include <Bengine/ResourceManager.h>

#include <string>

#include <glm/glm.hpp>



MainGame::MainGame() :
	time(0.0f),
	screenWidth(1024),
	screenHeight(768),
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

	constexpr float CAMERA_SPEED = 10.0f;
	constexpr float SCALE_SPEED = 1.02f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT: gameState = GameState::EXIT; break;
		case SDL_MOUSEMOTION: 
			//std::cout << "X> " << evnt.motion.x << "  |  " << evnt.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:
			inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}
	}
	

	if (inputManager.isKeyPressed(SDLK_w))
		camera.setPosition(camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED / camera.getScale()));
	if (inputManager.isKeyPressed(SDLK_s))
		camera.setPosition(camera.getPosition() - glm::vec2(0.0f, CAMERA_SPEED / camera.getScale()));
	if (inputManager.isKeyPressed(SDLK_a))
		camera.setPosition(camera.getPosition() - glm::vec2(CAMERA_SPEED / camera.getScale(), 0.0f));
	if (inputManager.isKeyPressed(SDLK_d))
		camera.setPosition(camera.getPosition() + glm::vec2(CAMERA_SPEED / camera.getScale(), 0.0f));
	if (inputManager.isKeyPressed(SDLK_q))
		camera.setScale(camera.getScale() / SCALE_SPEED);
	if (inputManager.isKeyPressed(SDLK_e))
		camera.setScale(camera.getScale() * SCALE_SPEED);
	if (inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		SDL_Quit();
		exit(144);
	}
}

void MainGame::initSystems() 
{
	// Init engine
	Bengine::init();

	window.create("Game engine!!!", screenWidth, screenHeight, Bengine::WindowFlags::DEFAULT);
	
	camera.init(screenWidth, screenHeight);

	spriteBatch.init();

	initShaders();
}

void MainGame::run() 
{
	initSystems();

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

		camera.update();

		switch (gameState)
		{
		case GameState::PLAY:
			time += 0.001f;
			processInput();
			render();
		}

		// Making program slower
		//for (int i = 0; i < 400000; i++)
		//{
		//	double r = rand() % (i * 2 % 2 + 1) + 1;
		//}

		elapsedTime = SDL_GetTicks() - startTicks;
		
		// Limit the fps to the max fps
		float maxET = 1000.0f / maxFPS;
		if (maxET > elapsedTime) {
			SDL_Delay(maxET - elapsedTime);
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

	// Set camera matrix
	GLint pLocation = colorProgram.getUnitformLocation("P");
	glm::mat4 cameraMatrix = camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	///////////////////////////////////////////////////////////////////////////////////////////////////
	spriteBatch.begin();

	// Draw stuff here
	glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GLuint textureID = Bengine::ResourceManager::getTexture("Graphics/Player.png").id;
	Bengine::Color col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	for (int i = 0; i < 1; i++)
	{
		spriteBatch.draw(position, uv, textureID, 1.0f, col);
		spriteBatch.draw(position + glm::vec4(30.0f, 0, 0, 0), uv, textureID, 1.0f, col);
	}

	spriteBatch.end();
	spriteBatch.renderBatch();
	///////////////////////////////////////////////////////////////////////////////////////////////////

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