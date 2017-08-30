#include "GameSystem.h"
#include <stdio.h>
#include <SDL.h>

GameSystem* GameSystem::_Instance= NULL;

GameSystem::GameSystem()
{

}

GameSystem* GameSystem::GetInstance()
{
	if (_Instance == NULL)
		_Instance = new GameSystem();
	return _Instance;
}

int GameSystem::GetWindowWidth()
{
	return 1024;
}

int GameSystem::GetWindowHeight()
{
	return 800;
}

void GameSystem::SetRenderer(SDL_Renderer* sdlRenderer)
{
	_sdlRenderer = sdlRenderer;
}

SDL_Renderer* GameSystem::GetRenderer()
{
	return _sdlRenderer;
}

int GameSystem::GameTimeTick()
{
	return _GameTimeTick;
}

void GameSystem::SetGameTime(float sec)
{
	_GameTimeTick = (int)(sec * 1000.0f);
}

int GameSystem::GetTotalHeight()
{
	return _trackHeight;
}

void GameSystem::SetTrackHeight(int height)
{
	_trackHeight = height;
}

void GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}