#pragma once

struct Position
{
	float x, y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex
{
	Position position;
	
	Color color;
};