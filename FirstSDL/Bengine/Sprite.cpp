#include "Sprite.h"

#include "ResourceManager.h"

Sprite::Sprite() : 
	vboID(0)
{
}


Sprite::~Sprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}

void Sprite::init(float nx, float ny, float nw, float nh, std::string texturePath)
{
	x = nx;
	y = ny;
	w = nw;
	h = nh;

	texture = ResourceManager::getTexture(texturePath);

	if (vboID == 0)
		glGenBuffers(1, &vboID); 
	
	Vertex vertexData[6];

	// First triangle
	vertexData[0].setPosition(x + w, y + w);
	vertexData[0].setUV(1, 1);

	vertexData[1].setPosition(x, y + h);
	vertexData[1].setUV(0, 1);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0, 0);

	// Second triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0, 0);

	vertexData[4].setPosition(x + w, y);
	vertexData[4].setUV(1, 0);

	vertexData[5].setPosition(x + w, y + h);
	vertexData[5].setUV(1, 1);

	for (int i = 0; i < 6; i++)
	{
		vertexData[1].setColor(255, 255, 255);
	}
/*
	vertexData[1].setColor(0, 0, 255);

	vertexData[4].setColor(10, 255, 25);*/

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);


	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableVertexAttribArray(0);


	// Position			  
	// index, How many vars, type, normalize?, size, pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));

	// Color 
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

	// Draw Triangles!
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(0);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}