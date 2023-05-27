#pragma once

#include "define.h"

class Stage
{
public:
	Stage();
	~Stage();

private:
	char stage[HEIGHT][WIDTH];
	POINT startPos;
	POINT endPos;

public:
	POINT GetStartPos() { return startPos; }
	POINT GetEndPos() { return endPos; }
	char GetBlock(int x, int y) { return stage[y][x]; }

public:
	bool Init(const char* fileName);
	void Render();
};