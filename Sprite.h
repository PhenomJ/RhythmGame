#pragma once
#include "Array.h"

class Texture;
class Sprite
{
private:
	Array<Texture*>* _textureFrame;
	int _frameMaxCount;
	int _frame;
	int _frameDuration;
	int _aniSpeed;
	int _x;
	int _y;
	

public :
	void Render();
	void Update(int deltaTime);
	void SetPosition(int x, int y);
public:
	Sprite(const char* fileName);
	~Sprite();
};
