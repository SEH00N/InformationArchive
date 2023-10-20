#include "pch.h"
#include "KeyManager.h"
#include "Core.h"

void KeyManager::Clear()
{
	for (int i = 0; i < (int)KeyType::LAST; ++i)
	{
		KeyInfo& info = keyInfos[i];

		if (info.state == KeyState::Press || info.state == KeyState::Down)
			info.state = KeyState::Up;
		if (info.state == KeyState::Up)
			info.state = KeyState::None;
	}
}

void KeyManager::Init()
{
	for (int i = 0; i < (int)KeyType::LAST; ++i)
		keyInfos.push_back(KeyInfo{ KeyState::None, false });

	mousePosition = { 0, 0 };
}

void KeyManager::Update()
{
	HWND focusedWnd = GetFocus();
	if (focusedWnd == nullptr)
	{
		Clear();
		return;
	}

	for (int i = 0; i < (int)KeyType::LAST; ++i)
	{
		KeyInfo& info = keyInfos[i];
		if (GetAsyncKeyState(keyCodes[i]))
		{
			if (info.isPreviousCheck)
				info.state = KeyState::Press;
			else
				info.state = KeyState::Down;

			info.isPreviousCheck = true;
		}
		else
		{
			if (info.isPreviousCheck)
				info.state = KeyState::Up;
			else
				info.state = KeyState::None;

			info.isPreviousCheck = false;
		}
	}

	GetCursorPos(&mousePosition);
	ScreenToClient(Core::GetInstance()->GetHWnd(), &mousePosition);
}
