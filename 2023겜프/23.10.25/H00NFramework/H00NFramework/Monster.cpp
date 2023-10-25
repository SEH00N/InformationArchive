#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"

Monster::Monster() : centerPosition{ Vector2(0, 0) }, direction{ 1 }, hp{ 5 }, maxDistance{ 50 }, speed{ 100 }
{
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vector2 position = GetPosition();
	position.x += speed * direction * DeltaTime;

	float distance = (abs(centerPosition.x - position.x) - maxDistance);
	if (distance > 0)
	{
		direction = -direction;
		position.x += distance * direction;
	}

	SetPosition(position);
}
