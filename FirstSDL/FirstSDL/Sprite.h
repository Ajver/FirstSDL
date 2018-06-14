#pragma once

#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float, float, float, float);
	void render();
	
private:
	int x, y, w, h;

	// Vertex Buffer Object ID
	GLuint vboID;
};

