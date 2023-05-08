#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "console.h"

using namespace std;

int main()
{
	//Go2xy(10, 10);
	//ConsoleCursor(false, 1);
	//
	//cout << "Hello, World!\n";

	//Sleep(3 * 1000);

	//int oldColor = GetColor() | (GetbgColor() << 4);
	//system("cls");
	//for(int i = 0; i < (int)COLOR::WHITE + 1; ++i)
	//{
	//	Go2xy(i, i);

	//	SetColor(i, (int)COLOR::BLACK);
	//	cout << "color number : ";
	//	SetColor(oldColor, oldColor >> 4);
	//	cout << i << '\n';
	//}

	int test;
	int x = 0, y = 0;
	int beforeX = 0, beforeY = 0;

	system("mode con cols=80 lines=40");
	HWND hConsole = GetConsoleWindow();
	SetWindowLong(hConsole, GWL_STYLE, GetWindowLong(hConsole, (hConsole, GWL_STYLE) & ~WS_MAXIMIZE & ~WS_SIZEBOX));
	RECT rt;
	GetWindowRect(hConsole, &rt);

	clock_t OldTime, CurTime;
	OldTime = clock();

	while (true)
	{
		CurTime = clock();
		if (CurTime - OldTime > 1000)
		{
			cout << "1초가 지났다.\n";
			OldTime = CurTime;
		}
		//if (_kbhit())
		//{
		//	test = _getch();
			//if (test == 224)
			//{
			//	test = _getch();
			//	switch (test)
			//	{
			//	case 72:
			//		--y;
			//		//cout << "위쪽\n";
			//		break;
			//	case 75:
			//		--x;
			//		//cout << "왼쪽\n";
			//		break;
			//	case 77:
			//		++x;
			//		//cout << "오른쪽\n";
			//		break;
			//	case 80:
			//		//cout << "아래쪽\n";
			//		++y;
			//		break;
			//	default:
			//		break;
			//	}
			//}

			BOOL result = Go2xyPlayer(x, y);
			if (result == FALSE)
			{
				x = beforeX;
				y = beforeY;
				continue;
			}
			else
			{
				beforeX = x;
				beforeY = y;
			}

			_putch('a');

			if (GetAsyncKeyState(VK_UP) & 0x8000) y--;
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)y++;
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)x--;
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)x++;

			Sleep(50);
		//}

	}
	
	//int a;
	//while (true)
	//{
	//	cin >> a;
	//	if (cin.fail())
	//	{
	//		cout << "비정상 입력\n";
	//		cin.clear();
	//		cin.ignore(1024, '\n');
	//	}
	//	//cout << a << '\n';
	//}

	return 0;
}