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
	int _judgedeltaLine = 300;
	int _combo;
	Note* _note;

public:
	Track();
	~Track();

	void Update(int deltaTime);
	void Render();
	void Deinit();
	void Init();
	void SetPosition(int x, int y);
	//input
public:
	void KeyDown();
	void KeyUp();
};