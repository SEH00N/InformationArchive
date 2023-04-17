#include <iostream>
#include "console.h";
#include "GameLogic.h";
#include "StartScene.h";

using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZONTAL] = {};
	PLAYER tPlayer = {};
	POS tStartPos = {};
	POS tEndPos = {};

	Init(cMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true) {
		system("cls");
		AsciiArt();
		int iMenu = GameMenu();

		if (iMenu == 0)
			break;
		else if (iMenu == 1)
			GameInfo();
		else if (iMenu == 2)
		{
			Sleep(100);
			system("cls");
			cout << "게임을 종료합니다." << endl;

			for (int i = 0; i < 3; ++i)
			{
				cout << '\r' << 3 - i << "...";
				Sleep(1000);
			}

			return 0;
		}
	}

	system("cls");
	while (true)
	{
		Go2xy(0, 0);
		Update(cMaze, &tPlayer);
		Render(cMaze, &tPlayer);
	}

	return 0;
}