#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StartScene.h"
#include "GameScene.h"

void SceneManager::RegisterScene(const std::wstring& sceneName, std::shared_ptr<Scene> scene)
{
	sceneMap.insert(sceneMap.end(), { sceneName, scene });
}

void SceneManager::LoadScene(const std::wstring& sceneName)
{
	if (currentScene != nullptr)
	{
		currentScene->Release();
		currentScene = nullptr;
	}

	auto iter = sceneMap.find(sceneName);
	if (iter != sceneMap.end())
	{
		currentScene = iter->second;
		currentScene->Init();
	}
}

void SceneManager::Init()
{
	currentScene = nullptr;

	RegisterScene(L"StartScene", std::make_shared<StartScene>());
	RegisterScene(L"GameScene", std::make_shared<GameScene>());

	LoadScene(L"StartScene");
}

void SceneManager::Update()
{
	currentScene->Update();
	currentScene->FinalUpdate();
}

void SceneManager::Render(HDC hDC)
{
	currentScene->Render(hDC);
}
