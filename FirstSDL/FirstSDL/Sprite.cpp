#include "Sprite.h"



Sprite::Sprite()
{
	vboID = 0;
}


Sprite::~Sprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}

void Sprite::init(float nx, float ny, float nw, float nh)
{
	x = nx;
	y = ny;
	w = nw;
	h = nh;

	if (vboID == 0)
		glGenBuffers(1, &vboID); 
	
	Vertex vertexData[6];

	// First triangle
	vertexData[0].position.x = x + w;
	vertexData[0].position.y = y + w;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + h;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	// Second triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + w;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + w;
	vertexData[5].position.y = y + h;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;

	vertexData[4].color.r = 10;
	vertexData[4].color.g = 255;
	vertexData[4].color.b = 25;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);


	// Position			  
	//Bytes, How many vars, type, normalize?, size, pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));

	// Color 
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}