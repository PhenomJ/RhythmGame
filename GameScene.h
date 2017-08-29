#pragma once
#include"DLinkedList.h"
#include "GameObject.h"

class Track;
class Sprite;

class GameScene : public GameObject
{
private:
	Track* _track;
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
};