#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)ObjectGroup::LAST; ++i)
	{
		for (size_t j = 0; j < objList[i].size(); ++j)
			if(objList[i][j]->GetAlive())
				objList[i][j]->Update();
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)ObjectGroup::LAST; ++i)
	{
		for (size_t j = 0; j < objList[i].size(); ++j)
			if (objList[i][j]->GetAlive())
				objList[i][j]->FinalUpdate();
	}
}

void Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)ObjectGroup::LAST; ++i)
	{
		for (size_t j = 0; j < objList[i].size(); ++j)
		{
			if (objList[i][j]->GetAlive())
				objList[i][j]->Render(hDC);
			else
				objList[i].erase(objList[i].begin() + j);
		}
	}
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)ObjectGroup::LAST; ++i)
	{
		for (size_t j = 0; j < objList[i].size(); ++j)
			delete objList[i][j];

		objList[i].clear();
	}
}
