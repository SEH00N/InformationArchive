#include <io.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include <algorithm>
#include "console.h"
#include "GameLogic.h"
#include <vector>

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

	_pEndPos->x = 19;
	_pEndPos->y = 15;

	_pStartPos->x = 0;
	_pStartPos->y = 0;

	PLAYER tSetPlayer = { *_pStartPos, {}, 1, 0, false, false };
	*_pPlayer = tSetPlayer;

	strcpy_s(_cMaze[0], "21100000000000000000");
	strcpy_s(_cMaze[1], "00111111110000000000");
	strcpy_s(_cMaze[2], "00000000011111100000");
	strcpy_s(_cMaze[3], "00000000000000100000");
	strcpy_s(_cMaze[4], "00000000000000100000");
	strcpy_s(_cMaze[5], "00000000000000100000");
	strcpy_s(_cMaze[6], "00000000000000100000");
	strcpy_s(_cMaze[7], "00000000000000100000");
	strcpy_s(_cMaze[8], "00000011111111100000");
	strcpy_s(_cMaze[9], "00000010000000000000");
	strcpy_s(_cMaze[10], "00000011110000000000");
	strcpy_s(_cMaze[11], "00000000011100000000");
	strcpy_s(_cMaze[12], "00000000000111111100");
	strcpy_s(_cMaze[13], "00000000000000000100");
	strcpy_s(_cMaze[14], "00000000000000000100");
	strcpy_s(_cMaze[15], "00000000000000000113");
	strcpy_s(_cMaze[16], "00000000000000000010");
	strcpy_s(_cMaze[17], "00000000000000000010");
	strcpy_s(_cMaze[18], "00000000000000000010");
	strcpy_s(_cMaze[19], "00000000000000000010");
}

void Update(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, vector<BOOM>& _vecBomb, vector<POS>& _vecBoomEffect)
{
	_pPlayer->tNewPos = _pPlayer->tPos;
	Sleep(50);

	POS input{};

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		--_pPlayer->tNewPos.y;
		input.y--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		++_pPlayer->tNewPos.y;
		input.y++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		--_pPlayer->tNewPos.x;
		input.x--;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		++_pPlayer->tNewPos.x;
		input.x++;
	}

	_pPlayer->tNewPos.x = clamp(_pPlayer->tNewPos.x, 0, HORIZONTAL - 2);
	_pPlayer->tNewPos.y = clamp(_pPlayer->tNewPos.y, 0, VERTICAL - 1);

	//if (_pPlayer->tNewPos.y < VERTICAL && _pPlayer->tNewPos.y >= 0 && _pPlayer->tNewPos.x < HORIZONTAL - 1 && _pPlayer->tNewPos.x >= 0)
	//if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != (char)MAPTYPE::WALL && _cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != (char)MAPTYPE::WATERBOMB)
		

	if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] == (char)MAPTYPE::WALL)
	{
		if (_pPlayer->bSlime) //슬라임일 때
		{
			_pPlayer->tPos = _pPlayer->tNewPos;
		}
		if (_pPlayer->bPushToggle) //푸쉬일 때
		{
			if (_cMaze[_pPlayer->tNewPos.y + input.y][_pPlayer->tNewPos.x + input.x] == (char)MAPTYPE::ROAD)
			{
				_pPlayer->tPos = _pPlayer->tNewPos;
				_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] = (char)MAPTYPE::ROAD;
				_cMaze[_pPlayer->tNewPos.y + input.y][_pPlayer->tNewPos.x + input.x] = (char)MAPTYPE::WALL;
				//_pPlayer->bPushToggle = false;
			}
		}
	}
	else if (_cMaze[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x] != (char)MAPTYPE::WATERBOMB)
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}

	if (GetItem(_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x], _pPlayer))
		_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] = (char)MAPTYPE::ROAD;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		BombCreate(_cMaze, _pPlayer, _vecBomb);

	int iBombCount = _pPlayer->iBombCount;
	for (int i = 0; i < iBombCount; i++)
	{
		BOOM& boomItem = _vecBomb[i];
		--boomItem.life;

		char tile = boomItem.life % 10 >= 5 ? (char)MAPTYPE::WATERBOMB : (char)MAPTYPE::TWINKLE;
		_cMaze[boomItem.y][boomItem.x] = tile;

		if (boomItem.life <= 0)
		{
			boomItem.bDie = true;
			--_pPlayer->iBombCount;

			Fire(_cMaze, _pPlayer, { boomItem.x, boomItem.y }, _vecBoomEffect);
		}
	}


	if (GetAsyncKeyState('E') & 0x8000)
		if(_pPlayer->bWallPush)
			_pPlayer->bPushToggle = !_pPlayer->bPushToggle;
}

void Render(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, vector<POS>& _vecBoomEffect)
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
			else if (_cMaze[i][j] == (char)MAPTYPE::WATERBOMB)
			{
				SetColor((int)COLOR::MINT, (int)COLOR::BLACK);
				cout << "☆";
			}
			else if (_cMaze[i][j] == (char)MAPTYPE::TWINKLE)
			{
				SetColor((int)COLOR::SKYBLUE, (int)COLOR::BLACK);
				cout << "⊙";
			}
			else if(_cMaze[i][j] == (char)MAPTYPE::POWER)
				cout << "◐";
			else if(_cMaze[i][j] == (char)MAPTYPE::SLIME)
				cout << "♤";
			else if(_cMaze[i][j] == (char)MAPTYPE::PUSH)
				cout << "□";

			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << endl;
	}

	cout << "SPACEBAR : 폭탄설치, E : 푸시능력 ON / OFF" << endl;
	cout << "폭탄 파워 : " << _pPlayer->iBombPower << endl;
	cout << "푸시 능력 : " << (_pPlayer->bPushToggle ? "ON " : "OFF") << endl;
	cout << "슬라임 능력 : " << (_pPlayer->bSlime ? "ON " : "OFF") << endl;
}

void Event(std::vector<BOOM>& _vecBomb)
{
	std::vector <BOOM>::iterator iter;

	for (iter = _vecBomb.begin(); iter != _vecBomb.end();)
	{
		if (iter->bDie)
			iter = _vecBomb.erase(iter);
		else
			iter++;
	}

	//for (iter = _vecBomb.end(); iter-- != _vecBomb.begin();)
	//	if (iter->bDie)
	//		_vecBomb.erase(iter);
	//if (iter->bDie)
	//	_vecBomb.erase(iter);
}

bool GetItem(char _cItem, PPLAYER _pPlayer)
{
	if (_cItem == (char)MAPTYPE::POWER)
	{
		++_pPlayer->iBombPower;
		return true;
	}
	else if (_cItem == (char)MAPTYPE::SLIME)
	{
		_pPlayer->bSlime = true;
		return true;
	}
	else if (_cItem == (char)MAPTYPE::PUSH)
	{
		_pPlayer->bWallPush = true;
		_pPlayer->bPushToggle = true;
		return true;
	}

	return false;
}

void BombCreate(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, std::vector<BOOM>& _vecBomb)
{
	if (_pPlayer->iBombCount >= 5)
		return;

	if (_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] == (char)MAPTYPE::ROAD)
	{
		_cMaze[_pPlayer->tPos.y][_pPlayer->tPos.x] = 'b';
		_pPlayer->iBombCount++;

		_vecBomb.push_back({_pPlayer->tPos.x, _pPlayer->tPos.y, 50, false});
	}
}

void Fire(char _cMaze[VERTICAL][HORIZONTAL], PPLAYER _pPlayer, POS _boomPos, std::vector<POS>& _vecBoomEffect)
{
	_cMaze[_boomPos.y][_boomPos.x] = (char)MAPTYPE::ROAD;

	int iScopeMinX = std::clamp(_boomPos.x - _pPlayer->iBombPower, 0, HORIZONTAL - 2);
	int iScopeMaxX = std::clamp(_boomPos.x + _pPlayer->iBombPower, 0, HORIZONTAL - 2);
	int iScopeMinY = std::clamp(_boomPos.y - _pPlayer->iBombPower, 0, VERTICAL - 1);
	int iScopeMaxY = std::clamp(_boomPos.y + _pPlayer->iBombPower, 0, VERTICAL - 1);

	if ((_pPlayer->tPos.x >= iScopeMinX && _pPlayer->tPos.x <= iScopeMaxX && _pPlayer->tPos.y == _boomPos.y) || (_pPlayer->tPos.y >= iScopeMinY && _pPlayer->tPos.y <= iScopeMaxY && _pPlayer->tPos.x == _boomPos.x))
		_pPlayer->tPos = { 0,0 };

	vector<POS> vecEffect;
	for (int i = iScopeMinX; i <= iScopeMaxX; ++i)
		vecEffect.push_back({ i, _boomPos.y });
	for (int i = iScopeMinY; i <= iScopeMaxY; ++i)
		vecEffect.push_back({ _boomPos.x, i });

	for (auto& target : vecEffect)
	{
		if (_cMaze[target.y][target.x] == (char)MAPTYPE::WALL)
		{
			int percent = rand() % 10001 / 100.f;
			if (percent <= 50.f)
			{
				percent = rand() % 10001 / 100.f;
				if (percent <= 50.f) //물풍선
					_cMaze[target.y][target.x] = (char)MAPTYPE::POWER;
				else if (percent <= 80.f) //푸시
					_cMaze[target.y][target.x] = (char)MAPTYPE::SLIME;
				else //슬라임
					_cMaze[target.y][target.x] = (char)MAPTYPE::PUSH;
			}
			else
				_cMaze[target.y][target.x] = (char)MAPTYPE::ROAD;
		}
		
	}
}

