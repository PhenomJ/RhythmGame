#include "Sprite.h"
#include "GameSystem.h"
#include "Texture.h"
#include "DLinkedList.h"
#include <stdio.h>
#include <string.h>

Sprite::Sprite(const char* fileName)
{	
	_frameDuration = 0;
	_aniSpeed = 10000 / 60; // 60 -> Fps
	
	DLinkedList<Texture*> linkedlist;
	char filePath[256];
	sprintf(filePath, "../Resource/%s", fileName);
	char* textureName;
	float scaleWidth;
	float scaleHeight;

	FILE* fp = fopen(filePath, "r");
	if (fp == NULL)
	{
		printf("File Open Error");
	}

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);

	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);

		if (record == NULL)
			break;
		{
			char* token = strtok(record, ",");
			textureName = token;

			token = strtok(NULL, ",");
			scaleWidth = atof(token);

			token = strtok(NULL, ",");
			scaleHeight = atof(token);

			Texture* texture = new Texture(textureName);

			texture->SetScale(scaleWidth, scaleHeight);

			texture->SetPosition(_x, _y);

			linkedlist.Append(texture);
		}
	}

	fclose(fp);
	
	_frameMaxCount = linkedlist.Count();
	_textureFrame = new Array<Texture*>(_frameMaxCount);

	int frame = 0;
	DLinkedListIterator<Texture*> itr = linkedlist.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		Texture* texture = itr.Item();
		_textureFrame->Set(frame, texture);
		frame++;
	}

	_frame = 0;
}

Sprite::~Sprite()
{

}

void Sprite::Render()
{
	_textureFrame->Get(_frame)->Render();
}

void Sprite::Update(int deltaTime)
{
	_frameDuration += deltaTime;
	if (_aniSpeed < _frameDuration)
	{
		_frameDuration = 0;
		_frame = (_frame + 1) % _frameMaxCount;
	
	}

	Texture* texture = _textureFrame->Get(_frame);
	texture->SetPosition(_x, _y);

}

void Sprite::SetPosition(int x, int y)
{
	_x = x;
	_y = y;

	Texture* texture = _textureFrame->Get(_frame);
	texture->SetPosition(_x, _y);
}