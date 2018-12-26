#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Bengine
{
	enum WindowFlags : unsigned int
	{
		// Create the window invisible
		DEFAULT = 0x0,
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string, int, int, WindowFlags = WindowFlags::DEFAULT);

		void swapBuffer();

		int getScreenWidth() { return screenWidth; }
		int getScreenHeight() { return screenHeight; }

	private:
		SDL_Window *sdlWindow;

		int screenWidth;
		int screenHeight;
	};

}
