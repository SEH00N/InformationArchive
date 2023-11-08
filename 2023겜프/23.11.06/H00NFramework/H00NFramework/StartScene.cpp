#include "pch.h"
#include "Core.h"
#include "StartScene.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"
#include "CollisionManager.h"

void StartScene::Init()
{
	Object* object = new Player();
	object->SetScale(Vector2(100, 100));
	object->SetPosition(Vector2(600, 300));

	this->AddObject(object, ObjectGroup::Player);

	Vector2 resolution = Core::GetInstance()->GetResolution();
	int monsterCount = 5;
	float objectScale = 50;
	float moveDistance = 50;
	float term = (resolution.x - ((moveDistance + objectScale / 2.0f) * 2.0f)) / (monsterCount - 1);

	for (int i = 0; i < monsterCount; ++i)
	{
		Monster* monster = new Monster();
		monster->SetScale(Vector2(50, 50));
		monster->SetPosition(Vector2((moveDistance + objectScale / 2.0f + (float)i * term), 50.0f));
		monster->SetCenterPosition(monster->GetPosition());
		monster->SetMaxDistance(moveDistance);

		this->AddObject(monster, ObjectGroup::Monster);
	}

	CollisionManager::GetInstance()->CheckGroup(ObjectGroup::Monster, ObjectGroup::Bullet);
	CollisionManager::GetInstance()->CheckGroup(ObjectGroup::Monster, ObjectGroup::Player);
}

void StartScene::Update()
{
	this->Scene::Update();
}

void StartScene::Render(HDC hDC)
{
	this->Scene::Render(hDC);
}

void StartScene::Release()
{
	Scene::Release();
	CollisionManager::GetInstance()->CheckReset();
}
