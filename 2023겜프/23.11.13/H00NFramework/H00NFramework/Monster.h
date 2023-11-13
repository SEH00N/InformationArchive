#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	~Monster();

public:
	virtual void Update() override;
	virtual void Render(HDC hDC) override;

public:
	virtual void EnterCollision(Collider* other) override;
	virtual void StayCollision(Collider* other) override;
	virtual void ExitCollision(Collider* other) override;

public:
	void SetSpeed(float speed) { this->speed = speed; }
	void SetCenterPosition(Vector2 pos) { this->centerPosition = pos; }
	void SetMaxDistance(float distance) { this->maxDistance = distance; }
	
public:
	const float& GetSpeed() const { return speed; }

private:
	Vector2 centerPosition;
	int direction;
	int hp;
	float maxDistance;
	float speed;
};
