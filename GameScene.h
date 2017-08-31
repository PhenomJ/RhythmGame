#pragma once
#include"DLinkedList.h"
#include "GameObject.h"

class Track;
class Sprite;

class GameScene : public GameObject
{
private:
	Track* _track;
	Track* _track1;
	Track* _track2;
	Sprite* _backgroundSprite;
	int _gameDuration;
public:
	GameScene();
	~GameScene();

public:
	void Update(int deltaTime);
	void Render();
	void Deinit();
	void Init();

	//input
public:
	void KeyDown(int keydown);
	void KeyUp(int keyup);
};