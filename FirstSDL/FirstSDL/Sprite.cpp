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
	
	float vertexData[12];

	// First triangle
	vertexData[0] = x + w;
	vertexData[1] = y + w;

	vertexData[2] = x;
	vertexData[3] = y + h;

	vertexData[4] = x;
	vertexData[5] = y;

	// Second triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + w;
	vertexData[9] = y;

	vertexData[10] = x + w;
	vertexData[11] = y + h;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}