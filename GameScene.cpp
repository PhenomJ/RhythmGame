#include "GameScene.h"
#include "Track.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "SDL_mixer.h"
#include <stdio.h>

GameScene::GameScene()
{
	_backgroundSprite = NULL;
}

GameScene::~GameScene()
{
	Deinit();
}

void GameScene::Update(int deltaTime)
{
	if (_gameDuration <= GameSystem::GetInstance()->GameTimeTick() + 1500)
	{
		_backgroundSprite->Update(deltaTime);
		_track->Update(deltaTime);
		_gameDuration += deltaTime;
	}
	
	else
	{
		GameSystem::GetInstance()->Quit();
	}
}
void GameScene::Render()
{
	_backgroundSprite->Render();
	_track->Render();
}
void GameScene::Deinit()
{
	_track->Deinit();
	if (_backgroundSprite != NULL)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
}

void GameScene::Init()
{
	_backgroundSprite = new Sprite("BackGroundSprite.csv", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_track = new Track();
	_track->Init();
	_gameDuration = 0;

	int result = Mix_Init(MIX_INIT_MP3);
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music* music = Mix_LoadMUS("../Resource/Music/SadStory.mp3");
		if (music != NULL)
		{
			Mix_PlayMusic(music, 0);
		}
	}

	else
	{
		printf("File Open Error (.mp3)");
	}
}

void GameScene::KeyDown(int keydown)
{
	switch (keydown)
	{
	case SDLK_SPACE:
			_track->KeyDown();
			break;
	}
}

void GameScene::KeyUp(int keyup)
{
	switch (keyup)
	{
	case SDLK_SPACE:
		_track->KeyUp();
		break;
	}
}