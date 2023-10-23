#pragma once

class Object;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	std::vector<Object*> objList[(UINT)ObjectGroup::LAST];
};

