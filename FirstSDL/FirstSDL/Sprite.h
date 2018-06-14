#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(int, int, int, int);	
	void draw();
	
private:
	int x, y, w, h;

};

