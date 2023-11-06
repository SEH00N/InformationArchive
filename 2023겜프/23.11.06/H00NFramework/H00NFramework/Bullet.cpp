#include "pch.h"
#include "Bullet.h"
#include "Texture.h"
#include "TimeManager.h"
#include "ResManager.h"

Bullet::Bullet() : theta{ 0.f }, direction{ 0.f, 0.f }, texture{ nullptr }
{
	texture = ResManager::GetInstance()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
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
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	Vector2 pos = GetPosition();
	Vector2 scale = GetScale();

	TransparentBlt(
		hDC,
		pos.x - scale.x / 2, pos.y - scale.y / 2,
		width, height,
		texture->GetDC(),
		0, 0,
		width, height,
		RGB(255, 0, 255)
	);

	ComponentRender(hDC);

	//Vector2 position = GetPosition();
	//Vector2 scale = GetScale();
	//ELLIPSE_RENDER(hDC, position.x, position.y, scale.x, scale.y);
}
