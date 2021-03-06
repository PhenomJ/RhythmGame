#pragma once
#include "GameObject.h"

class Sprite;

class Note : public GameObject
{
private:
	bool _isLive;
	int _startTick;
	Sprite* _noteSprite;
	int _updateDuration;
	int _x;
	int _y;
	int _judgeDeltaLine;
	bool _isPass;

public :
	Note(float sec, int judgedeltaTime);
	~Note();
public:
	void Update(int deltaTime);
	void UpdatePosition(int deltaTime);
	void Render();
	void Init();
	void Deinit();
	bool IsLive();
	int GetNoteTime();
	bool isPass();
	void Pass();
	void SetPosition(int x);
};