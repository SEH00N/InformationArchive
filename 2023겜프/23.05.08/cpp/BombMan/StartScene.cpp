#include <iostream>
#include "console.h";
#include "StartScene.h"
#include <conio.h>

using namespace std;

int GameMenu()
{
	int x = 30, y = 12;
	
	Go2xy(x, y);
	cout << "���� ����";
	
	Go2xy(x, y + 1);
	cout << "���� ����";
	
	Go2xy(x, y + 2);
	cout << "���� �ϱ�";

	Go2xy(x - 2, y);
	cout << ">";

	while (true) {
		int iKey = KeyController();

		switch (iKey)
		{
		case (int)KEY::UP:
		{
			if (y > 12)
			{
				Go2xy(x - 2, y);
				cout << " ";
				Go2xy(x - 2, --y);
				cout << ">";
			}
		}
			break;
		case (int)KEY::DOWN:
		{
			if (y < 14)
			{
				Go2xy(x - 2, y);
				cout << " ";
				Go2xy(x - 2, ++y);
				cout << ">";
			}
		}
			break;
		case (int)KEY::SPACE:
		{
			return (y - 12);
		}
			break;
		}
	}

	return -1;
}

int KeyController()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//	return (int)KEY::UP;
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//	return (int)KEY::DOWN;
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//	return (int)KEY::SPACE;
	// Sleep(20);

	int iKey = _getch();
	if (iKey == 224)
	{
		iKey = _getch();
		switch (iKey)
		{
		case 72: //UP
			return (int)KEY::UP;
			break;
		case 80: //DOWN
			return (int)KEY::DOWN;
			break;
		}
	}
	else if (iKey == 32)
		return (int)KEY::SPACE;

	return -1;
}

void GameInfo()
{
	system("cls");
	//cout << endl << endl;
	cout << "[���۹�]" << endl;
	cout << "�޴� �̵� : ����Ű" << endl;
	cout << "�޴� ���� : �����̽���" << endl;
	cout << "����Ű�� ������ ��ǥ������ �����ϼ���." << endl;
	cout << "SpaceBar : ��ź ��ġ, e : Ǫ�ôɷ� ON / OFF" << endl;

	while (true)
	{
		if (KeyController() == (int)KEY::SPACE)
			break;
	}
}