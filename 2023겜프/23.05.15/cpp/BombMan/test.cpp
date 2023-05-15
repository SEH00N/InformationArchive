#include <iostream>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include "console.h";
#include "GameLogic.h";
#include "StartScene.h";

#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
	char cMaze[VERTICAL][HORIZONTAL] = {};
	PLAYER tPlayer = {};
	POS tStartPos = {};
	POS tEndPos = {};
	vector<BOOM> vecBoom;
	vector<POS> vecBoomEffect;

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
	clock_t oldTime, currentTime;
	oldTime = clock();

	while (true)
	{
		Go2xy(0, 0);
		Update(cMaze, &tPlayer, vecBoom, vecBoomEffect);
		Render(cMaze, &tPlayer, vecBoomEffect);
		Event(vecBoom, vecBoomEffect);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			PlaySound(TEXT("random.wav"), 0, SND_FILENAME | SND_ASYNC);
			Sleep(1000);
			break;
		}

		while (true)
		{
			currentTime = clock();
			if(currentTime - oldTime >= 1000/30.f * 2.f)
			{
				oldTime = currentTime;
				break;
			}
		}
	}

	return 0;
}