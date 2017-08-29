#pragma once
#include <SDL_image.h>


class Texture
{
private:
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;

public:
	void SetScale(float x, float y);
	void SetPosition(int xpos, int ypos);
	void Render();
	int GetRenderWidth();
	int GetRenderHeight();

public:
	Texture(const char* fileName);
	~Texture();
};