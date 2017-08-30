#pragma once
#include "DLinkedList.h"
#include "GameObject.h"

class Sprite;
class Note;

enum eJudge
{
	NONE,
	JUDGE,
	FAIL
};

class Track : public GameObject
{
private:
	Sprite* _trackSprite;
	Sprite* _JudgeSprite;
	Sprite* _Destory;
	DLinkedList<Note*> _noteList;
	bool _isKeyDown;
	eJudge _judge;

public:
	Track();
	~Track();

	void Update(int deltaTime);
	void Render();
	void Deinit();
	void Init();

	//input
public:
	void KeyDown();
	void KeyUp();
};