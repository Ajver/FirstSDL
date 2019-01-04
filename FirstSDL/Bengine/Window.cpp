#include "Window.h"

#include "Errors.h"


namespace Bengine
{

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string title, int w, int h, WindowFlags flags)
	{
		screenWidth = w;
		screenHeight = h;

		// Create SDL flags (OpenGL Flag is default)
		Uint32 sdlFlags = SDL_WINDOW_OPENGL;

		if (flags & WindowFlags::INVISIBLE)
			sdlFlags |= SDL_WINDOW_HIDDEN;

		if (flags & WindowFlags::FULLSCREEN)
			sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (flags & WindowFlags::BORDERLESS)
			sdlFlags |= SDL_WINDOW_BORDERLESS;


		sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			screenWidth, screenHeight, sdlFlags);

		if (sdlWindow == nullptr)
			fatalError("SDL Window could not be created!");

		SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);

		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created!");

		GLenum error = glewInit();

		if (error != GLEW_OK)
			fatalError("Glew could not be initialized!");

		// Chech the OpenGL version
		printf("*** Open GL Version: %s ***\n", glGetString(GL_VERSION));

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(sdlWindow);
	}

}