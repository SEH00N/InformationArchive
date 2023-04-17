#include <io.h>
#include <iostream>
#include <fcntl.h>
#include "console.h"
#include <string>
#include "GameLogic.h"
#include <windows.h>

using namespace std;

int cursorY = 0;

void AsciiArt()
{
	int previewMode = _setmode(_fileno(stdout), _O_U16TEXT);

	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗ \n";
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗████╗ ████║██╔══██╗████╗  ██║ \n";
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝██╔████╔██║███████║██╔██╗ ██║ \n";
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║ \n";
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║ \n";
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝ \n";

	int curMode = _setmode(_fileno(stdout), _O_TEXT);
}

void Init(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, PPOS _pStartPos, PPOS _pEndPos)
{
	//SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 80, 30 });
	//system("mode con cols=80 lines=30");
	ConsoleCursor(false, 1);

	SetConsoleTitle(TEXT("2 - 1  BOMBMAN"));

	_pEndPos->x = 20;
	_pEndPos->y = 16;

	_pStartPos->x = 0;
	_pStartPos->y = 0;

	PLAYER tSetPlayer = { *_pStartPos, 1, 0, false, false };
	*_pPlayer = tSetPlayer;

	strcpy_s(_cMaze[0],		"21100000000000000000");
	strcpy_s(_cMaze[1],		"10111111110000000000");
	strcpy_s(_cMaze[2],		"00000000011111100000");
	strcpy_s(_cMaze[3],		"00000000000000100000");
	strcpy_s(_cMaze[4],		"00000000000000100000");
	strcpy_s(_cMaze[5],		"00000000000000100000");
	strcpy_s(_cMaze[6],		"00000000000000100000");
	strcpy_s(_cMaze[7],		"00000000000000100000");
	strcpy_s(_cMaze[8],		"00000111111111100000");
	strcpy_s(_cMaze[9],		"00000110000000000000");
	strcpy_s(_cMaze[9],		"00000011100000000000");
	strcpy_s(_cMaze[10],	"00000000111000000000");
	strcpy_s(_cMaze[11],	"00000000001100000000");
	strcpy_s(_cMaze[12],	"00000000000111111100");
	strcpy_s(_cMaze[13],	"00000000000000000100");
	strcpy_s(_cMaze[14],	"00000000000000000100");
	strcpy_s(_cMaze[15],	"00000000000000000113");
	strcpy_s(_cMaze[16],	"00000000000000000000");
	strcpy_s(_cMaze[17],	"00000000000000000000");
	strcpy_s(_cMaze[18],	"00000000000000000000");
	strcpy_s(_cMaze[19],	"00000000000000000000");
}

void Update(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer)
{
	POS temp = _pPlayer->tPos;

	if (GetAsyncKeyState(VK_UP) && 0x8000)
		temp.y--;
	else if (GetAsyncKeyState(VK_DOWN) && 0x8000)
		temp.y++;
	else if (GetAsyncKeyState(VK_LEFT) && 0x8000)
		temp.x--;
	else if (GetAsyncKeyState(VK_RIGHT) && 0x8000)
		temp.x++;

	if (temp.y < VERTICAL && temp.y >= 0 && temp.x < HORIZONTAL - 1 && temp.x >= 0)
		if (_cMaze[temp.y][temp.x] != (char)MAPTYPE::WALL)
			_pPlayer->tPos = temp;

	Sleep(100);
}

void Render(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer)
{
	for (int i = 0; i < VERTICAL; ++i)
	{
		for (int j = 0; j < HORIZONTAL; ++j)
		{
			if (i == _pPlayer->tPos.y && j == _pPlayer->tPos.x)
				cout << "@";
			else if (_cMaze[i][j] == (char)MAPTYPE::WALL)
				cout << "■";
			else if(_cMaze[i][j] == (char)MAPTYPE::ROAD)
				cout << " ";
			else if(_cMaze[i][j] == (char)MAPTYPE::START)
				cout << "⊙";
			else if(_cMaze[i][j] == (char)MAPTYPE::END)
				cout << "♨";
		}
		cout << endl;
	}
}
