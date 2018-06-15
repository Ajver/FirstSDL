#pragma once

struct Vertex
{
	struct Position
	{
		float x, y;
	} position;
	
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};