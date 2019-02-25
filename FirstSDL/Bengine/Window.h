#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace Bengine
{
	enum WindowFlags : unsigned int
	{
		// Noresizable, visible window
		DEFAULT = 0x0,

		// Window invisible
		INVISIBLE = 0x1,

		// Borderless and fillign the screen
		FULLSCREEN = 0x2,

		// Noresizable
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
