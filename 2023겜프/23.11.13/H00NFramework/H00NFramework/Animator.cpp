#include "pch.h"
#include "Animator.h"

Animator::Animator() : owner{ nullptr }, currentAnimation{nullptr}
{
}

Animator::~Animator()
{
	std::map<std::wstring, Animation*>::iterator iter = animationMap.begin();
	for (iter = animationMap.begin(); iter != animationMap.end(); ++iter)
		delete iter->second;
}

void Animator::Update()
{
}

void Animator::Render(HDC hDC)
{
}

void Animator::CreateAnimation(const std::wstring name, Texture* tex, Vector2 leftTop, Vector2 sliceSize, Vector2 step, UINT frameCount)
{
}

Animation* Animator::FindAnimation(const std::wstring name)
{
}

void Animator::PlayAnimation(const std::wstring* name, bool repeat)
{
}
