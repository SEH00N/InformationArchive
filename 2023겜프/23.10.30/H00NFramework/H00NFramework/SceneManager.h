#pragma once

class Scene;

class SceneManager
{
	SINGLE(SceneManager)

public:
	void RegisterScene(const std::wstring& sceneName, std::shared_ptr<Scene> scene);
	void LoadScene(const std::wstring& sceneName);

public:
	void Init();
	void Update();
	void Render(HDC hDC);

public:
	const std::shared_ptr<Scene>& GetCurrentScene() const { return currentScene; }

private:
	std::shared_ptr<Scene> currentScene;
	std::map<std::wstring, std::shared_ptr<Scene>> sceneMap;
};

