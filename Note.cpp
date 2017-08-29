#include "Note.h"
#include "Sprite.h"
#include "GameSystem.h"

Note::Note(float sec, int judgedeltaLine)
{
	_noteSprite = NULL;
	_startTick = GameSystem::GetInstance()->GameTimeTick() - (int)(sec * 1000.0f);
	_judgeDeltaLine = judgedeltaLine;
}

Note::~Note()
{
	Deinit();
}

void Note::Update(int deltaTime)
{
	_noteSprite->Update(deltaTime);
	UpdatePosition(deltaTime);
	_noteSprite->SetPosition(_x, _y);
}

void Note::UpdatePosition(int deltaTime)
{
	_updateDuration += deltaTime;
	if (_updateDuration <= GameSystem::GetInstance()->GameTimeTick() + 1000)
	{
		int gameTimeTick = GameSystem::GetInstance()->GameTimeTick();
		int trackHeight = GameSystem::GetInstance()->GetTotalHeight();
		float positionRate = (float)_updateDuration / (float)gameTimeTick;
		float positionInSec = trackHeight * positionRate;

		_y = positionInSec - (trackHeight - GameSystem::GetInstance()->GetWindowHeight(800) + _judgeDeltaLine);
	}

	else
	{
		_isLive = false;
	}
	/*
	
	_updateDuration = (_updateDuration + (deltaTime));

	
	
	
	_noteSprite->SetPosition(_x, _y);
	*/
}

void Note::Render()
{
	_noteSprite->Render();
}

void Note::Init()
{
	_noteSprite = new Sprite("SpriteScript.csv"); // Texture 생성 대체
	_x = GameSystem::GetInstance()->GetWindowWidth(1024) / 2;

	int gameTimeTick = GameSystem::GetInstance()->GameTimeTick();
	_isLive = true;
	_updateDuration = _startTick;

	UpdatePosition(0);
}

void Note::Deinit()
{
	if (_noteSprite != NULL)
	{
		delete _noteSprite;
		_noteSprite = NULL;
	}
}

bool Note::IsLive()
{
	return _isLive;
}