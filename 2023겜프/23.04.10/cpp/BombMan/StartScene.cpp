#include <iostream>
#include "console.h";
#include "StartScene.h"

using namespace std;

int GameMenu()
{
	int x = 30, y = 12;
	
	Go2xy(x, y);
	cout << "게임 시작";
	
	Go2xy(x, y + 1);
	cout << "게임 정보";
	
	Go2xy(x, y + 2);
	cout << "종료 하기";

	while (true) {
		int iKey = KeyController();

		switch (iKey)
		{
		case (int)KEY::UP:
		{
			if (y > 12)
			{
				Go2xy(x - 2, y);
				cout << ' ';
				Go2xy(x - 2, --y);
				cout << '>';
			}
		}
			break;
		case (int)KEY::DOWN:
		{
			if (y < 14)
			{
				Go2xy(x - 2, y);
				cout << ' ';
				Go2xy(x - 2, ++y);
				cout << '>';
			}
		}
			break;
		case (int)KEY::SPACE:
		{
			return (y - 12);
		}
			break;
		default:
			break;
		}
	}

	return -1;
}

int KeyController()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		return (int)KEY::UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		return (int)KEY::DOWN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		return (int)KEY::SPACE;

	Sleep(200);
	return -1;
}

void GameInfo()
{

}