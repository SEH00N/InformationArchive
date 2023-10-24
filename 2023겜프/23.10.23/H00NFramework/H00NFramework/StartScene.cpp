#include "pch.h"
#include "StartScene.h"
#include "Object.h"

void StartScene::Init()
{
	Object* object = new Object();
	object->SetScale(Vector2(100, 100));
	object->SetPosition(Vector2(600, 300));

	this->AddObject(object, ObjectGroup::Player);
}

void StartScene::Update()
{
	this->Scene::Update();
}

void StartScene::Render(HDC hDC)
{
	this->Scene::Render(hDC);
}