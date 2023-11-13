#pragma once

class Object;
class Animation;
class Texture;

class Animator
{
public:
	Animator();
	~Animator();

public:
	void Update();
	void Render(HDC hDC);

public:
	void CreateAnimation(const std::wstring name, Texture* tex, Vector2 leftTop, Vector2 sliceSize, Vector2 step, UINT frameCount);
	Animation* FindAnimation(const std::wstring name);
	void PlayAnimation(const std::wstring* name, bool repeat);

private:
	std::map<std::wstring, Animation*> animationMap;
	Animation* currentAnimation;
	Object* owner;
	friend class Object;
};

