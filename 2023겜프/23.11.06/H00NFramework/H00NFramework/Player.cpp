#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "ResManager.h"
#include "PathManager.h"
#include "Scene.h"
#include "Texture.h"
#include "Collider.h"

Player::Player() : texture{nullptr}
{
	//std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
	//filePath += L"Texture\\planem.bmp";
	
	texture = ResManager::GetInstance()->TexLoad(L"Player", L"Texture\\plane.bmp");
	//texture->Load(filePath);
	CreateCollider();
	GetCollider()->SetScale(Vector2{80.f, 58.f});
	GetCollider()->SetOffset(Vector2{50.f, 0.f});
}

Player::~Player()
{
}

void Player::Update()
{
	Vector2 position = GetPosition();

	if (GetKeyPress(KeyType::Left))
		position.x -= 1000 * DeltaTime;
	if (GetKeyPress(KeyType::Right))
		position.x += 1000 * DeltaTime;

	if (GetKeyDown(KeyType::Space))
		CreateBullet();

	SetPosition(position);
}

void Player::Render(HDC hDC)
{
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	Vector2 pos = GetPosition();
	Vector2 scale = GetScale();

	//BitBlt(
	//	hDC, 
	//	pos.x - scale.x / 2, pos.y - scale.y / 2, 
	//	width, height, 
	//	texture->GetDC(), 
	//	0, 0, 
	//	SRCCOPY
	//);

	//TransparentBlt(
	//	hDC,
	//	pos.x - scale.x / 2, pos.y - scale.y / 2,
	//	width, height,
	//	texture->GetDC(),
	//	0, 0,
	//	width, height,
	//	RGB(255, 0, 255)
	//);

	StretchBlt(
		hDC,
		pos.x - scale.x / 2, pos.y - scale.y / 2,
		width, height,
		texture->GetDC(),
		0, 0,
		width, height,
		SRCCOPY
	);

	ComponentRender(hDC);
}

void Player::CreateBullet()
{
	Bullet* bullet = new Bullet();
	Vector2 bulletPos = GetPosition();
	bulletPos.y -= GetScale().y / 2.f;

	bullet->SetScale({25.f, 25.f});
	bullet->SetPosition(bulletPos);
	//bullet->SetDirection(-45 * Deg2Rad);
	bullet->SetDirection({-10.f, -15.f});

	SceneManager::GetInstance()->GetCurrentScene()->AddObject(bullet, ObjectGroup::Bullet);
}
