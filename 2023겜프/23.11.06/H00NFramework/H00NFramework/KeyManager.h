#pragma once

struct KeyInfo
{
	KeyState state;
	bool isPreviousCheck;
};

class KeyManager
{
	SINGLE(KeyManager)

private:
	std::vector<KeyInfo> keyInfos;
	int keyCodes[(int)KeyType::LAST] =
	{	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 
		'Q','W','E','R', 'T','Y','U','I',
		'O','P', 'A','S','D','F','G','H',
		'J','K','L', 'Z','X','C','V','B',
		'N','M', VK_CONTROL, VK_LMENU, 
		VK_LSHIFT, VK_SPACE, VK_RETURN, VK_TAB, 
		VK_ESCAPE, VK_LBUTTON, VK_RBUTTON };

	POINT mousePosition;

private:
	void Clear();

public:
	const POINT& GetMousePosition() const { return mousePosition; }
	const KeyState& GetKey(KeyType key) const { return keyInfos[(int)key].state; }

public:
	void Init();
	void Update();
};

