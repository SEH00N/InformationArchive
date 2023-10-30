#pragma once
#include "pch.h"
#include "Object.h"

class Texture;

class Player : public Object
{
public:
	Player();
	~Player();

public:
	virtual void Update() override;
	virtual void Render(HDC hDC) override;
private:
	void CreateBullet();

private:
	Texture* texture;
};

