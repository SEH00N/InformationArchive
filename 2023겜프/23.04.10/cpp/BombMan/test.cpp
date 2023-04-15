#include <iostream>
#include "console.h";
#include "bombman.h";
#include "StartScene.h";

using namespace std;

int main()
{
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), {80, 30});
	//system("mode con cols=80 lines=30");
	ConsoleCursor(false, 1);

	while (true) {
		AsciiArt();
		int iMenu = GameMenu();

		if (iMenu == 0)
			break;
		else if (iMenu == 1)
			GameInfo();
		else if (iMenu == 2)
		{
			cout << "게임을 종료합니다." << endl;

			for (int i = 0; i < 3; ++i)
			{
				cout << '\r' << i + 1 << "...";
				Sleep(1000);
			}

			return 0;
		}
	}

	return 0;
}