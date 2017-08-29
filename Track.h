#pragma once
#include "DLinkedList.h"
#include "GameObject.h"

class Sprite;
class Note;

class Track : public GameObject
{
private:
	Sprite* _trackSprite;
	Sprite* _JudgeSprite;
	DLinkedList<Note*> _noteList;

public:
	Track();
	~Track();

	void Update(int deltaTime);
	void Render();
	void Deinit();
	void Init();
};