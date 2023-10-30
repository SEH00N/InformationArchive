#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet() : theta{ 0.f }, direction{ 0.f, 0.f }
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vector2 position = GetPosition();

	//float x = cosf(theta);
	//float y = sinf(theta);

	position.x += 600.f * direction.x * DeltaTime;
	position.y += 600.f * direction.y * DeltaTime;

	SetPosition(position);
}

void Bullet::Render(HDC hDC)
{
	Vector2 position = GetPosition();
	Vector2 scale = GetScale();
	ELLIPSE_RENDER(hDC, position.x, position.y, scale.x, scale.y);
}
