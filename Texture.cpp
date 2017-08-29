#include <stdio.h>
#include "Texture.h"
#include "GameSystem.h"
#include <SDL_image.h>

Texture::Texture(const char* fileName)
{
	char filePath[256];
	sprintf(filePath, "../Resource/Image/%s", fileName);
	_texture = IMG_LoadTexture(GameSystem::GetInstance()->GetRenderer(), filePath);
	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);
	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
}

Texture::~Texture()
{

}

void Texture::SetScale(float w, float h) // Scale Á¶Á¤Àº DestRect
{
	_destRect.w = _srcRect.w * w;
	_destRect.h = _srcRect.h * h;
}

void Texture::SetPosition(int xpos, int ypos)
{
	_destRect.x = xpos - GetRenderWidth() / 2;
	_destRect.y = ypos - GetRenderHeight() / 2;
}

void Texture::Render()
{
	SDL_RenderCopy (GameSystem::GetInstance()->GetRenderer(), _texture, &_srcRect, &_destRect);
}
	
int Texture::GetRenderWidth()
{
	return _destRect.w;
}

int Texture::GetRenderHeight()
{
	return _destRect.h;
}