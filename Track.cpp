#include "Track.h"
#include "Note.h"
#include "Sprite.h"
#include "GameSystem.h"
#include <stdio.h>
#include <stdlib.h>

Track::Track()
{
	_trackSprite = NULL;
	_JudgeSprite = NULL;
	_isKeyDown = false;
	_Destory = NULL;
	_judge = eJudge::NONE;
}
Track::~Track()
{

}
void Track::Update(int deltaTime)
{
	
	_trackSprite->Update(deltaTime);
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->IsLive())
		{
			itr.Item()->Update(deltaTime);
		}

		else
		{
			delete itr.Item();
			_noteList.Remove(itr);
		}

		int judgeTick = GameSystem::GetInstance()->GameTimeTick();
		int judgeStartTick = judgeTick - 100;
		int judgeEndTick = judgeTick + 300;

		if (judgeEndTick < itr.Item()->GetNoteTime() &&  false == itr.Item()->isPass())
		{
			itr.Item()->Pass();
			_judge = eJudge::FAIL;
		}
	}


	_JudgeSprite->Update(deltaTime);
	_Destory->Update(deltaTime);
}

void Track::Render()
{
	_trackSprite->Render();
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Render();
	}
	_JudgeSprite->Render();
	_Destory->Render();
}

void Track::Deinit()
{
	if (_trackSprite != NULL)
	{
		delete _trackSprite;
		_trackSprite = NULL;
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Deinit();
		delete itr.Item();
		_noteList.Remove(itr);
	}

	if (_trackSprite != NULL)
	{
		delete _JudgeSprite;
		_JudgeSprite = NULL;
	}

	if (_Destory != NULL)
	{
		delete _Destory;
		_Destory = NULL;
	}
}

void Track::Init()
{
	int judgedeltaLine = 300;
	_trackSprite = new Sprite("track.csv", true);
	_JudgeSprite = new Sprite("JudgeLine.csv", true);
	_trackSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_JudgeSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2 + judgedeltaLine);

	_Destory = new Sprite("Destory.csv", false);
	_Destory->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2 + judgedeltaLine);

	int gameTime = GameSystem::GetInstance()->GameTimeTick();
	//float sec = 0.0f;
	int deltaTick = 0;
	for (int noteTick = 0; noteTick < gameTime;)
	{
		int randValue = rand() % 5;

		switch (randValue)
		{
		case 0:
			deltaTick = 250;
			break;
		case 1:
			deltaTick = 500;
			break;
		case 2:
			deltaTick = 750;
			break;
		case 3:
			deltaTick = 1000;
			break;
		case 4:
			deltaTick = 1500;
			break;
		default:
			deltaTick = 1750;
			break;
		}

		noteTick += deltaTick;

		float sec = (float)noteTick / 1000.0f;
		Note* note = new Note(sec, judgedeltaLine);
		note->Init();
		_noteList.Append(note);
	}
	
}

void Track::KeyDown()
{
	if (_isKeyDown)
		return;

	_isKeyDown = true;

	
	// ����
	int judgeTick = GameSystem::GetInstance()->GameTimeTick();
	int judgeStartTick = judgeTick - 100;
	int judgeEndTick = judgeTick + 300;
	//bool isJudge = false;

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->GetNoteTime() < judgeStartTick)
		{
			break;
		}

		if (judgeStartTick <= itr.Item()->GetNoteTime() && itr.Item()->GetNoteTime() <= judgeEndTick)
		{
			//isJudge = true;
			_judge = eJudge::JUDGE;
			break;
		}

		
	}

	switch (_judge)
	{
	case JUDGE:
		_Destory->Play();
		_noteList.Remove(itr);
		break;

	default:
		break;
	}

	/*if (isJudge == true)
	{
		_Destory->Play();
		_noteList.Remove(itr);
	}*/
}

void Track::KeyUp()
{
	_isKeyDown = false;
}