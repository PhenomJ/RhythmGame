#include "GameScene.h"
#include "Track.h"
#include "Sprite.h"
#include "GameSystem.h"
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
	_backgroundSprite = new Sprite("BackGroundSprite.csv");
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth(1024) / 2, GameSystem::GetInstance()->GetWindowHeight(800) / 2);
	_track = new Track();
	_track->Init();
	_gameDuration = 0;
}