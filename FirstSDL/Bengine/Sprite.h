#pragma once

#include <GL/glew.h>
#include <cstddef>
#include <string>

#include "Vertex.h"
#include "GLTexture.h"

namespace Bengine
{

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float, float, float, float, std::string);
		void render();

	private:
		int x, y, w, h;

		// Vertex Buffer Object ID
		GLuint vboID;

		GLTexture texture;
	};

}