#pragma once
#include <SDL.h>
#include <SDL_image.h>


class GameSystem
{
//Singleton
private:
	static GameSystem* _Instance;
	SDL_Renderer* _sdlRenderer;
	
public:
	static GameSystem* GetInstance();
	int GetWindowWidth(int width);
	int GetWindowHeight(int height);

	//Gameinfo
private:
	int _trackHeight;
	int _GameTimeTick;

public:
	void SetRenderer(SDL_Renderer* sdlRenderer);
	SDL_Renderer* GetRenderer();
	int GameTimeTick();
	void SetGameTime(float sec);
	int GetTotalHeight();
	void SetTrackHeight(int height);
	void Quit();
private:
	GameSystem();
public:
	~GameSystem();
};