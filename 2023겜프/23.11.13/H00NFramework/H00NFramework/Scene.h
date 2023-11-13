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
	virtual void FinalUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	const std::vector<Object*>& GetGroupObject(ObjectGroup type) const {
		return objList[(UINT)type];
	}
	void AddObject(Object* obj, ObjectGroup type) 
	{
		objList[(UINT)type].push_back(obj);
	}

private:
	std::vector<Object*> objList[(UINT)ObjectGroup::LAST];
};

